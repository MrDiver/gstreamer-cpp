#pragma once

#include "gst/gstmessage.h"
namespace gst
{

    namespace msg
    {
        typedef enum
        {
            Unknown            = 0,
            EOS                = (1 << 0),
            Error              = (1 << 1),
            Warning            = (1 << 2),
            Info               = (1 << 3),
            Tag                = (1 << 4),
            Buffering          = (1 << 5),
            StateChanged       = (1 << 6),
            StateDirty         = (1 << 7),
            StepDone           = (1 << 8),
            ClockProvide       = (1 << 9),
            ClockLost          = (1 << 10),
            NewClock           = (1 << 11),
            StructureChange    = (1 << 12),
            StreamStatus       = (1 << 13),
            Application        = (1 << 14),
            Element            = (1 << 15),
            SegmentStart       = (1 << 16),
            SegmentDone        = (1 << 17),
            DurationChanged    = (1 << 18),
            Latency            = (1 << 19),
            AsyncStart         = (1 << 20),
            AsyncDone          = (1 << 21),
            RequestState       = (1 << 22),
            StepStart          = (1 << 23),
            QOS                = (1 << 24),
            Progress           = (1 << 25),
            TOC                = (1 << 26),
            ResetTime          = (1 << 27),
            StreamStart        = (1 << 28),
            NeedContext        = (1 << 29),
            HaveContext        = (1 << 30),
            Extended           = (gint)(1U << 31),
            DeviveAdded        = Extended + 1,
            DeviceRemoved      = Extended + 2,
            PropertyNotify     = Extended + 3,
            StreamCollection   = Extended + 4,
            StreamsSelected    = Extended + 5,
            Redirected         = Extended + 6,
            DeviceChanged      = Extended + 7,
            InstantRateRequest = Extended + 8,
            Any                = (gint)(0xffffffff)
        } Type;
    } // namespace msg
    class Message
    {
      private:
        GstMessage *msg;

      public:
        Message(GstMessage *msg);
        GstMessage *ref() const;
        msg::Type type() const;
    };
} // namespace gst