#pragma once

#include <string>
#include <fstream>

namespace build_analyzer
{
namespace file_system
{
class FileReader
{
public:
    FileReader() = default;

public:
    std::string read(std::string const& path) const;

private:
    mutable std::string buffer_;
    mutable std::fstream file_;
};
} // namespace file_system
} // namespace build_analyzer
