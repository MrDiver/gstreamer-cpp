#include "core/Pad.hpp"
#include "gst/gstpad.h"
#include <stdexcept>

namespace gst
{
    Pad::Pad(GstPad *ref) : Object(&ref->object), pad_ref(ref) {}

    GstElement *Pad::ref()
    {
        // NOLINTNEXTLINE
        return GST_ELEMENT_CAST(this->pad_ref);
    }
    GstPad *Pad::ref_pad()
    {
        return this->pad_ref;
    }

    Pad make(PadDirection dir, std::string name)
    {
        return Pad(gst_pad_new(name.empty() ? NULL : name.c_str(), static_cast<GstPadDirection>(dir)));
    }

    LinkReturn Pad::link(Pad &destination)
    {
        return static_cast<LinkReturn>(gst_pad_link(this->pad_ref, destination.ref_pad()));
    }

    void Pad::unlink(Pad &destination)
    {
        if (gst_pad_unlink(this->pad_ref, destination.ref_pad()) != TRUE)
        {
            throw std::runtime_error(std::string("Failed to link pads ")
                                         .append(this->get_name())
                                         .append(" to ")
                                         .append(destination.get_name()));
        }
    }

} // namespace gst