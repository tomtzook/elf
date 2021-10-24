
#include "elf_base.h"


namespace elf {

image_headers::image_headers(const void* base)
    : m_base(reinterpret_cast<const uint8_t*>(base))
    , m_header(reinterpret_cast<const header64*>(m_base)) {
    check_headers();
}

const uint8_t* image_headers::base() const {
    return m_base;
}

const section_header64* image_headers::section_headers() const {
    return reinterpret_cast<const section_header64*>(m_base + m_header->section_header_offset);
}

size_t image_headers::section_count() const {
    return m_header->section_header_count;
}

size_t image_headers::name_section_index() const {
    return m_header->name_section_index;
}

void image_headers::check_headers() {

}

}
