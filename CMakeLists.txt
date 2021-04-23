cmake_minimum_required (VERSION 3.20.1)

project(LandmassTool)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(OpenGL)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
		"${SOURCE_DIR}/*.h"
		"${SOURCE_DIR}/*.cpp"
)

add_executable(LandmassTool ${SOURCES})

target_include_directories(LandmassTool PRIVATE ${SOURCE_DIR})

target_link_libraries(LandmassTool Qt5::OpenGL)
target_link_libraries(LandmassTool Qt5::Xml)
target_link_libraries(LandmassTool Qt5::Widgets)
target_link_libraries(LandmassTool ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
