#pragma once

enum {
	OK = 0,
	ERR_GLFW_INIT,
	ERR_GLFW_INIT_WINDOW,
	ERR_GLEW_INIT,
	ERR_NANOVG_INIT,
} hi_error;


int hi_init(void **context_ptr);
int hi_update(void *context_ptr);
void hi_destroy(void *context_ptr);
