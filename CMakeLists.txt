cmake_minimum_required(VERSION 3.25)

# !!! Change this line to the name of your project !!!
project(DYEditorTemplateProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DYE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extern/DYEngine)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${DYE_PATH}/cmake/Modules/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${DYE_PATH}/DYEditor/cmake/Modules/")
include(RedirectOutputTo)
include(DYEditorProject)

# Redirect built binaries output directory.
if (CMAKE_BUILD_TYPE MATCHES Debug)
    RedirectOutputTo("build/Debug")
    add_compile_definitions(DYE_DEBUG)
    add_compile_definitions(DYE_OPENGL_DEBUG)
elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    RedirectOutputTo("build/RelWithDebInfo")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    RedirectOutputTo("build/Release")
elseif (CMAKE_BUILD_TYPE MATCHES MinSizeRel)
    RedirectOutputTo("build/MinSizeRel")
endif ()

# !!! Include your source files here !!!
set(SOURCE_FILES
        src/CreateApplication.cpp)

# !!! Include your header files here !!!
set(HEADER_FILES
        include/Components/ExampleComponent.h
        include/Systems/ExampleSystem.h)

set(INCLUDE_DIRS
        include
        ${CMAKE_CURRENT_SOURCE_DIR})

# Build DYEngine & DYEditor.
add_subdirectory(extern/DYEngine/DYEngine)
add_subdirectory(extern/DYEngine/DYEditor)

# Be sure to add "" around INCLUDE_DIRS, SOURCE_FILES and HEADER_FILES to make them arrays.
DYEditor_AddEditorExecutable(${PROJECT_NAME}_Editor "${CMAKE_CURRENT_SOURCE_DIR}" "${INCLUDE_DIRS}" "${SOURCE_FILES}" "${HEADER_FILES}")
#DYEditor_AddRuntimeExecutable(${PROJECT_NAME}_Runtime "${CMAKE_CURRENT_SOURCE_DIR}" "${INCLUDE_DIRS}" "${SOURCE_FILES}" "${HEADER_FILES}")
