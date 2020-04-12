#include "analyze/source_analyzer.h"

#include "events/event.h"

#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"

#include <algorithm>
#include <ostream>
#include <vector>

namespace build_analyzer
{
namespace analyze
{
events::EventType SourceAnalyzer::supportedEvent() const
{
    return events::EventType::Source;
}

void SourceAnalyzer::add(events::Event event)
{
    auto& data = statistics_[std::move(event.value_)];

    data.duration_ += event.duration_;
    ++data.count_;
}

std::vector<SourceAnalyzer::PrintData> SourceAnalyzer::getSortedData() const
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

void SourceAnalyzer::print(std::ostream& output) const
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
} // namespace analyze
} // namespace build_analyzer
