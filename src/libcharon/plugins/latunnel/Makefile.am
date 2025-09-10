AM_CPPFLAGS = \
	-I$(top_srcdir)/src/libstrongswan \
	-I$(top_srcdir)/src/libcharon

AM_CFLAGS = \
	$(PLUGIN_CFLAGS)

if MONOLITHIC
noinst_LTLIBRARIES = libstrongswan-latunnel.la
else
plugin_LTLIBRARIES = libstrongswan-latunnel.la
endif

libstrongswan_latunnel_la_SOURCES = \
	latunnel_plugin.h latunnel_plugin.c \
	latunnel_listener.h latunnel_listener.c

libstrongswan_latunnel_la_LDFLAGS = -module -avoid-version