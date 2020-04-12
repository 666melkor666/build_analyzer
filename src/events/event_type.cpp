#include "events/event_type.h"

#include <unordered_map>

namespace build_analyzer
{
namespace events
{
std::string toString(EventType type)
{
    static std::unordered_map<EventType, std::string_view> const types =
    {
        { EventType::Source, "Source" },
        { EventType::Frontend, "Frontend" },
        { EventType::Backend, "Backend" },
        { EventType::ParseTemplate, "ParseTemplate" },
        { EventType::ParseClass, "ParseClass" },
        { EventType::InstantiateClass, "InstantiateClass" },
        { EventType::InstantiateFunction, "InstantiateFunction" },
        { EventType::OptFunction, "OptFunction" },
        { EventType::OptModule, "OptModule" },
        { EventType::CodeGenFunction, "CodeGen Function" }
    };

    auto result = types.find(type);
    if(result != std::end(types))
        return result->second.data();

    return "Unknown";
}

EventType fromString(std::string_view type)
{
    static std::unordered_map<std::string_view, EventType> const types =
    {
        { "Source", EventType::Source },
        { "Frontend", EventType::Frontend },
        { "Backend", EventType::Backend },
        { "ParseTemplate", EventType::ParseTemplate },
        { "ParseClass", EventType::ParseClass },
        { "InstantiateClass", EventType::InstantiateClass },
        { "InstantiateFunction", EventType::InstantiateFunction },
        { "OptFunction", EventType::OptFunction },
        { "OptModule", EventType::OptModule },
        { "CodeGen Function", EventType::CodeGenFunction }
    };

    auto result = types.find(type);
    if(result != std::end(types))
        return result->second;

    return EventType::Unknown;
}
} // namespace events
} // namespace build_analyzer
