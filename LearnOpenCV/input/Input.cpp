#include "Input.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Core::Input::InitInput()
{
	glfwSetCursorEnterCallback(window, mouse_enter_callback);
	glfwSetCursorPosCallback(window, mouse_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
}
