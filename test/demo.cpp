#include "Prelude.hpp"
#include "core/Message.hpp"
#include "gst/gstbus.h"
#include "gst/gstelementfactory.h"
#include "gst/gstobject.h"
#include <glib.h>
#include <gst/gst.h>
#include <iostream>
#include <vector>

#include <thread>

int main(int arg, char *argv[])
{
    using namespace gst;
    init(&arg, &argv);
    Pipeline pipe = Pipeline::make("Test-Pipeline");
    Element src   = ElementFactory::make("videotestsrc");
    Element sink  = ElementFactory::make("autovideosink");

    pipe.add(src).add(sink);
    Pad sink_pad = sink.static_pad("sink");
    src.static_pad("src").link(sink_pad);

    pipe.set_state(State::Playing);
    Bus bus = pipe.bus();

    bool popping = true;
    while (popping)
    {
        Message msg = bus.pop_timed(-1);
        switch (msg.type())
        {
        case msg::EOS:
            popping = false;
            break;
        default:
            break;
        }
    }
    return 0;
    // gst_deinit();
}