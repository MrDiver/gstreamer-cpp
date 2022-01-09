#include "core/Bus.hpp"
#include "gst/gstbus.h"
#include "gst/gstmessage.h"
#include <stdexcept>

namespace gst
{
    Bus::Bus(GstBus *ref) : Object(&ref->object), bus_ref(ref) {}

    GstBus *Bus::ref()
    {
        return this->bus_ref;
    }

    Message Bus::pop()
    {
        return Message(gst_bus_pop(this->bus_ref));
    }

    Message Bus::pop_filtered(msg::Type types)
    {
        return Message(gst_bus_pop_filtered(this->bus_ref, static_cast<GstMessageType>(types)));
    }

    Message Bus::pop_timed(ClockTime time)
    {
        return Message(gst_bus_timed_pop(this->ref(), static_cast<GstClockTime>(time)));
    }

    Message Bus::pop_timed_filtered(ClockTime time, msg::Type types)
    {
        return Message(gst_bus_timed_pop_filtered(this->bus_ref, static_cast<GstClockTime>(time),
                                                  static_cast<GstMessageType>(types)));
    }
} // namespace gst
