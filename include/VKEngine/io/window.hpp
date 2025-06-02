#pragma once

#define GLFW_INCLUDE_NONE

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window();

    bool isRunning();
    
private:
    int width;
    int height;
    std::string title;
    
    GLFWwindow* window;

    void initVulkan();
};