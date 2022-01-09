#pragma once

#include "core/Bin.hpp"
#include "gst/gstpipeline.h"

namespace gst
{
    class Pipeline : public Bin
    {
      private:
        GstPipeline *pipeline_ref;

      public:
        Pipeline(GstPipeline *ref);
        GstElement *ref() const;
        GstPipeline *ref_pipeline() const;

        static Pipeline make(std::string name);
    };
} // namespace gst