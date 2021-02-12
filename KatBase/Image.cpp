#include "pch.h"

void ReadImage() {
    std::streampos size;
    char* memblock;

    std::ifstream file("Shake.bin");
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char[size];
        file.seekg(0);
        file.read(memblock, size);
        file.close();

        std::cout << "the entire file content is in memory";

        delete[] memblock;
    }
    else std::cout << "Unable to open file";
}
