#pragma once

#include "elf_def.h"
#include "elf_base.h"
#include "program.h"
#include "section.h"


namespace elf {

class image {
public:
    explicit image(const void* base);

    const image_headers& headers() const;

    image_programs& programs();
    image_sections& sections();

private:
    image_headers m_headers;
    image_programs m_programs;
    image_sections m_sections;
};

}
