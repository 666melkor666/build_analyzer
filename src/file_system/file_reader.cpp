#include "file_system/file_reader.h"

#include <filesystem>
#include <fstream>

namespace build_analyzer
{
namespace file_system
{
std::string FileReader::read(std::string const& path) const
{
    auto const size = std::filesystem::file_size(path);

    buffer_.resize(size + 1);

    file_.open(path);
    file_.read(buffer_.data(), size);
    buffer_[size] = '\0';
    file_.close();

    return buffer_;
}
} // namespace file_system
} // namespace build_analyzer
