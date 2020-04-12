#pragma once

#include "events/event_type.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace build_analyzer
{
struct Config;

namespace events
{
struct Event;
} // namespace events

namespace analyze
{
class Analyzer;

class BuildAnalyzer
{
public:
    BuildAnalyzer(Config const& config);
    ~BuildAnalyzer();

public:
    void add(events::Event event);
    void print(std::string const& outputDir) const;

private:
    template<typename T>
    void registerAnalyzer();

private:
    std::unordered_map<events::EventType, std::unique_ptr<Analyzer>> analyzers_;
};
} // namespace analyze
} // namespace build_analyzer
