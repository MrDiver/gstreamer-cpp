#pragma once

#include "core/Bus.hpp"
#include "core/Pad.hpp"
#include "gst/gstelement.h"

namespace gst
{
    enum State
    {
        VoidPending = 0,
        Null        = 1,
        Ready       = 2,
        Paused      = 3,
        Playing     = 4
    };

    enum StateChangeReturn
    {
        Failure   = 0,
        Success   = 1,
        Async     = 2,
        NoPreroll = 3
    };

    /**
     * @brief C++ Wrapper around @see GstElement
     *
     */
    class Element : public Object
    {
      private:
        GstElement *element_ref;

      protected:
        Element(GstElement *ref);

      public:
        static Element create(GstElement *ref);

        GstElement *ref() const;

        Element &link(Element &destination);
        Element &link_filtered(std::string src_pad_name, Element &destination, std::string dest_pad_name);
        Element &unlink(Element &destination) const;
        StateChangeReturn set_state(State state) const;
        State state() const;
        State state_next() const;
        State state_pending() const;
        State state_target() const;
        Pad static_pad(std::string pad_name) const;
        Bus bus();
    };
} // namespace gst