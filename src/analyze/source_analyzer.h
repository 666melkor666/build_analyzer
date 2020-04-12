#pragma once

#include "analyze/analyzer.h"

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace build_analyzer
{
namespace analyze
{
class SourceAnalyzer : public Analyzer
{
public:
    events::EventType supportedEvent() const override;
    void add(events::Event event) override;
    void print(std::ostream& output) const override;

private:
    struct Data;
    struct PrintData
    {
        PrintData(Data const* data, char const* value)
            : data_{data}
            , value_{value}
        {}

        Data const* data_;
        char const* value_;
    };

    std::vector<PrintData> getSortedData() const;

private:
    struct Data
    {
        Data() = default;

        std::uint64_t duration_ = 0;
        std::uint64_t count_ = 0;
    };

    std::unordered_map<std::string, Data> statistics_;
};
} // namespace analyze
} // namespace build_analyzer
