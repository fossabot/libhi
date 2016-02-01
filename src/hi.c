#include <GLFW/glfw3.h>
//#include <OpenGL/gl.h>
#include "nanovg/src/nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"

#include <stdio.h>

#include "hi.h"
#include "font.h"

typedef struct hi_context_t {
	GLFWwindow *window;
	NVGcontext *vg;
} hi_context_t;


void error_callback(int error, const char *desc) {
	fprintf(stderr, "GLFW error %d: %s\n", error, desc);
}

void draw(GLFWwindow *window, NVGcontext *vg) {
	double mouse_x, mouse_y;
	int window_width, window_height;
	int fb_width, fb_height;
	float pixel_ratio;

	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	glfwGetWindowSize(window, &window_width, &window_height);
	glfwGetFramebufferSize(window, &fb_width, &fb_height);
	pixel_ratio = (float)fb_width / (float)window_width;

	glViewport(0, 0, fb_width, fb_height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	nvgBeginFrame(vg, window_width, window_height, pixel_ratio);

	nvgStrokeColor(vg, nvgRGBf(1.0f, 1.0f, 1.0f));
	nvgStrokeWidth(vg, 1.0f);
	nvgLineCap(vg, NVG_SQUARE);

	//nvgScale(vg, (float)window_width, (float)window_height);

	//nvgBeginPath(vg);
	//nvgMoveTo(vg, 25.0f, 50.0f);
	//nvgLineTo(vg, 75.0f, 50.0f);
	//nvgClosePath(vg);
	//nvgStroke(vg);

	nvgFontFace(vg, "04B-03B");
	nvgFontSize(vg, 16.0f);
	nvgFontBlur(vg, 0.0f);
	nvgText(vg, 50.0f, 50.0f, "HELLO WORLD!", NULL);
	nvgStroke(vg);

	nvgEndFrame(vg);
}


int hi_init(void **context_ptr) {
	*context_ptr = (void *)malloc(sizeof(hi_context_t));
	hi_context_t *context = *context_ptr;

	if(glfwInit() == GL_FALSE) {
		fprintf(stderr, "Error initializing glfw\n");
		free(context);
		return ERR_GLFW_INIT;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	context->window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);
	if(!context->window) {
		glfwTerminate();
		free(context);
		return ERR_GLFW_INIT_WINDOW;
	}

	glfwMakeContextCurrent(context->window);

	context->vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	if(context->vg == NULL) {
		fprintf(stderr, "NanoVG init failed\n");
		glfwTerminate();
		free(context);
		return ERR_NANOVG_INIT;
	}

	//nvgCreateFont(context->vg, "04B-03B", "fonts/04B_03B_.TTF");
	nvgCreateFontMem(context->vg, "04B-03B", FONT_04B_03B_TTF, FONT_04B_03B_TTF_len, 0);

	// vsync
	//glfwSwapInterval(0);
	return OK;
}


int hi_update(void *context_ptr) {
	hi_context_t *context = (hi_context_t *)context_ptr;

	if(glfwWindowShouldClose(context->window)) {
		glfwTerminate();
		free(context);
		return 1;
	}else{
		draw(context->window, context->vg);
		glfwSwapBuffers(context->window);
		glfwPollEvents();
		return 0;
	}
}

