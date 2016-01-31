#include <GLFW/glfw3.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if(glfwInit() == GL_FALSE) {
		fprintf(stderr, "Error initializing glfw\n");
		return 1;
	}
	return 0;
}
