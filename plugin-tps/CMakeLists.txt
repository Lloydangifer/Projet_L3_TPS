cmake_minimum_required(VERSION 3.2.1)

project(TPS)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SH_ROOT_DIR "../Shine" CACHE PATH "Shine root directory")


add_subdirectory(PluginGame)

add_subdirectory(Extension)