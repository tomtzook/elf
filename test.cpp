
#include <iostream>
#include <fstream>
#include <vector>

#include <elf.h>
#include <debug.h>



int main() {
    const char* path = "/home/tomtzook/projects/pe/cmake-build-debug/pe_test";
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);

    elf::image image(buffer.data());
    std::cout << image << std::endl;

    for (auto section : image.sections()) {
        std::cout << "SECTION:" << std::endl
                  << "\tName: " << image.sections().names()[section.name_offset()] << std::endl
                  << "\tType: " << section.type() << std::endl
                  << "\tFlags: " << section.flags() << std::endl;
    }

    /*auto header = reinterpret_cast<const elf::header64*>(buffer.data());

    for (int i = 0; i < sizeof(elf::file_identification); i++) {
        std::cout << "0x"
                  << std::hex << (int)header->identification.all[i]
                  << " ";
    }
    std::cout << std::endl;

    std::cout << "IDENTIFICATION:" << std::endl
              << "\tMagic: " << header->identification.magic << std::endl
              << "\tClass: " << std::hex << (int)header->identification.fclass << std::endl
              << "\tData: " << std::hex << (int)header->identification.data << std::endl
              << "\tVersion: " << std::hex << (int)header->identification.version << std::endl
              << "HEADER:" << std::endl
              << "\tTYPE: " << std::hex << (int)header->type << std::endl
              << "\tMACHINE: " << (int)header->machine << std::endl
              << "\tVERSION " << std::hex << (int)header->version << std::endl;

    elf::image image(buffer.data());

    for (auto section : image.sections()) {
        std::cout << "SECTION:" << std::endl
            << "\tName: " << image.sections().names()[section.name_offset()] << std::endl
            << "\tType: " << std::hex << section.type() << std::endl
            << "\tFlags: " << std::hex << section.flags().data << std::endl;
    }*/
}