#include "core.hpp"
#include "gst/gstdebugutils.h"

#include <gst/gst.h>

namespace gst
{
    void deinit()
    {
        gst_deinit();
    }

    void init(int *argc, char ***argv)
    {
        gst_init(argc, argv);
    }

    bool init_check(int *argc, char ***argv, GError **error)
    {
        return static_cast<bool>(gst_init_check(argc, argv, error));
    }

    std::string get_main_executable_path()
    {
        return std::string(gst_get_main_executable_path());
    }

    GOptionGroup *init_get_option_group()
    {
        return gst_init_get_option_group();
    }

    bool is_initialized()
    {
        return gst_is_initialized() == TRUE;
    }

    bool segtrap_is_enabled()
    {
        return gst_segtrap_is_enabled() == TRUE;
    }

    void segtrap_set_enabled(bool enabled)
    {
        gst_segtrap_set_enabled(enabled ? TRUE : FALSE);
    }

    Version version()
    {
        Version v = {};
        gst_version(&v.major, &v.minor, &v.micro, &v.nano);
        return v;
    }

    std::string version_string()
    {
        return std::string(gst_version_string());
    }

    std::string debug_bin_to_dot_data(Bin &bin, DebugGraphDetails details)
    {
        return std::string(gst_debug_bin_to_dot_data(bin.ref_bin(), static_cast<GstDebugGraphDetails>(details)));
    }

    void debug_bin_to_dot_file(Bin &bin, DebugGraphDetails details, std::string file_name)
    {
        gst_debug_bin_to_dot_file(bin.ref_bin(), static_cast<GstDebugGraphDetails>(details), file_name.c_str());
    }
} // namespace gst