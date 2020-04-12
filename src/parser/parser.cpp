#include "parser/parser.h"

#include "events/event_type.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <iostream>

namespace build_analyzer
{
namespace parser
{
Parser::Parser(std::string const& content, std::string const& filePath)
{
    document_.Parse(content.c_str());
    if(!document_.IsObject() || !document_.HasMember("traceEvents"))
        throw std::invalid_argument{"bad input file: " + filePath};

    traceEvents_ = document_["traceEvents"];
    assert(traceEvents_.IsArray());

    currentEvent_ = traceEvents_.Begin();
    end_ = traceEvents_.End();
}

namespace
{
std::optional<events::EventType> getEventType(rapidjson::Value const& value)
{
    auto name = value.FindMember("name");
    if(name == value.MemberEnd())
        return std::nullopt;

    assert(name->value.IsString());

    return events::fromString(name->value.GetString());
}

events::Event getEvent(rapidjson::Value const& value)
{
    assert(value.HasMember("ts") && value["ts"].IsUint64());
    assert(value.HasMember("dur") && value["dur"].IsUint64());
    assert(value.HasMember("name") && value["name"].IsString());

    std::string args;
    if(value.HasMember("args") && value["args"].HasMember("detail"))
        args = value["args"]["detail"].GetString();

    return { *getEventType(value)
           , value["ts"].GetUint64()
           , value["dur"].GetUint64()
           , std::move(args) };
}
} // namespace unnamed

std::optional<events::Event> Parser::next()
{
    auto isSupported = [](rapidjson::Value const& value)
    {
        auto eventType = getEventType(value);
        return eventType && *eventType != events::EventType::Unknown;
    };

    currentEvent_ = std::find_if(currentEvent_, end_, isSupported);

    if(currentEvent_ == traceEvents_.End())
        return std::nullopt;

    auto result = getEvent(*currentEvent_);

    ++currentEvent_;

    return result;
}
} // namespace parser
} // namespace build_analyzer
