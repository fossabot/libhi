bin_PROGRAMS=gltest
nanovg_SOURCES=nanovg/src/nanovg.h nanovg/src/nanovg.c
gltest_SOURCES=$(nanovg_SOURCES) gltest.c 
gltest_CFLAGS=$(GLFW3_CFLAGS)
gltest_LDFLAGS=$(GLFW3_LIBS) -framework OpenGL
