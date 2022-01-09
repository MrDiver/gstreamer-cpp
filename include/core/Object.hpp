#pragma once

#include "gst/gstobject.h"
#include <string>

namespace gst
{

    /**
     * @brief C++ Wrapper around GstObject meant to be used in harmony with the other elements
     * only provides virtual functions which are used to manage basic functionality of GstObject
     */
    class Object
    {
      private:
        bool moved;
        GstObject *object_ref;

      public:
        Object(Object &other);
        Object &operator=(Object const &other);

        Object(Object &&other);
        Object &operator=(Object &&other);
        // Pad operator[](std::string);
        Object(GstObject *ref);
        ~Object();
        GstObject *ref() const;
        std::string get_name() const;
        uint32_t refcount();
        void set_name(std::string name);

        void set_property_from_string(std::string property_name, std::string value) const;
    };

} // namespace gst