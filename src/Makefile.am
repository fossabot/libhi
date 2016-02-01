nanovg_SOURCES=nanovg/src/nanovg.h nanovg/src/nanovg.c

lib_LTLIBRARIES=libhi.la
libhi_la_SOURCES=$(nanovg_SOURCES) hi.c
libhi_la_CFLAGS=$(GLFW3_CFLAGS)
libhi_la_LDFLAGS=$(GLFW3_LIBS) -framework OpenGL -version-info 0:0:0

bin_PROGRAMS=gltest
gltest_SOURCES=gltest.c
gltest_LDFLAGS=-L.libs/ -lhi
