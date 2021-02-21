#include "pch.h"
using namespace std;

void ReadImage() {
	char* memblock;
	int size = 0;
	std::ifstream file("hdd:\\Shake.bin");
	if (file.is_open())
	{
		file.open("Shake.bin", ios::in | ios::binary);
		file.seekg(0, ios::end);
		size = (int)file.tellg();
		file.seekg(0, ios::beg);

		while (file.tellg() < size)
		{
			file.read(memblock, size);

			*(char*)0xA881C000 = *memblock;
		}
		file.close();
		std::cout << "the entire file content is in memory\n";

		delete[] memblock;
	}
	else std::cout << "Unable to open file";
}
