cmake_minimum_required(VERSION 3.18) # 可通过修改版本解决
project (P1) # 项目名

# 头文件设置
set(GLAD_H ${PROJECT_SOURCE_DIR}/include)
set(GLFW_H /usr/local/include)
set(dependencies /base)
include_directories(${GLAD_H} ${GLFW_H} ${dependencies})
set(CMAKE_CXX_STANDARD 17)
set(GLFW_LINK /usr/local/lib/libglfw.3.dylib)

link_libraries(${GLFW_LINK})

# 执行编译命令 testc
# base文件夹内基类cpp文件和glad.c
set(baseSOURCES glad.c base/shader.cpp base/application.cpp base/camera.cpp base/object3d.cpp base/model.cpp base/shader.cpp base/skybox.cpp base/texture.cpp base/modelEntity.cpp base/ElementEntity.cpp base/element.cpp)
# 所有要编译的文件
set(SOURCES  tiny_obj_loader/tiny_obj_loader.cc main.cpp entity.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_impl_glfw.cpp imgui/imgui_impl_opengl3.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp stb/stb_vorbis.c stb/stb_image.cpp)
#项目名
add_executable(P1 ${baseSOURCES} ${SOURCES})

# 链接系统的 OpenGL 框架
if (APPLE)
    target_link_libraries(P1 "-framework OpenGL") # 这边项目名也记得改
endif()

set(GLFW_LINK /usr/local/lib/libglfw.3.dylib)
link_libraries(${GLFW_LINK})


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
