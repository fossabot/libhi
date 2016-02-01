#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "nanovg/src/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"

#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#include "hi.h"
#include "font.h"

#define FPS_LEN 16
#define CROSSHAIR_SIZE 5.0f

typedef struct hi_context_t {
	GLFWwindow *window;
	NVGcontext *vg;

	double fps_timer;
	uint16_t fps_counter;
	char fps[6];
} hi_context_t;


static void error_callback(int error, const char *desc) {
	fprintf(stderr, "GLFW error %d: %s\n", error, desc);
}

static void update_fps(hi_context_t *context) {
	context->fps_counter++;
	if((glfwGetTime() - context->fps_timer) >= 1.0) {
		snprintf(context->fps, FPS_LEN, "%i", context->fps_counter);
		context->fps_counter = 0;
		context->fps_timer += 1.0;
	}
}

static void draw_cursor(hi_context_t *context) {
	NVGcontext *vg = context->vg;
	double xpos, ypos;
	glfwGetCursorPos(context->window, &xpos, &ypos);
	
	nvgStrokeColor(vg, nvgRGBf(0.0f, 1.0f, 0.0f));
	nvgStrokeWidth(vg, 1.0f);

	nvgBeginPath(vg);
	nvgMoveTo(vg, (xpos - CROSSHAIR_SIZE), ypos);
	nvgLineTo(vg, (xpos + CROSSHAIR_SIZE), ypos);
	nvgClosePath(vg);
	nvgStroke(vg);

	nvgBeginPath(vg);
	nvgMoveTo(vg, xpos, (ypos - CROSSHAIR_SIZE));
	nvgLineTo(vg, xpos, (ypos + CROSSHAIR_SIZE));
	nvgClosePath(vg);
	nvgStroke(vg);
}

static void draw(hi_context_t *context) {
	GLFWwindow *window = context->window;
	NVGcontext *vg = context->vg;

	double mouse_x, mouse_y;
	int window_width, window_height;
	int fb_width, fb_height;
	float pixel_ratio;
	float bounds[4];

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
	//nvgLineCap(vg, NVG_SQUARE);

	nvgFontFace(vg, "04B-03B");
	nvgFontSize(vg, 16.0f);
	nvgFontBlur(vg, 0.0f);

	nvgBeginPath(vg);
	nvgText(vg, 50.0f, 50.0f, "HELLO WORLD!", NULL);

	// FPS counter
	nvgTextBounds(vg, 0, 0, context->fps, NULL, bounds);
	nvgText(vg, window_width - (bounds[2]-bounds[0]), bounds[3]-bounds[1], context->fps, NULL);
	nvgClosePath(vg);
	nvgStroke(vg);

	draw_cursor(context);
	nvgEndFrame(vg);
}


int hi_init(void **context_ptr) {
	*context_ptr = (void *)malloc(sizeof(hi_context_t));
	hi_context_t *context = *context_ptr;
	GLenum err;

	if(glfwInit() == GL_FALSE) {
		fprintf(stderr, "Error initializing glfw\n");
		free(context);
		return ERR_GLFW_INIT;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	context->window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);
	if(!context->window) {
		glfwTerminate();
		free(context);
		return ERR_GLFW_INIT_WINDOW;
	}

	glfwMakeContextCurrent(context->window);

	context->vg = nvgCreateGL3(0);
	if(context->vg == NULL) {
		fprintf(stderr, "NanoVG init failed\n");
		glfwTerminate();
		free(context);
		return ERR_NANOVG_INIT;
	}

	//nvgCreateFont(context->vg, "04B-03B", "fonts/04B_03B_.TTF");
	nvgCreateFontMem(context->vg, "04B-03B", FONT_04B_03B_TTF, FONT_04B_03B_TTF_len, 0);

	// vsync
	glfwSwapInterval(0);
	strcpy(context->fps, "00");
	context->fps_counter = 0;
	context->fps_timer = glfwGetTime();

	glfwSetInputMode(context->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	return OK;
}

void hi_destroy(void *context_ptr) {
	glfwTerminate();
	free(context_ptr);
}

int hi_update(void *context_ptr) {
	hi_context_t *context = (hi_context_t *)context_ptr;

	if(glfwWindowShouldClose(context->window)) {
		return 1;
	}else{
		draw(context);
		glfwSwapBuffers(context->window);
		//glfwPollEvents();
		glfwWaitEvents();
		update_fps(context);
		return 0;
	}
}
