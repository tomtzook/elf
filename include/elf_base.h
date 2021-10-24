#pragma once

#include "elf_def.h"
#include "except.h"

namespace elf {

class image_headers {
public:
    explicit image_headers(const void* base);

    const uint8_t* base() const;

    file_identification identification() const;
    machine_type machine() const;

    const section_header64* section_headers() const;
    size_t section_count() const;
    size_t name_section_index() const;

private:
    void check_headers();

    const uint8_t* m_base;
    const header64* m_header;
};

}
