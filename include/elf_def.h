#pragma once

#include <cstdint>
#include <cstddef>


namespace elf {

#pragma pack(push, 1)

enum file_class : uint8_t {
    FILE_CLASS_NONE = 0,
    FILE_CLASS_CLASS32 = 1,
    FILE_CLASS_CLASS64 = 2
};

enum data_encoding : uint8_t {
    ENCODING_NONE = 0,
    ENCODING_LSB = 1,
    ENCODING_MSB = 2
};

union file_identification {
    static constexpr size_t SIZE = 16;
    static constexpr const char* MAGIC = "\177ELF";
    static constexpr size_t MAGIC_SIZE = 4;

    uint8_t all[SIZE];
    struct {
        uint8_t magic[MAGIC_SIZE];
        file_class fclass;
        data_encoding data;
        uint8_t version;
    };
};
static_assert(sizeof(file_identification) == file_identification::SIZE, "identification size");

enum file_type : uint16_t {
    FILE_TYPE_NONE = 0,
    FILE_TYPE_REL = 1,
    FILE_TYPE_EXEC = 2,
    FILE_TYPE_DYN = 3,
    FILE_TYPE_CORE = 4
};

enum machine_type : uint16_t {
    MACHINE_NONE = 0,
    MACHINE_M32 = 1,
    MACHINE_SPARC = 2,
    MACHINE_INTEL386 = 3,
    MACHINE_MOTOROLA68K = 4,
    MACHINE_MOTOROLA88K = 5,
    MACHINE_INTEL486 = 6, /* Perhaps disused */
    MACHINE_INTEL860 = 7,
    MACHINE_MIPS = 8,	/* MIPS R3000 (officially, big-endian only) */
    /* Next two are historical and binaries and
       modules of these types will be rejected by
       Linux.  */
    MACHINE_MIPSRS3LE = 10,	/* MIPS R3000 little-endian */
    MACHINE_MIPSRS4BE = 10,	/* MIPS R4000 big-endian */

