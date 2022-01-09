#pragma once

#include "core/Element.hpp"
#include "gst/gstbin.h"

namespace gst
{
    class Bin : public Element
    {
      private:
        GstBin *bin_ref;

      public:
        Bin(GstBin *ref);
        GstElement *ref() const;
        GstBin *ref_bin() const;

        Bin &add(Element &element);
        // void add_many(std::vector<ElementPtr> elements);
    };
} // namespace gst