#pragma once

#include "elf_def.h"
#include "elf_base.h"


namespace elf {

class program {
public:
    program(const image_headers& image, const void* header);

    program_type type() const;
    program_flags flags() const;
    size_t size() const;

    const void* data() const;
    template<typename T>
    const T* data() const {
        return reinterpret_cast<const T*>(data());
    }

private:
    const image_headers& m_image;
    const program_header32* m_header32;
    const program_header64* m_header64;
};

class image_programs {
public:
    class iterator {
    public:
        using value_type = program;
        using reference = program;
        using pointer = program;
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
        const uint8_t* m_header;
    };

    explicit image_programs(const image_headers& image);

    size_t count() const;

    program operator[](size_t index) const;

    iterator begin() const;
    iterator end() const;

private:
    const image_headers& m_image;
    const uint8_t* m_headers;
};

}