    MACHINE_PARISC = 15,	/* HPPA */
    MACHINE_SPARC32PLUS = 18,	/* Sun's "v8plus" */
    MACHINE_PPC = 20,	/* PowerPC */
    MACHINE_PPC64 = 21,	 /* PowerPC64 */
    MACHINE_SPU = 23,	/* Cell BE SPU */
    MACHINE_ARM = 40,	/* ARM 32 bit */
    MACHINE_SH = 42,	/* SuperH */
    MACHINE_SPARCV9 = 43,	/* SPARC v9 64-bit */
    MACHINE_H8300 = 46,	/* Renesas H8/300 */
    MACHINE_IA64 = 50,	/* HP/Intel IA-64 */
    MACHINE_X8664 = 62,	/* AMD x86-64 */
    MACHINE_S390 = 22,	/* IBM S/390 */
    MACHINE_CRIS = 76,	/* Axis Communications 32-bit embedded processor */
    MACHINE_M32R = 88,	/* Renesas M32R */
    MACHINE_MN10300 = 89,	/* Panasonic/MEI MN10300, AM33 */
    MACHINE_OPENRISC = 92,     /* OpenRISC 32-bit embedded processor */
    MACHINE_ARCOMPACT = 93,	/* ARCompact processor */
    MACHINE_XTENSA = 94,	/* Tensilica Xtensa Architecture */
    MACHINE_BLACKFIN = 106,     /* ADI Blackfin Processor */
    MACHINE_UNICORE = 110,	/* UniCore-32 */
    MACHINE_ALTERANIOS2 = 113,	/* Altera Nios II soft-core processor */
    MACHINE_TIC6000 = 140,	/* TI C6X DSPs */
    MACHINE_HEXAGON = 164,	/* QUALCOMM Hexagon */
    MACHINE_NDS32 = 167,	/* Andes Technology compact code size
				   embedded RISC processor family */
    MACHINE_AARCH64 = 183,	/* ARM 64 bit */
    MACHINE_TILEPRO = 188,	/* Tilera TILEPro */
    MACHINE_MICROBLAZE = 189,	/* Xilinx MicroBlaze */
    MACHINE_TILEGX = 191,	/* Tilera TILE-Gx */
    MACHINE_ARCV2 = 195,	/* ARCv2 Cores */
    MACHINE_RISCV = 243,	/* RISC-V */
    MACHINE_BPF = 247,	/* Linux BPF - in-kernel virtual machine */
    MACHINE_CSKY = 252,	/* C-SKY */
    MACHINE_FRV = 0x5441,	/* Fujitsu FR-V */
};

struct header32 {
    file_identification identification;
    file_type type;
    uint16_t machine;
    uint32_t version;
    uint32_t entry_address;
    uint32_t program_header_offset;
    uint32_t section_header_offset;
    uint32_t flags;
    uint16_t header_size;
    uint16_t program_header_entry_size;
    uint16_t program_header_count;
    uint16_t section_header_entry_size;
    uint16_t section_header_count;
    uint16_t name_section_index;
};

struct header64 {
    file_identification identification;
    file_type type;
    machine_type machine;
    uint32_t version;
    uint64_t entry_address;
    uint64_t program_header_offset;
    uint64_t section_header_offset;
    uint32_t flags;
    uint16_t header_size;
    uint16_t program_header_entry_size;
    uint16_t program_header_count;
    uint16_t section_header_entry_size;
    uint16_t section_header_count;
    uint16_t name_section_index;
};

enum program_type : uint32_t {
    PROGRAM_NONE = 0,
    PROGRAM_LOAD = 1,
    PROGRAM_DYNAMIC = 2,
    PROGRAM_INTERP = 3,
    PROGRAM_NOTE = 4,
    PROGRAM_SHLIB = 5,
    PROGRAM_PHDR = 6,
    PROGRAM_TLS = 7
};

struct program_header32 {
    program_type type;
    uint32_t offset;
    uint32_t virtual_address;
    uint32_t physical_address;
    uint32_t size_in_file;
    uint32_t size_in_memory;
    uint32_t flags;
    uint32_t align;
};

struct program_header64 {
    program_type type;
    uint32_t flags;
    uint64_t offset;
    uint64_t virtual_address;
    uint64_t physical_address;
    uint64_t size_in_file;
    uint64_t size_in_memory;
    uint64_t align;
};

enum section_type : uint32_t {
    SECTION_NONE = 0,
    SECTION_PROGBITS = 1,
    SECTION_SYMTAB = 2,
    SECTION_STRTAB = 3,
    SECTION_RELA = 4,
    SECTION_HASH = 5,
    SECTION_DYNAMIC = 6,
    SECTION_NOTE = 7,
    SECTION_NOBITS = 8,
    SECTION_REL = 9,
    SECTION_SHLIB = 10,
    SECTION_DYNSYM = 11
};

enum section_flag : uint32_t {
    SECTION_FLAGS_WRITE = 0x1,
    SECTION_FLAGS_ALLOC = 0x2,
    SECTION_FLAGS_EXECINSTR = 0x4,
    SECTION_FLAGS_RELA_LIVEPATCH = 0x00100000,
    SECTION_FLAGS_RO_AFTER_INIT = 0x00200000
};

union section_flags32 {
    uint32_t data;
    struct {
        uint32_t write : 1;
        uint32_t alloc : 1;
        uint32_t exec_instr : 1;
        uint32_t reserved0 : 16;
        uint32_t rela_livepatch : 1;
        uint32_t ro_after_init : 1;
    };
};
static_assert(sizeof(section_flags32) == 4, "section_flags32 size");

union section_flags64 {
    uint64_t data;
    struct {
        section_flags32 low;
        uint32_t high : 32;
    } ;
};
static_assert(sizeof(section_flags64) == 8, "section_flags64 size");

struct section_header32 {
    uint32_t name;
    section_type type;
    section_flags32 flags;
    uint32_t address;
    uint32_t offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t alignment;
    uint32_t entry_size;
};

struct section_header64 {
    uint32_t name;
    section_type type;
    section_flags64 flags;
    uint64_t address;
    uint64_t offset;
    uint64_t size;
    uint32_t link;
    uint32_t info;
    uint64_t alignment;
    uint64_t entry_size;
};

#pragma pack(pop)

}
