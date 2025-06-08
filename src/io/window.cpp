#include <VKEngine/io/window.hpp>

Window::Window(int width, int height, std::string title)
    : width(width), height(height), title(title) {
    
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

bool Window::isRunning() {
    return !glfwWindowShouldClose(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}
