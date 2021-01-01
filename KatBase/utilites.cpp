#include "pch.h"

std::uint32_t ResolveImport(const char* importName, std::int32_t index)
{
	HMODULE hMod = GetModuleHandleA(importName);
	return hMod ? (std::uint32_t)GetProcAddress(hMod, (LPCSTR)index) : NULL;
}

wchar_t* ConvertToWChar(const char* text)
{
	const size_t cSize = strlen(text) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t tmp = 0;
	mbstowcs_s(&tmp, wc, cSize, text, cSize);
	return wc;
}


XNotifyQueueUI_t XNotifyQueueUI = XNotifyQueueUI_t(ResolveImport("xam.xex", 0x290));
XamGetCurrentTitleId_t XamGetCurrentTitleId = XamGetCurrentTitleId_t(ResolveImport("xam.xex", 0x1CF));

void XNotify(const char* text, XNOTIFYQUEUEUI_TYPE icon)
{
	XNotifyQueueUI(icon, 0xFF, XNOTIFY_SYSTEM, ConvertToWChar(text), 0);
}

char* va(const char* fmt, ...)
{
	va_list argList;
	va_start(argList, fmt);
	char buffer[0x2000];
	vsprintf(buffer, fmt, argList);
	va_end(argList);
	return buffer;
	delete[] buffer;
}

char* concat(const char* text, ...)
{
	va_list list;
	char buffer[0x1000];
	va_start(list, text);
	vsprintf(buffer, text, list);
	va_end(list);
	char* result = (char*)malloc(strlen(buffer) + 1);
	strcpy(result, buffer);

	return result;
}

void WriteMemory(std::uint32_t Address, BYTE Data[], std::int32_t size)
{
	for (auto i = 0; i < size; i++)
		*(BYTE*)(Address + i) = Data[i];
}

BYTE* ReadMemory(std::uint32_t Address, std::int32_t size)
{
	BYTE* buffer;
	memcpy(buffer, (void*)Address, size);
	return buffer;
}

XINPUT_STATE Buttons;
bool KeyIsDown(XINPUT_STATE xState, short button)
{
	return (xState.Gamepad.wButtons & button) ? true : false;
}

byte* stubAlloc = NULL;
bool stubSpaceUsed[0x200];

DWORD* AllocateStubSpace() {
	for (int i = 0; i < sizeof stubSpaceUsed; i++) {
		if (!stubSpaceUsed[i]) {
			stubSpaceUsed[i] = true;
			return (DWORD*)(stubAlloc + i * 0x80);
		}
	}

	Sleep(1000);
	ExitThread(-1);
}
void FreeStub(void* stub) {
	if ((DWORD)stub < (DWORD)stubAlloc
		|| (DWORD)stub >= (DWORD)(stubAlloc + 0x10000))
		return;

	memset((void*)((DWORD)stub & ~0x7F), 0, 0x80);
	stubSpaceUsed[((DWORD)stub - (DWORD)stubAlloc) / 0x80] = false;
}

DWORD revertBranch(byte* addr, DWORD instr)
{
	return (instr < 0x4A000000) ? ((DWORD)addr + (instr & 0x3FFFFFE)) : ((DWORD)addr - (~instr & 0x3FFFFFE)) & ~3;
}

MinHook_t::MinHook_t(unsigned long address, unsigned long destination, bool stub)
{
	this->address = (unsigned long*)address;
	this->destination = destination;
	memcpy(this->originalStub, (void*)address, 0x10);

	if (stub) {
		if (!stubAlloc)
			stubAlloc = (byte*)XEncryptedAlloc(0x10000);

		this->saveStub = AllocateStubSpace();
		this->Stub = (StubCallback)this->saveStub;
	}
	else
		this->saveStub = NULL;
}

void MinHook_t::Start()
{
	if (this->address == NULL)
		return;

	if (this->saveStub != NULL)
	{
		DWORD* pFunc = (DWORD*)this->address;

		int stubSize = 4;
		for (int i = 0; i < 4; i++) {
			if ((pFunc[i] & 0xFC000002) == 0x48000000)
				stubSize += 4;
			else
				stubSize += 1;
		}

		for (int i = 0, stubIndex = 0; i < 4; i++) {
			if ((pFunc[i] & 0xFC000002) == 0x48000000) {
				DWORD calladdr = revertBranch((byte*)&pFunc[i], pFunc[i]);
				this->saveStub[stubIndex] = 0x3D600000 | (calladdr >> 16);
				this->saveStub[stubIndex + 1] = 0x616B0000 | (calladdr & 0xFFFF);
				this->saveStub[stubIndex + 2] = 0x7D6903A6;
				this->saveStub[stubIndex + 3] = 0x4E800421;
				stubIndex += 4;
			}
			else {
				this->saveStub[stubIndex] = pFunc[i];
				stubIndex++;
			}
		}

		DWORD jumpback = (DWORD)this->address + 0x10;
		this->saveStub[stubSize - 4] = 0x3D800000 | (jumpback >> 16); // lis r12, addrhi
		this->saveStub[stubSize - 3] = 0x618C0000 | (jumpback & 0xFFFF); // ori r12, r12, addrlo
		this->saveStub[stubSize - 2] = 0x7D8903A6; // mtctr r12
		this->saveStub[stubSize - 1] = 0x4E800420; // bctr
	}

	this->address[0] = ((this->destination & 0x8000) ? 0x3D600000 + (((this->destination >> 16) & 0xFFFF) + 1) : 0x3D600000 + ((this->destination >> 16) & 0xFFFF));
	this->address[1] = 0x396B0000 + (this->destination & 0xFFFF);
	this->address[2] = 0x7D6903A6;
	this->address[3] = 0x4E800420;
}

void MinHook_t::Stop()
{
	if (this->address)
		memcpy(this->address, this->originalStub, 0x10);

	if (this->saveStub)
		FreeStub(this->saveStub);
}

void MinHook_t::Clean()
{
	this->address = NULL;
}

MinHook_t MinHook[10];

void StopHooks()
{
	for (int i = 0; i < ARRAYSIZE(MinHook); i++)
		MinHook[i].Stop();
}

void CleanHooks()
{
	for (int i = 0; i < ARRAYSIZE(MinHook); i++)
		MinHook[i].Clean();
}

void StartHooks()
{
	for (int i = 0; i < ARRAYSIZE(MinHook); i++)
		MinHook[i].Start();
}