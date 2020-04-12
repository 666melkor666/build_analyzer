#include "analyze/build_analyzer.h"

#include "analyze/source_analyzer.h"
#include "analyze/total_analyzer.h"
#include "analyze/valueless_analyzer.h"

#include "events/event.h"
#include "events/event_type.h"

#include "config.h"

#include "Demangle.h"

#include <filesystem>
#include <fstream>

namespace build_analyzer
{
namespace analyze
{
namespace
{
struct FunctionNameDemangler
{
    std::string operator()(std::string value) const
    {
        return llvm::demangle(value);
    }
};
} // namespace unnamed

BuildAnalyzer::BuildAnalyzer(Config const& config)
{
    using events::EventType;

    if(config.collectSources)
        registerAnalyzer<SourceAnalyzer>();
    if(config.collectFrontend)
        registerAnalyzer<ValuelessAnalyzer<EventType::Frontend>>();
    if(config.collectBackend)
        registerAnalyzer<ValuelessAnalyzer<EventType::Backend>>();
    if(config.collectParseTemplates)
        registerAnalyzer<TotalAnalyzer<EventType::ParseTemplate>>();
    if(config.collectParseClass)
        registerAnalyzer<TotalAnalyzer<EventType::ParseClass>>();
    if(config.collectInstantiateClass)
        registerAnalyzer<TotalAnalyzer<EventType::InstantiateClass>>();
    if(config.collectInstantiateFunction)
        registerAnalyzer<TotalAnalyzer<EventType::InstantiateFunction>>();
    if(config.collectOptFunction)
        registerAnalyzer<TotalAnalyzer<EventType::OptFunction, FunctionNameDemangler>>();
    if(config.collectOptModule)
        registerAnalyzer<TotalAnalyzer<EventType::OptModule>>();
    if(config.collectCodeGenFunction)
        registerAnalyzer<TotalAnalyzer<EventType::CodeGenFunction>>();
}

BuildAnalyzer::~BuildAnalyzer() = default;

template<typename T>
void BuildAnalyzer::registerAnalyzer()
{
    auto analyzer = std::make_unique<T>();
    auto const eventType = analyzer->supportedEvent();

    analyzers_.emplace(eventType, std::move(analyzer));
}

void BuildAnalyzer::add(events::Event event)
{
    auto analyzer = analyzers_.find(event.type_);
    if(analyzer == std::end(analyzers_))
        return;

    analyzer->second->add(std::move(event));
}

void BuildAnalyzer::print(std::string const& outputDir) const
{
    std::filesystem::create_directories(outputDir);

    for(auto const&[_, analyzer] : analyzers_)
    {
        auto const path = outputDir + "/" + events::toString(analyzer->supportedEvent()) + ".json";
        std::ofstream statisticsFile{path};
        analyzer->print(statisticsFile);
    }
}
} // namespace analyze
} // namespace build_analyzer
