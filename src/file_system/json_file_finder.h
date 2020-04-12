#pragma once

#include "file_system/file_finder.h"

#include <filesystem>
#include <optional>
#include <string>

namespace build_analyzer
{
namespace file_system
{
class JsonFileFinder
{
public:
    JsonFileFinder(std::string const& path)
        : finder_{path}
    {}

public:
    std::optional<std::string> next()
    {
        auto isJson = [](std::filesystem::path const& path)
        {
            return path.extension().string() == ".json";
        };

        return finder_.next(isJson);
    }
private:
    FileFinder finder_;
};
} // namespace file_system
} // namespace build_analyzer
