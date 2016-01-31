
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include "nanovg/src/nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg/src/nanovg_gl.h"

#include <stdio.h>


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


int main(int argc, char **argv) {
	GLFWwindow *window;
	NVGcontext *vg = NULL;

	if(glfwInit() == GL_FALSE) {
		fprintf(stderr, "Error initializing glfw\n");
		return 1;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Hello world", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	if(vg == NULL) {
		fprintf(stderr, "NanoVG init failed\n");
		glfwTerminate();
		return -1;
	}

	nvgCreateFont(vg, "04B-03B", "04B_03B_.TTF");

	// vsync
	//glfwSwapInterval(0);

	while(!glfwWindowShouldClose(window)) {
		draw(window, vg);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
