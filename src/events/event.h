#pragma once

#include "events/event_type.h"

#include <cstdint>
#include <string>

namespace build_analyzer
{
namespace events
{
struct Event
{
    Event(EventType type, std::uint64_t start, std::uint64_t duration, std::string value)
        : type_{type}
        , start_{start}
        , duration_{duration}
        , value_{std::move(value)}
    {}

    EventType type_;
    std::uint64_t start_;
    std::uint64_t duration_;
    std::uint64_t count_ = 1;
    std::string value_;
};
} // namespace events
} // namespace build_analyzer
