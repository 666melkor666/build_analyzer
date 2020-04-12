#pragma once

#include "events/event_type.h"

#include <iosfwd>

namespace build_analyzer
{
namespace events
{
struct Event;
} // namespace events

namespace analyze
{
struct Analyzer
{
    virtual ~Analyzer() = default;

    virtual events::EventType supportedEvent() const = 0;
    virtual void add(events::Event event) = 0;
    virtual void print(std::ostream& output) const = 0;
};
} // namespace analyze
} // namespace build_analyzer
