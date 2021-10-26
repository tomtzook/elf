
#include <cstring>
#include "program.h"


namespace elf {

program::program(const image_headers& image, const void* header)
        : m_image(image)
        , m_header32(reinterpret_cast<const program_header32*>(header))
        , m_header64(reinterpret_cast<const program_header64*>(header)) {
}

program_type program::type() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_header32->type;
        case FILE_CLASS_CLASS64: return m_header64->type;
        default: throw std::exception();
    }
}

program_flags program::flags() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_header32->flags;
        case FILE_CLASS_CLASS64: return m_header64->flags;
        default: throw std::exception();
    }
}

size_t program::size() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_header32->size_in_file;
        case FILE_CLASS_CLASS64: return m_header64->size_in_file;
        default: throw std::exception();
    }
}

const void* program::data() const {
    switch (m_image.identification().fclass) {
        case FILE_CLASS_CLASS32: return m_image.base() + m_header32->offset;
        case FILE_CLASS_CLASS64: return m_image.base() + m_header64->offset;
        default: throw std::exception();
    }
}

image_programs::iterator::iterator(const image_headers& image, const void* header)
        : m_image(image)
        , m_header(reinterpret_cast<const uint8_t*>(header))
{}

image_programs::iterator& image_programs::iterator::operator++() {
    m_header += m_image.program_header_size();
    return *this;
}
image_programs::iterator& image_programs::iterator::operator--() {
    m_header -= m_image.program_header_size();
    return *this;
}

image_programs::iterator::reference image_programs::iterator::operator*() {
    return {m_image, m_header};
}
image_programs::iterator::pointer image_programs::iterator::operator->() {
    return {m_image, m_header};
}

bool image_programs::iterator::operator==(const iterator& rhs) {
    return m_header == rhs.m_header;
}
bool image_programs::iterator::operator!=(const iterator& rhs) {
    return m_header != rhs.m_header;
}

image_programs::image_programs(const image_headers& image)
        : m_image(image)
        , m_headers(reinterpret_cast<const uint8_t*>(image.program_headers()))
{}

size_t image_programs::count() const {
    return m_image.program_count();
}

program image_programs::operator[](size_t index) const {
    return {m_image, m_headers + (index * m_image.program_header_size())};
}

image_programs::iterator image_programs::begin() const {
    return {m_image, m_headers};
}
image_programs::iterator image_programs::end() const {
    return {m_image, m_headers + (count() * m_image.program_header_size())};
}

}
