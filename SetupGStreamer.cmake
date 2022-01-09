
find_package(PkgConfig) #finding pkg-config is a helper tool

#using pkg-config to getting Gstreamer
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

function(add_gstreamer T)
    #including GStreamer header files directory
    target_include_directories(
            ${T}
            PUBLIC
            ${GLIB_INCLUDE_DIRS}
            ${GSTREAMER_INCLUDE_DIRS}
    )

    #linking GStreamer library directory
    target_link_directories(
            ${T}
            PUBLIC
            ${GLIB_LIBRARY_DIRS}
            ${GSTREAMER_LIBRARY_DIRS}
    )

    #linking Gstreamer library with target executable
    target_link_libraries(${T} ${GSTREAMER_LIBRARIES})
endfunction()