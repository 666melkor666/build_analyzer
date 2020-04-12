#include "config.h"

#include <cassert>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <string_view>

namespace build_analyzer
{
namespace
{
std::string_view const all{ "--all" };
std::string_view const timeTraseFilesPath{ "--timeTraceFilesPath" };
std::string_view const collectSources{ "--collectSources" };
std::string_view const collectFrontend{ "--collectFrontend" };
std::string_view const collectBackend{ "--collectBackend" };
std::string_view const collectParseTemplates{ "--collectParseTemplates" };
std::string_view const collectParseClass{ "--collectParseClass" };
std::string_view const collectInstantiateClass{ "--collectInstantiateClass" };
std::string_view const collectInstantiateFunction{ "--collectInstantiateFunction" };
std::string_view const collectOptFunction{ "--collectOptFunction" };
std::string_view const collectOptModule{ "--collectOptModule" };
std::string_view const collectCodeGenFunction{ "--collectCodeGenFunction" };
std::string_view const outputDir{"--outputDir"};

void turnOnAllOptions(Config& config)
{
    config.collectSources = true;
    config.collectFrontend = true;
    config.collectBackend = true;
    config.collectParseTemplates = true;
    config.collectParseClass = true;
    config.collectInstantiateClass = true;
    config.collectInstantiateFunction = true;
    config.collectOptFunction = true;
    config.collectOptModule = true;
    config.collectCodeGenFunction = true;
}

std::string extractPath(std::string_view pathOption)
{
    auto assignPos = pathOption.find('=');
    if(assignPos == std::string::npos)
    {
        std::string error = "Bad path to time trace files: ";
        error += pathOption;
        throw std::invalid_argument{error};
    }

    auto path = pathOption.substr(assignPos + 1);
    if(path.empty())
        throw std::invalid_argument{"Empty path to time trace files" };

    std::string result;
    result = path;
    return result;
}

void setTimeTraceFilesPath(std::string_view pathOption, Config& result)
{
    result.timeTraceFilesPath = extractPath(pathOption);
}

void setOutputDir(std::string_view pathOption, Config& result)
{
    result.outputDir = extractPath(pathOption);
}

bool startsWith(std::string_view lhs, std::string_view rhs)
{
    auto pos = lhs.find(rhs);

    return pos == 0;
}

void processOption(char const* option, Config& config)
{
    assert(option);

    if(all == option)
        turnOnAllOptions(config);
    else if(startsWith(option, timeTraseFilesPath))
        setTimeTraceFilesPath(option, config);
    else if(collectSources == option)
        config.collectSources = true;
    else if(collectFrontend == option)
        config.collectFrontend = true;
    else if(collectBackend == option)
        config.collectBackend = true;
    else if(collectParseTemplates == option)
        config.collectParseTemplates = true;
    else if(collectParseClass == option)
        config.collectParseClass = true;
    else if(collectInstantiateClass == option)
        config.collectInstantiateClass = true;
    else if(collectInstantiateFunction == option)
        config.collectInstantiateFunction = true;
    else if(collectOptFunction == option)
        config.collectOptFunction = true;
    else if(collectOptModule == option)
        config.collectOptModule = true;
    else if(collectCodeGenFunction == option)
        config.collectCodeGenFunction = true;
    else if(startsWith(option, outputDir))
        setOutputDir(option, config);
    else
    	throw std::invalid_argument{"Unsupported option: " + std::string{option}};
}
} // namespace unnamed

void printHelp(std::ostream& output)
{
	output << "--help - prints help\n"
		   << timeTraseFilesPath << "=<path> - a path to the folder which contains clang time-report files\n"
		   << outputDir << "=<path> - a path for analysis output\n"
		   << all << " - collects all possible statistics\n"
		   << collectSources << " - collects statistics for 'Source' events\n"
		   << collectFrontend << " - collects statistics for 'Frontend' events\n"
		   << collectBackend << " - collects statistics for 'Backend' events\n"
		   << collectParseTemplates << " - collects statistics for 'ParseTemplates' events\n"
		   << collectParseClass << " - collects statistics for 'ParseClass' events\n"
		   << collectInstantiateClass << " - collects statistics for 'InstantiateClass' events\n"
		   << collectInstantiateFunction << " - collects statistics for 'InstantiateFunction' events\n"
		   << collectOptFunction << " - collects statistics for 'OptFunction' events\n"
		   << collectOptModule << " - collects statistics for 'OptModule' events\n"
		   << collectCodeGenFunction << " - collects statistics for 'CodeGenFunction' events\n";
}

Config parse(char const* const* args, std::size_t count)
{
    Config result;

    for(std::size_t i = 1; i < count; ++i)
        processOption(args[i], result);

    return result;
}
} // namespace build_analyzer
