#include "core/Message.hpp"

namespace gst
{
    Message::Message(GstMessage *msg) : msg(msg) {}

    GstMessage *Message::ref() const
    {
        return this->msg;
    }

    msg::Type Message::type() const
    {
        return static_cast<msg::Type>(GST_MESSAGE_TYPE(this->msg));
    }
} // namespace gst