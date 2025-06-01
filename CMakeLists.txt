cmake_minimum_required(VERSION 4.0)
project(VKEngine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

find_package(Vulkan REQUIRED)
find_package(glfw3)
find_package(glm)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(VKEngine_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

IF(NOT glfw3_FOUND)
    message(STATUS "glfw3 not found, fetching...")
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.4
    )
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW example programs" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW documentation" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "Install GLFW" FORCE)
    set(GLFW_VULKAN_STATIC ON CACHE BOOL "Use static Vulkan library" FORCE)
    FetchContent_MakeAvailable(glfw)
else()
    message(STATUS "glfw3 found at ${glfw3_DIR}")
endif()

IF(NOT glm_FOUND)
    message(STATUS "glm not found, fetching...")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 1.0.1
    )
    set(glm_BUILD_EXAMPLES OFF CACHE BOOL "Build glm example programs" FORCE)
    set(glm_BUILD_TESTS OFF CACHE BOOL "Build glm tests" FORCE)
    set(glm_INSTALL OFF CACHE BOOL "Install glm" FORCE)
    FetchContent_MakeAvailable(glm)
else()
    message(STATUS "glm found at ${glm_DIR}")
endif()

# Add STB (for stb_image and stb_vorbis)
message(STATUS "Fetching stb...")
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
)
FetchContent_MakeAvailable(stb)

add_library(VKEngine SHARED
    ${VKEngine_SOURCE_DIR}/graphics/mesh.cpp
    ${VKEngine_SOURCE_DIR}/io/window.cpp
)

target_include_directories(VKEngine PRIVATE
    ${VKEngine_INCLUDE_DIRS}
    ${Vulkan_INCLUDE_DIRS}
    ${glfw3_INCLUDE_DIRS}
    ${glm_INCLUDE_DIRS}
    ${stb_SOURCE_DIR}
)

target_link_libraries(VKEngine PRIVATE
    Vulkan::Vulkan
    glm::glm
    glfw
)

target_compile_definitions(VKEngine PRIVATE
    STB_IMAGE_IMPLEMENTATION
    STB_VORBIS_IMPLEMENTATION
)
