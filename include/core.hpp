#pragma once

#include "core/Bin.hpp"
#include "core/Bus.hpp"
#include "core/Clock.hpp"
#include "core/Element.hpp"
#include "core/ElementFactory.hpp"
#include "core/Message.hpp"
#include "core/Object.hpp"
#include "core/Pad.hpp"
#include "core/Pipeline.hpp"

/**
 * @brief Namespace for all GStreamer an GLib Wrappers
 *
 */
namespace gst
{
    /**
     * @brief Clean up any resources created by GStreamer in gst::init.
     *
     * It is normally not needed to call this function in a normal application as the resources will automatically be
     * freed when the program terminates. This function is therefore mostly used by testsuites and other memory
     * profiling tools. After this call GStreamer (including this method) should not be used anymore.
     */
    void deinit();

    /**
     * @brief Initializes the GStreamer library, setting up internal path lists, registering built-in elements, and
     * loading standard plugins.
     *
     * @param argc  pointer to application's argc
     * @param argv  pointer to application's argv
     */
    void init(int *argc, char ***argv);

    /**
     * @brief Initializes the GStreamer library, setting up internal path lists, registering built-in elements, and
     * loading standard plugins. This function will return FALSE if GStreamer could not be initialized for some reason.
     * If you want your program to fail fatally, use gst_init instead.
     * @param argc pointer to application's argc
     * @param argv pointer to application's argv
     * @param error pointer to a GError to which a message will be posted on error
     * @return true if GStreamer could be initialized.
     * @return false else
     */
    bool init_check(int *argc, char ***argv, GError **error);

    /**
     * @brief This helper is mostly helpful for plugins that need to inspect the folder of the main executable to
     * determine their set of features.
     *
     * @return std::string The path of the executable that initialized GStreamer, or
     * NULL if it could not be determined.
     */
    std::string get_main_executable_path();

    /**
     * @brief Returns a GOptionGroup with GStreamer's argument specifications. The group is set up to use standard
     * GOption callbacks, so when using this group in combination with GOption parsing methods, all argument parsing and
     * initialization is automated.
     *
     * @return GOptionGroup* a pointer to GStreamer's option group.
     */
    GOptionGroup *init_get_option_group();

    /**
     * @brief Use this function to check if GStreamer has been initialized with gst::init or gst::init_check.
     *
     * @return true if initialization has been done.
     * @return false else
     */
    bool is_initialized();

    /**
     * @brief Some functions in the GStreamer core might install a custom SIGSEGV handler to better catch and report
     * errors to the application. Currently this feature is enabled by default when loading plugins.
     *
     * @return true if GStreamer is allowed to install a custom SIGSEGV handler.
     * @return false else
     */
    bool segtrap_is_enabled();

    /**
     * @brief Applications might want to disable/enable the SIGSEGV handling of the GStreamer core. See @see
     * gst::segtrap_is_enabled for more information.
     *
     * @param enabled whether a custom SIGSEGV handler should be installed.
     */
    void segtrap_set_enabled(bool enabled);

    /**
     * @brief Struct for the version of gstreamer;
     *
     */
    typedef struct Version
    {
        uint32_t major;
        uint32_t minor;
        uint32_t micro;
        uint32_t nano;
    } Version;

    /**
     * @brief Gets the version number of the GStreamer library.
     *
     * @return Version struct containing major,minor,micro,nano version numbers
     */
    Version version();

    /**
     * @brief This function returns a string that is useful for describing this version of GStreamer to the outside
     * world: user agent strings, logging, ...
     *
     * @return std::string a newly allocated string describing this version of GStreamer.
     */
    std::string version_string();

    /**
     * @brief Enum containing different modes for dot graph debug output
     *
     */
    typedef enum
    {
        SHOW_MEDIA_TYPE         = (1 << 0),
        SHOW_CAPS_DETAILS       = (1 << 1),
        SHOW_NON_DEFAULT_PARAMS = (1 << 2),
        SHOW_STATES             = (1 << 3),
        SHOW_FULL_PARAMS        = (1 << 4),
        SHOW_ALL                = ((1 << 4) - 1),
        SHOW_VERBOSE            = (gint)(0xffffffff)
    } DebugGraphDetails;

    /**
     * @brief To aid debugging applications one can use this method to obtain the whole network of gstreamer elements
     * that form the pipeline into a dot file. This data can be processed with graphviz to get an image.
     *
     * @param bin the top-level pipeline that should be analyzed
     * @param details type of @see DebugGraphDetails to use
     * @return std::string a string containing the pipeline in graphviz dot format.
     */
    std::string debug_bin_to_dot_data(Bin &bin, DebugGraphDetails details);

    /**
     * @brief To aid debugging applications one can use this method to write out the whole network of gstreamer elements
     * that form the pipeline into a dot file. This file can be processed with graphviz to get an image.
     *
     * @param bin the top-level pipeline that should be analyzed
     * @param details type of @see DebugGraphDetails to use
     * @param file_name output base filename (e.g. "myplayer")
     */
    void debug_bin_to_dot_file(Bin &bin, DebugGraphDetails details, std::string file_name);

    /**
     * @brief This works like @see gst::debug_bin_to_dot_file, but adds the current timestamp to the filename, so that
     * it can be used to take multiple snapshots.
     *
     * @param bin the top-level pipeline that should be analyzed
     * @param details type of @see DebugGraphDetails to use
     * @param file_name output base filename (e.g. "myplayer")
     */
    void gst_debug_bin_to_dot_file_with_ts(Bin &bin, DebugGraphDetails details, std::string file_name);

} // namespace gst