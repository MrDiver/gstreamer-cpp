#include "core/Element.hpp"
#include "gst/gstelement.h"
#include "gst/gstinfo.h"
#include "gst/gstutils.h"
#include <stdexcept>

namespace gst
{
    Element::Element(GstElement *ref) : Object(&ref->object), element_ref(ref) {}

    Element Element::create(GstElement *ref)
    {
        return Element(ref);
    }

    GstElement *Element::ref() const
    {
        return this->element_ref;
    }

    Element &Element::link(Element &destination)
    {
        if (gst_element_link(this->ref(), destination.ref()) == FALSE)
        {
            // NOLINTNEXTLINE
            gst_printerrln("Failed to link element %s to %s", this->get_name().c_str(), destination.get_name().c_str());
            throw std::runtime_error("Failed to Link Elements");
        }
        return destination;
    }

    Element &Element::link_filtered(std::string src_pad_name, Element &destination, std::string dest_pad_name)
    {
        if (gst_element_link_pads(this->ref(), src_pad_name.c_str(), destination.ref(), dest_pad_name.c_str()) == FALSE)
        {
            // NOLINTNEXTLINE
            gst_printerrln("Failed to link element %s to %s", this->get_name().c_str(), destination.get_name().c_str());
            throw std::runtime_error("Failed to Link Elements");
        }
        return destination;
    }

    Element &Element::unlink(Element &destination) const
    {
        gst_element_unlink(this->ref(), destination.ref());
        return destination;
    }

    StateChangeReturn Element::set_state(State state) const
    {
        return static_cast<StateChangeReturn>(gst_element_set_state(this->ref(), static_cast<GstState>(state)));
    }

    State Element::state() const
    {
        return static_cast<State>(GST_STATE(this->ref()));
    }

    State Element::state_next() const
    {
        return static_cast<State>(GST_STATE(this->ref()));
    }

    State Element::state_pending() const
    {
        return static_cast<State>(GST_STATE(this->ref()));
    }

    State Element::state_target() const
    {
        return static_cast<State>(GST_STATE(this->ref()));
    }

    Pad Element::static_pad(std::string pad_name) const
    {
        return Pad(gst_element_get_static_pad(this->ref(), pad_name.c_str()));
    }

    Bus Element::bus()
    {
        if (this->element_ref->bus == nullptr)
        {
            throw std::runtime_error(
                std::string("Nullpointer: Failed to get Bus element of ").append(this->get_name()));
        }
        return Bus(static_cast<GstBus *>(gst_element_get_bus(this->element_ref)));
    }
} // namespace gst