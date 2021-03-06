#pragma once

#include <cstddef>
#include <iterator>

#include "elf_def.h"
#include "elf_base.h"


namespace elf {

class section {
public:
    section(const image_headers& image, const void* header);

    size_t name_offset() const;
    section_type type() const;
    section_flags flags() const;
    size_t size() const;

    const void* data() const;
    template<typename T>
    const T* data() const {
        return reinterpret_cast<const T*>(data());
    }

private:
    const image_headers& m_image;
    const section_header32* m_header32;
    const section_header64* m_header64;
};

class name_section : public section {
public:
    name_section(const image_headers& image, const void* header);

    const char* operator[](size_t index) const;

private:
    const char* m_str_table;
};

class image_sections {
public:
    class iterator {
    public:
        using value_type = section;
        using reference = section;
        using pointer = section;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator(const image_headers& image, const void* header);

        iterator& operator++();
        iterator& operator--();

        reference operator*();
        pointer operator->();

        bool operator==(const iterator& rhs);
        bool operator!=(const iterator& rhs);

    private:
        const image_headers& m_image;
        const uint8_t * m_header;
    };

    explicit image_sections(const image_headers& image);

    size_t count() const;

    const name_section& names() const;

    section operator[](const char* name) const;
    section operator[](size_t index) const;

    iterator begin() const;
    iterator end() const;

private:
    const image_headers& m_image;
    const uint8_t* m_headers;
    class name_section m_name_section;
};

}
