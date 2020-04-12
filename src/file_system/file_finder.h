#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <optional>

namespace build_analyzer
{
namespace file_system
{
class FileFinder
{
public:
    FileFinder(std::string const& path)
        : iterator_{path}
    {}

public:
    std::optional<std::string> next();

    template<typename Predicate>
    std::optional<std::string> next(Predicate predicate);

private:
    std::filesystem::recursive_directory_iterator iterator_;
};

template<typename Predicate>
std::optional<std::string> FileFinder::next(Predicate predicate)
{
    auto filter = [predicate](auto const& entry)
    {
        return std::filesystem::is_regular_file(entry.path())
            && predicate(entry.path());
    };

    std::filesystem::recursive_directory_iterator end{};
    iterator_ = std::find_if(iterator_, end, filter);

    if(iterator_ == end)
        return std::nullopt;

    auto result = iterator_->path();
    ++iterator_;

    return result;
}

std::optional<std::string> FileFinder::next()
{
    return next([](auto const&){ return true; });
}
} // namespace file_system
} // namespace build_analyzer
