cmake_minimum_required(VERSION 3.10)

project(Renderer)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
message(STATUS ${CMAKE_SOURCE_DIR})
set(sources 
	${CMAKE_SOURCE_DIR}/main.cpp 
	${CMAKE_SOURCE_DIR}/src/glad.c 
	${CMAKE_SOURCE_DIR}/src/Log.cpp 
	${CMAKE_SOURCE_DIR}/src/Shader.cpp 
	${CMAKE_SOURCE_DIR}/src/Window.cpp
)
set(headers 
	${CMAKE_SOURCE_DIR}/include/glad/glad.h 
	${CMAKE_SOURCE_DIR}/include/Log.h 
	${CMAKE_SOURCE_DIR}/include/Window.h 
	${CMAKE_SOURCE_DIR}/include/Shader.h 
)
add_executable(Renderer ${sources} ${headers})
target_link_libraries(Renderer ${GLFW_LIBRARIES})
target_include_directories(Renderer PUBLIC ${CMAKE_SOURCE_DIR}/include)
