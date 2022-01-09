#include "core/Object.hpp"
#include "gst/gstobject.h"
#include <iostream>
#include <stdexcept>

namespace gst
{
    Object::Object(GstObject *ref) : object_ref(ref), moved(false) {}

    Object::~Object()
    {
        if (this->object_ref != nullptr)
        {
            gst_object_unref(this->object_ref);
        }
    }

    // Copy
    Object::Object(Object &other) : object_ref(other.object_ref), moved(false)
    {
        if (this != &other)
        {
            gst_object_ref(this->object_ref);
        }
    }

    Object &Object::operator=(Object const &other)
    {
        if (this != &other)
        {
            this->object_ref = other.object_ref;
            gst_object_ref(this->object_ref);
        }
        return *this;
    }

    // Move
    Object::Object(Object &&other) : object_ref(other.object_ref), moved(false)
    {
        if (this != &other)
        {
            other.object_ref = nullptr;
        }
    }

    Object &Object::operator=(Object &&other)
    {
        if (this != &other)
        {
            this->object_ref = other.object_ref;
            other.object_ref = nullptr;
        }
        return *this;
    }

    // Object *Object::operator[](std::string key)
    // {
    //     std::cout << "You accessed me" << std::endl;
    //     return this;
    // }

    std::string Object::get_name() const
    {
        return gst_object_get_name(static_cast<GstObject *>(this->object_ref));
    }

    void Object::set_name(std::string name)
    {
        gst_object_set_name(static_cast<GstObject *>(this->object_ref), name.c_str());
    }

    uint32_t Object::refcount()
    {
        // NOLINTNEXTLINE
        return GST_OBJECT_REFCOUNT_VALUE(this->object_ref);
    }

    GstObject *Object::ref() const
    {
        return this->object_ref;
    }

    void Object::set_property_from_string(std::string property_name, std::string value) const
    {
        // NOLINTNEXTLINE
        g_object_set(this->ref(), property_name.c_str(), value.c_str(), NULL);
    }
} // namespace gst