nanovg_SOURCES=nanovg/src/nanovg.h nanovg/src/nanovg.c

lib_LTLIBRARIES=libhi.la
include_HEADERS=hi.h
libhi_la_SOURCES=$(nanovg_SOURCES) hi.c
libhi_la_CFLAGS=$(GLFW3_CFLAGS)
libhi_la_LDFLAGS=$(GLFW3_LIBS) -version-info 0:0:1 -export-symbols-regex ^hi_

bin_PROGRAMS=hitest
hitest_SOURCES=hitest.c
hitest_LDFLAGS=-lhi
