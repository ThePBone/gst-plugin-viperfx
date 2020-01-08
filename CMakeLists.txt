cmake_minimum_required(VERSION 3.10)
project(gst-plugin-viperfx)

include_directories(.)
include_directories(src)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.0
        gstreamer-base-1.0>=1.0
        gstreamer-controller-1.0>=1.0
        gstreamer-audio-1.0>=1.0)

file(GLOB SOURCES
        src/*.h
        src/*.c
        )

add_library(gst-plugin-viperfx SHARED ${SOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0 gio-unix-2.0)
target_include_directories(gst-plugin-viperfx PUBLIC ${GST_INCLUDE_DIRS})
target_compile_options(gst-plugin-viperfx PUBLIC ${GST_CFLAGS})
target_link_libraries(gst-plugin-viperfx ${GST_LIBRARIES} pthread PkgConfig::deps)
