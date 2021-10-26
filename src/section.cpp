
#include <cstring>
#include "section.h"


namespace elf {

section::section(const image_headers& image, const void* header)
    : m_image(image)
    , m_header32(reinterpret_cast<const section_header32*>(header))
    , m_header64(reinterpret_cast<const section_header64*>(header)) {
}

size_t section::name_offset() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_header32->name;
        case FILE_CLASS_CLASS64: return m_header64->name;
        default: throw std::exception();
    }
}

section_type section::type() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_header32->type;
        case FILE_CLASS_CLASS64: return m_header64->type;
        default: throw std::exception();
    }
}

section_flags section::flags() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_header32->flags;
        case FILE_CLASS_CLASS64: return m_header64->flags.low;
        default: throw std::exception();
    }
}

size_t section::size() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_header32->size;
        case FILE_CLASS_CLASS64: return m_header64->size;
        default: throw std::exception();
    }
}

const void* section::data() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_image.base() + m_header32->offset;
        case FILE_CLASS_CLASS64: return m_image.base() + m_header64->offset;
        default: throw std::exception();
    }
}

name_section::name_section(const image_headers& image, const void* header)
    : section(image, header)
    , m_str_table(data<char>()) {

}

const char* name_section::operator[](size_t index) const {
    return m_str_table + index;
}

image_sections::iterator::iterator(const image_headers& image, const void* header)
        : m_image(image)
        , m_header(reinterpret_cast<const uint8_t*>(header))
{}

image_sections::iterator& image_sections::iterator::operator++() {
    m_header += m_image.section_header_size();
    return *this;
}
image_sections::iterator& image_sections::iterator::operator--() {
    m_header -= m_image.section_header_size();
    return *this;
}

image_sections::iterator::reference image_sections::iterator::operator*() {
    return {m_image, m_header};
}
image_sections::iterator::pointer image_sections::iterator::operator->() {
    return {m_image, m_header};
}

bool image_sections::iterator::operator==(const iterator& rhs) {
    return m_header == rhs.m_header;
}
bool image_sections::iterator::operator!=(const iterator& rhs) {
    return m_header != rhs.m_header;
}

image_sections::image_sections(const image_headers& image)
        : m_image(image)
        , m_headers(reinterpret_cast<const uint8_t*>(image.section_headers()))
        , m_name_section(image, m_headers + (image.name_section_index() * m_image.section_header_size()))
{}

size_t image_sections::count() const {
    return m_image.section_count();
}

const name_section& image_sections::names() const {
    return m_name_section;
}

section image_sections::operator[](const char* name) const {
    for(const auto& section : *this) {
        if (0 == strcmp(name, m_name_section[section.name_offset()])) {
            return section;
        }
    }

    throw section_not_found_exception(name);
}

section image_sections::operator[](size_t index) const {
    return {m_image, m_headers + (index * m_image.section_header_size())};
}

image_sections::iterator image_sections::begin() const {
    return {m_image, m_headers};
}
image_sections::iterator image_sections::end() const {
    return {m_image, m_headers + (count() * m_image.section_header_size())};
}

}
