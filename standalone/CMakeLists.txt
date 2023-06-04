cmake_minimum_required(VERSION 3.14...3.22)

project(GreeterStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 3.0.0
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

CPMAddPackage("gh:ocornut/imgui@1.89.6")

CPMAddPackage(
        NAME GLFW
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.3.2
        OPTIONS
          "GLFW_BUILD_TESTS OFF"
          "GLFW_BUILD_EXAMPLES OFF"
          "GLFW_BULID_DOCS OFF"
)

CPMAddPackage(NAME Greeter SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

find_package(OpenGL REQUIRED)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 OUTPUT_NAME "Greeter")

target_sources(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/>imgui.cpp
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/>imgui_draw.cpp
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/>imgui_widgets.cpp
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/>imgui_tables.cpp
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/>imgui_demo.cpp
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/>backends/imgui_impl_glfw.cpp
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/>backends/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>)

target_link_libraries(${PROJECT_NAME} Greeter::Greeter cxxopts)
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)