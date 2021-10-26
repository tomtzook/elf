
#include <iostream>
#include <fstream>
#include <vector>

#include <elf.h>
#include <debug.h>



int main() {
    //const char* path = "/home/tomtzook/projects/pe/cmake-build-debug/pe_test";
    const char* path = "/home/tomtzook/development/native/pru-test/cmake-build-debug-ti-pru/pru_test.out";
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);

    elf::image image(buffer.data());
    std::cout << image << std::endl;

    for (auto program : image.programs()) {
        std::cout << "PROGRAM:" << std::endl
                  << "\tType: " << program.type() << std::endl
                  << "\tFlags: " << program.flags() << std::endl
                  << "\tSize: " << program.size() << std::endl;

        if (program.flags().bits.execute) {
            // code
            std::cout << "CODE PROGRAM" << std::endl;

            for (int i = 0; i < 20; ++i) {
                std::cout << std::hex << (int)program.data<uint8_t>()[i] << " ";
            }
            std::cout << std::endl;

        } else if (program.flags().bits.read || program.flags().bits.write) {
            // data
            std::cout << "DATA PROGRAM" << std::endl;
        }
    }

    /*for (auto section : image.sections()) {
        std::cout << "SECTION:" << std::endl
                  << "\tName: " << image.sections().names()[section.name_offset()] << std::endl
                  << "\tType: " << section.type() << std::endl
                  << "\tFlags: " << section.flags() << std::endl;
    }*/



}