
#include "elf.h"


namespace elf {

image::image(const void* base)
    : m_headers(base)
    , m_programs(m_headers)
    , m_sections(m_headers) {

}

const image_headers& image::headers() const {
    return m_headers;
}

image_programs& image::programs() {
    return m_programs;
}

image_sections& image::sections() {
    return m_sections;
}

}
