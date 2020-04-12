#pragma once

#include "analyze/analyzer.h"

#include "events/event_type.h"
#include "events/event.h"

#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"

#include <algorithm>
#include <ostream>
#include <unordered_map>
#include <vector>

namespace build_analyzer
{
namespace analyze
{
template<events::EventType type>
class ValuelessAnalyzer final: public Analyzer
{
public:
    ValuelessAnalyzer() = default;

public:
    events::EventType supportedEvent() const override
    {
        return type;
    }

    void add(events::Event event) override
    {
        data_.duration_ += event.duration_;
        ++data_.count_;
    }

    void print(std::ostream& output) const override
    {
        rapidjson::OStreamWrapper outputStream{output};
        rapidjson::Writer<rapidjson::OStreamWrapper> document{outputStream};

        document.StartObject();
        document.Key("eventType");
        document.String(events::toString(supportedEvent()).c_str());

        document.Key("statistics");
        document.StartArray();

        document.StartObject();

        document.Key("duration");
        document.String(std::to_string(data_.duration_).c_str());

        document.Key("count");
        document.String(std::to_string(data_.count_).c_str());

        document.EndObject();

        document.EndArray();
        document.EndObject();
    }

private:
    struct Data
    {
        Data() = default;

        std::uint64_t duration_ = 0;
        std::uint64_t count_ = 0;
    } data_;
};
} // namespace analyze
} // namespace build_analyzer
