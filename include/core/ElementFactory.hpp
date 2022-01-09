#pragma once

#include "core/Element.hpp"
#include <string>

namespace gst
{
    /**
     * @brief C++ Wrapper around GstElementFactory
     *
     */
    class ElementFactory
    {
      public:
        static Element make(std::string factory_name, std::string element_name = "");
    };

} // namespace gst