
#include "elf_base.h"


namespace elf {

image_headers::image_headers(const void* base)
    : m_base(reinterpret_cast<const uint8_t*>(base))
    , m_id(reinterpret_cast<const file_identification*>(m_base))
    , m_header32(reinterpret_cast<const header32*>(m_base))
    , m_header64(reinterpret_cast<const header64*>(m_base)) {
    check_headers();
}

const uint8_t* image_headers::base() const {
    return m_base;
}

file_identification image_headers::identification() const {
    return *m_id;
}

machine_type image_headers::machine() const {
    switch (m_id->fclass) {
        case FILE_CLASS_CLASS32: return m_header32->machine;
        case FILE_CLASS_CLASS64: return m_header64->machine;
        default: throw std::exception();
    }
}

const void* image_headers::program_headers() const {
    switch (m_id->fclass) {
        case FILE_CLASS_CLASS32: return m_base + m_header32->program_header_offset;
        case FILE_CLASS_CLASS64: return m_base + m_header64->program_header_offset;
        default: throw std::exception();
    }
}

size_t image_headers::program_count() const {
    switch (m_id->fclass) {
        case FILE_CLASS_CLASS32: return m_header32->program_header_count;
        case FILE_CLASS_CLASS64: return m_header64->program_header_count;
        default: throw std::exception();
    }
}

size_t image_headers::program_header_size() const {
    switch (m_id->fclass) {
        case FILE_CLASS_CLASS32: return m_header32->program_header_entry_size;
        case FILE_CLASS_CLASS64: return m_header64->program_header_entry_size;
        default: throw std::exception();
    }
}

const void* image_headers::section_headers() const {
    switch (m_id->fclass) {
        case FILE_CLASS_CLASS32: return m_base + m_header32->section_header_offset;
        case FILE_CLASS_CLASS64: return m_base + m_header64->section_header_offset;
        default: throw std::exception();
    }
}

size_t image_headers::section_count() const {
    switch (m_id->fclass) {
        case FILE_CLASS_CLASS32: return m_header32->section_header_count;
        case FILE_CLASS_CLASS64: return m_header64->section_header_count;
        default: throw std::exception();
    }
}

size_t image_headers::section_header_size() const {
    switch (m_id->fclass) {
        case FILE_CLASS_CLASS32: return m_header32->section_header_entry_size;
        case FILE_CLASS_CLASS64: return m_header64->section_header_entry_size;
        default: throw std::exception();
    }
}

size_t image_headers::name_section_index() const {
    switch (m_id->fclass) {
        case FILE_CLASS_CLASS32: return m_header32->name_section_index;
        case FILE_CLASS_CLASS64: return m_header64->name_section_index;
        default: throw std::exception();
    }
}

void image_headers::check_headers() {

}

}
