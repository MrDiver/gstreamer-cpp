#include "core/Bin.hpp"
#include <stdexcept>

namespace gst
{
    Bin::Bin(GstBin *ref) : Element(&ref->element), bin_ref(ref) {}

    GstElement *Bin::ref() const
    {
        // NOLINTNEXTLINE
        return GST_ELEMENT_CAST(this->bin_ref);
    }

    GstBin *Bin::ref_bin() const
    {
        return this->bin_ref;
    }

    Bin &Bin::add(Element &e)
    {
        gst_object_ref(e.ref());
        gst_bin_add(this->bin_ref, e.ref());
        return *this;
    }

    // void Bin::add_many(std::vector<ElementPtr> elements)
    // {
    //     std::vector<GstElement *> ptrs = {};
    //     for (auto e : elements)
    //     {
    //         ptrs.push_back(e->ref());
    //     }
    //     // NOLINTNEXTLINE
    //     gst_bin_add_many(GST_BIN(this->ref()), *ptrs.data(), NULL);
    // }
} // namespace gst