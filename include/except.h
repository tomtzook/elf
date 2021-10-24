#pragma once

#include <stdexcept>


namespace elf {

class exception : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "ELF Exception";
    }
};

class name_not_found_exception : public exception {
public:
    explicit name_not_found_exception(const char* name)
            : m_name(name)
    {}

    const char* name() const {
        return m_name;
    }

    virtual const char* what() const noexcept override {
        return "Name not found";
    }

private:
    const char* m_name;
};

class section_not_found_exception : public name_not_found_exception {
public:
    explicit section_not_found_exception(const char* name)
            : name_not_found_exception(name)
    {}

    virtual const char* what() const noexcept override {
        return "Section not found";
    }
};

}
