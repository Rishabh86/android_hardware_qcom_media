# -----------------------------------------------------------------------------
#               Common definitons
# -----------------------------------------------------------------------------

AM_CPPFLAGS = -g -O3
AM_CPPFLAGS += -Werror

AM_CPPFLAGS += -D_LINUX_
AM_CPPFLAGS += -DHAVE_ANDROID_OS
AM_CPPFLAGS += -I$(top_srcdir)/mm-video-v4l2/vidc/common/inc

# -----------------------------------------------------------------------------
#           Make the Shared library (libhypv_intercept)
# -----------------------------------------------------------------------------
h_sources = hypv_intercept.h hypv_debug.h
c_sources = hypv_intercept.cpp

include_HEADERS = $(h_sources)
lib_LTLIBRARIES = libhypv_intercept.la
libhypv_intercept_la_SOURCES = $(c_sources)
libhypv_intercept_la_CPPFLAGS = $(AM_CPPFLAGS) -fPIC
libhypv_intercept_la_LDFLAGS = -shared -llog -ldl
