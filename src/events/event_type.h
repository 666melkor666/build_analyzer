#pragma once

#include <cstdint>
#include <string_view>
#include <string>

namespace build_analyzer
{
namespace events
{
enum class EventType : std::uint8_t
{
    Unknown,
    Source,
    Frontend,
    Backend,
    ParseTemplate,
    ParseClass,
    InstantiateClass,
    InstantiateFunction,
    OptFunction,
    OptModule,
    CodeGenFunction
};

EventType fromString(std::string_view type);
std::string toString(EventType type);
} // namespace events
} // namespace build_analyzer
