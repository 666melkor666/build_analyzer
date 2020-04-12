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
struct DummyValueProcessor
{
    std::string operator()(std::string value) const
    {
        return value;
    }
};

template<events::EventType type, typename ValueProcessor = DummyValueProcessor>
class TotalAnalyzer final: public Analyzer
{
public:
    TotalAnalyzer() = default;

public:
    events::EventType supportedEvent() const override
    {
        return type;
    }

    void add(events::Event event) override
    {
        auto& data = statistics_[ValueProcessor{}(std::move(event.value_))];

        data.duration_ += event.duration_;
        ++data.count_;
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

        auto sortedData = getSortedData();

        for(auto const& element : sortedData)
        {
            document.StartObject();

            document.Key("duration");
            document.String(std::to_string(element.data_->duration_).c_str());

            document.Key("count");
            document.String(std::to_string(element.data_->count_).c_str());

            document.Key("value");
            document.String(element.value_);

            document.EndObject();
        }

        document.EndArray();
        document.EndObject();
    }

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

    std::vector<PrintData> getSortedData() const
    {
        std::vector<PrintData> result;
        result.reserve(statistics_.size());

        for(auto const& statistic : statistics_)
            result.emplace_back(&statistic.second, statistic.first.c_str());

        auto comparator = [](PrintData const& lhs, PrintData const& rhs)
        {
            return lhs.data_->duration_ > rhs.data_->duration_;
        };

        std::sort(std::begin(result), std::end(result), comparator);

        return result;
    }

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
