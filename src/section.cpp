
#include <cstring>
#include "section.h"


namespace elf {

section::section(const image_headers& image, const section_header64* header)
    : m_image(image)
    , m_header(header) {
}

size_t section::name_offset() const {
    return m_header->name;
}

section_type section::type() const {
    return m_header->type;
}

section_flags64 section::flags() const {
    return m_header->flags;
}

const void* section::data() const {
    return m_image.base() + m_header->offset;
}

name_section::name_section(const image_headers& image, const section_header64* header)
    : section(image, header)
    , m_str_table(reinterpret_cast<const char*>(image.base() + header->offset)) {

}

const char* name_section::operator[](size_t index) const {
    return m_str_table + index;
}

image_sections::iterator::iterator(const image_headers& image, const section_header64* header)
        : m_image(image)
        , m_header(header)
{}

image_sections::iterator& image_sections::iterator::operator++() {
    m_header++;
    return *this;
}
image_sections::iterator& image_sections::iterator::operator--() {
    m_header--;
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
        , m_headers(image.section_headers())
        , m_name_section(image, header(image.name_section_index()))
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
    return section(m_image, header(index));
}

image_sections::iterator image_sections::begin() const {
    return iterator(m_image, m_headers);
}
image_sections::iterator image_sections::end() const {
    return iterator(m_image, m_headers + count());
}

const section_header64* image_sections::header(size_t index) const {
    return m_headers + index;
}

}
