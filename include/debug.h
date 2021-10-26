#pragma once

#include <ostream>

#include "elf_def.h"
#include "elf_base.h"
#include "elf.h"
#include "program.h"
#include "section.h"


std::ostream& operator<<(std::ostream& os, const elf::file_class& file_class);
std::ostream& operator<<(std::ostream& os, const elf::data_encoding& data_encoding);
std::ostream& operator<<(std::ostream& os, const elf::file_identification& file_identification);
std::ostream& operator<<(std::ostream& os, const elf::file_type& file_type);
std::ostream& operator<<(std::ostream& os, const elf::machine_type& type);
std::ostream& operator<<(std::ostream& os, const elf::image_headers& headers);
std::ostream& operator<<(std::ostream& os, const elf::image& image);

std::ostream& operator<<(std::ostream& os, const elf::program_type& type);
std::ostream& operator<<(std::ostream& os, const elf::program_flags& flags);

std::ostream& operator<<(std::ostream& os, const elf::section_type& type);
std::ostream& operator<<(std::ostream& os, const elf::section_flags& flags);
std::ostream& operator<<(std::ostream& os, const elf::section_flags64& flags);

