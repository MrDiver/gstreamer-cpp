#include "core/Pipeline.hpp"
#include "gst/gstinfo.h"
#include <stdexcept>

namespace gst
{
    Pipeline::Pipeline(GstPipeline *ref) : Bin(&ref->bin), pipeline_ref(ref) {}

    GstElement *Pipeline::ref() const
    {
        // NOLINTNEXTLINE
        return GST_ELEMENT_CAST(this->pipeline_ref);
    }

    GstPipeline *Pipeline::ref_pipeline() const
    {
        // NOLINTNEXTLINE
        return this->pipeline_ref;
    }

    Pipeline Pipeline::make(std::string name)
    {
        // NOLINTNEXTLINE
        GstPipeline *pipeline = GST_PIPELINE_CAST(gst_pipeline_new(name.c_str()));
        if (pipeline == nullptr)
        {
            // NOLINTNEXTLINE
            gst_printerrln("Failed to create Pipeline %s", name.c_str());
            throw std::runtime_error("Failed to create Pipeline");
        }
        Pipeline p(pipeline);
        return p;
    }

} // namespace gst