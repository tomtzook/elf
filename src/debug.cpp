

#include "debug.h"


#define FLAG_BIT_DEBUG(bit, str) \
    if (bit) {                              \
        if (has) {                          \
            os << " | ";                    \
        }                                   \
        os << str;                          \
        has = true;                         \
    }


std::ostream& operator<<(std::ostream& os, const elf::file_class& file_class) {
    switch (file_class) {
        case elf::file_class::FILE_CLASS_NONE: os << "FILE_CLASS_NONE"; break;
        case elf::file_class::FILE_CLASS_CLASS32: os << "FILE_CLASS_CLASS32"; break;
        case elf::file_class::FILE_CLASS_CLASS64: os << "FILE_CLASS_CLASS64"; break;
    }    
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::data_encoding& data_encoding) {
    switch (data_encoding) {
        case elf::data_encoding::ENCODING_NONE: os << "ENCODING_NONE"; break;
        case elf::data_encoding::ENCODING_LSB: os << "ENCODING_LSB"; break;
        case elf::data_encoding::ENCODING_MSB: os << "ENCODING_MSB"; break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::file_identification& file_identification) {
    os << "IDENTIFICATION: ";

    for (int i = 0; i < sizeof(elf::file_identification); i++) {
        os << "0x" << std::hex << static_cast<int>(file_identification.all[i]);
        if (i < sizeof(elf::file_identification) - 1) {
            os << " ";
        }
    }
    os << std::endl;

    os << "\tMagic: " << file_identification.magic << std::endl
       << "\tClass: " << file_identification.fclass << std::endl
       << "\tData: " << file_identification.data << std::endl
       << "\tVersion: " << std::hex << static_cast<int>(file_identification.version);
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::file_type& file_type) {
    switch (file_type) {
        case elf::file_type::FILE_TYPE_NONE: os << "FILE_TYPE_NONE"; break;
        case elf::file_type::FILE_TYPE_REL: os << "FILE_TYPE_REL"; break;
        case elf::file_type::FILE_TYPE_EXEC: os << "FILE_TYPE_EXEC"; break;
        case elf::file_type::FILE_TYPE_DYN: os << "FILE_TYPE_DYN"; break;
        case elf::file_type::FILE_TYPE_CORE: os << "FILE_TYPE_CORE"; break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::machine_type& type) {
    switch (type) {
       case elf::machine_type::MACHINE_NONE: os << "MACHINE_NONE"; break;
       case elf::machine_type::MACHINE_M32: os << "MACHINE_M32"; break;
       case elf::machine_type::MACHINE_SPARC: os << "MACHINE_SPARC"; break;
       case elf::machine_type::MACHINE_INTEL386: os << "MACHINE_INTEL386"; break;
       case elf::machine_type::MACHINE_MOTOROLA68K: os << "MACHINE_MOTOROLA68K"; break;
       case elf::machine_type::MACHINE_MOTOROLA88K: os << "MACHINE_MOTOROLA88K"; break;
       case elf::machine_type::MACHINE_INTEL486: os << "MACHINE_INTEL486"; break;
       case elf::machine_type::MACHINE_INTEL860: os << "MACHINE_INTEL860"; break;
       case elf::machine_type::MACHINE_MIPS: os << "MACHINE_MIPS"; break;
       case elf::machine_type::MACHINE_MIPSRS3LE: os << "MACHINE_MIPSRS3LE"; break;
       case elf::machine_type::MACHINE_PARISC: os << "MACHINE_PARISC"; break;
       case elf::machine_type::MACHINE_SPARC32PLUS: os << "MACHINE_SPARC32PLUS"; break;
       case elf::machine_type::MACHINE_PPC: os << "MACHINE_PPC"; break;
       case elf::machine_type::MACHINE_PPC64: os << "MACHINE_PPC64"; break;
       case elf::machine_type::MACHINE_SPU: os << "MACHINE_SPU"; break;
       case elf::machine_type::MACHINE_ARM: os << "MACHINE_ARM"; break;
       case elf::machine_type::MACHINE_SH: os << "MACHINE_SH"; break;
       case elf::machine_type::MACHINE_SPARCV9: os << "MACHINE_SPARCV9"; break;
       case elf::machine_type::MACHINE_H8300: os << "MACHINE_H8300"; break;
       case elf::machine_type::MACHINE_IA64: os << "MACHINE_IA64"; break;
       case elf::machine_type::MACHINE_X8664: os << "MACHINE_X8664"; break;
       case elf::machine_type::MACHINE_S390: os << "MACHINE_S390"; break;
       case elf::machine_type::MACHINE_CRIS : os << "MACHINE_CRIS"; break;
       case elf::machine_type::MACHINE_M32R: os << "MACHINE_M32R"; break;
       case elf::machine_type::MACHINE_MN10300: os << "MACHINE_MN10300"; break;
       case elf::machine_type::MACHINE_OPENRISC: os << "MACHINE_OPENRISC"; break;
       case elf::machine_type::MACHINE_ARCOMPACT: os << "MACHINE_ARCOMPACT"; break;
       case elf::machine_type::MACHINE_XTENSA: os << "MACHINE_XTENSA"; break;
       case elf::machine_type::MACHINE_BLACKFIN: os << "MACHINE_BLACKFIN"; break;
       case elf::machine_type::MACHINE_UNICORE: os << "MACHINE_UNICORE"; break;
       case elf::machine_type::MACHINE_ALTERANIOS2: os << "MACHINE_ALTERANIOS2"; break;
       case elf::machine_type::MACHINE_TIC6000: os << "MACHINE_TIC6000"; break;
       case elf::machine_type::MACHINE_HEXAGON: os << "MACHINE_HEXAGON"; break;
       case elf::machine_type::MACHINE_NDS32: os << "MACHINE_NDS32"; break;
       case elf::machine_type::MACHINE_AARCH64: os << "MACHINE_AARCH64"; break;
       case elf::machine_type::MACHINE_TILEPRO: os << "MACHINE_TILEPRO"; break;
       case elf::machine_type::MACHINE_MICROBLAZE: os << "MACHINE_MICROBLAZE"; break;
       case elf::machine_type::MACHINE_TILEGX: os << "MACHINE_TILEGX"; break;
       case elf::machine_type::MACHINE_ARCV2: os << "MACHINE_ARCV2"; break;
       case elf::machine_type::MACHINE_RISCV: os << "MACHINE_RISCV"; break;
       case elf::machine_type::MACHINE_BPF: os << "MACHINE_BPF"; break;
       case elf::machine_type::MACHINE_CSKY: os << "MACHINE_CSKY"; break;
       case elf::machine_type::MACHINE_FRV: os << "MACHINE_FRV"; break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::image_headers& headers) {
    os << "IMAGE:" << std::endl
        << "\t" << headers.identification() << std::endl
        << "\tMachine: " << headers.machine();

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::image& image) {
    os << image.headers();

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::program_type& type) {
    switch (type) {
        case elf::program_type::PROGRAM_NONE: os << "PROGRAM_NONE"; break;
        case elf::program_type::PROGRAM_LOAD: os << "PROGRAM_LOAD"; break;
        case elf::program_type::PROGRAM_DYNAMIC: os << "PROGRAM_DYNAMIC"; break;
        case elf::program_type::PROGRAM_INTERP: os << "SECTION_STRTAB"; break;
        case elf::program_type::PROGRAM_NOTE: os << "PROGRAM_NOTE"; break;
        case elf::program_type::PROGRAM_SHLIB: os << "PROGRAM_SHLIB"; break;
        case elf::program_type::PROGRAM_PHDR: os << "PROGRAM_PHDR"; break;
        case elf::program_type::PROGRAM_TLS: os << "PROGRAM_TLS"; break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::program_flags& flags) {
    bool has = false;
    FLAG_BIT_DEBUG(flags.bits.execute, "EXECUTE");
    FLAG_BIT_DEBUG(flags.bits.write, "WRITE");
    FLAG_BIT_DEBUG(flags.bits.read, "READ");

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::section_type& type) {
    switch (type) {
        case elf::section_type::SECTION_NONE: os << "SECTION_NONE"; break;
        case elf::section_type::SECTION_PROGBITS: os << "SECTION_PROGBITS"; break;
        case elf::section_type::SECTION_SYMTAB: os << "SECTION_SYMTAB"; break;
        case elf::section_type::SECTION_STRTAB: os << "SECTION_STRTAB"; break;
        case elf::section_type::SECTION_RELA: os << "SECTION_RELA"; break;
        case elf::section_type::SECTION_HASH: os << "SECTION_HASH"; break;
        case elf::section_type::SECTION_DYNAMIC: os << "SECTION_DYNAMIC"; break;
        case elf::section_type::SECTION_NOTE: os << "SECTION_NOTE"; break;
        case elf::section_type::SECTION_NOBITS: os << "SECTION_NOBITS"; break;
        case elf::section_type::SECTION_REL: os << "SECTION_REL"; break;
        case elf::section_type::SECTION_SHLIB: os << "SECTION_SHLIB"; break;
        case elf::section_type::SECTION_DYNSYM: os << "SECTION_DYNSYM"; break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::section_flags& flags) {
    bool has = false;
    FLAG_BIT_DEBUG(flags.bits.write, "WRITE");
    FLAG_BIT_DEBUG(flags.bits.alloc, "ALLOC");
    FLAG_BIT_DEBUG(flags.bits.exec_instr, "EXECINSTR");
    FLAG_BIT_DEBUG(flags.bits.rela_livepatch, "RELA_LIVEPATCH");
    FLAG_BIT_DEBUG(flags.bits.ro_after_init, "RO_AFTER_INIT");

    return os;
}

std::ostream& operator<<(std::ostream& os, const elf::section_flags64& flags) {
    os << flags.low;

    return os;
}
