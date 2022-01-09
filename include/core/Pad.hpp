#pragma once

#include "core/Object.hpp"
#include "gst/gstpad.h"
namespace gst
{
    enum PadDirection
    {
        Unknown = 0,
        Src     = 1,
        Sink    = 2
    };

    enum LinkReturn
    {
        OK              = 0,
        WRONG_HIERARCHY = -1,
        WAS_LINKED      = -2,
        WRONG_DIRECTION = -3,
        NOFORMAT        = -4,
        NOSCHED         = -5,
        REFUSED         = -6
    };

    class Pad : Object
    {
      private:
        GstPad *pad_ref;

      public:
        Pad(GstPad *ref);
        Pad make(PadDirection dir, std::string name = "");

        GstElement *ref();
        GstPad *ref_pad();

        LinkReturn link(Pad &destination);
        void unlink(Pad &destination);
    };
} // namespace gst