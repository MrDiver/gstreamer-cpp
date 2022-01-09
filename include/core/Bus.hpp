#pragma once

#include "core/Clock.hpp"
#include "core/Message.hpp"
#include "core/Object.hpp"
#include "gst/gstbus.h"

namespace gst
{

    class Bus : public Object
    {
      private:
        GstBus *bus_ref;

      public:
        Bus(GstBus *ref);
        GstBus *ref();

        Message pop();
        Message pop_filtered(msg::Type types);
        // void post();
        Message pop_timed(ClockTime time);
        Message pop_timed_filtered(ClockTime time, msg::Type types);
    };
} // namespace gst