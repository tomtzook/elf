
#include "elf.h"


namespace elf {

image::image(const void* base)
    : m_headers(base)
    , m_sections(m_headers) {

}

const image_headers& image::headers() const {
    return m_headers;
}

image_sections& image::sections() {
    return m_sections;
}

}
