#include "core/ElementFactory.hpp"
#include "gst/gstinfo.h"
#include <stdexcept>

namespace gst
{
    Element ElementFactory::make(std::string factory_name, std::string element_name)
    {
        GstElement *element =
            gst_element_factory_make(factory_name.c_str(), element_name.empty() ? NULL : element_name.c_str());
        if (element == nullptr)
        {
            // NOLINTNEXTLINE
            gst_printerrln("Failed to create Element %s", element_name.c_str());
            throw std::runtime_error("Failed to create Element");
        }
        // calls constructor of @see Element and sets Element::owner to true
        Element e = Element::create(element);
        return e;
    }
} // namespace gst