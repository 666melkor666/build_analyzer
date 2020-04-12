#pragma once

#include "events/event.h"

#include "rapidjson/document.h"

#include <string>
#include <optional>

namespace build_analyzer
{
namespace parser
{
class Parser
{
public:
    Parser(std::string const& content, std::string const& filePath);

public:
    std::optional<events::Event> next();

private:
    rapidjson::Document document_;
    rapidjson::Value traceEvents_;
    rapidjson::Value::ConstValueIterator currentEvent_;
    rapidjson::Value::ConstValueIterator end_;
};
} // namespace parser
} // namespace build_analyzer
