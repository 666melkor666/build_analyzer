#pragma once

#include <string>
#include <iosfwd>

namespace build_analyzer
{
struct Config
{
    std::string timeTraceFilesPath;
    std::string outputDir = "./";
    bool collectSources = false;
    bool collectFrontend = false;
    bool collectBackend = false;
    bool collectParseTemplates = false;
    bool collectParseClass = false;
    bool collectInstantiateClass = false;
    bool collectInstantiateFunction = false;
    bool collectOptFunction = false;
    bool collectOptModule = false;
    bool collectCodeGenFunction = false;
};

Config parse(char const* const* args, std::size_t count);
void printHelp(std::ostream& output);

} // namespace build_analyzer
