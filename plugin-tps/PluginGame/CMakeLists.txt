cmake_minimum_required(VERSION 3.2.1)

project(PluginGame)

include_directories("${SH_ROOT_DIR}/include")

if (WIN32)
	find_package(DirectX9 REQUIRED)
	include_directories("${DirectX9_INCLUDE_DIR}")
endif (WIN32)

set(SOURCES_CSHPLUGINGAME CShPluginGame.cpp CShPluginGame.h)
source_group("TPS" FILES ${SOURCES_CSHPLUGINGAME})

# Compile to use it on Runtime
add_library(PluginGame STATIC ${SOURCES_CSHPLUGINGAME})
set_property(TARGET PluginGame PROPERTY FOLDER "Runtime")
set_property(TARGET PluginGame APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET PluginGame APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

# Compile to use it in the Shine Editor
add_library(PluginGame_Editor OBJECT ${SOURCES_CSHPLUGINGAME})
set_property(TARGET PluginGame_Editor PROPERTY FOLDER "Editor")
set_property(TARGET PluginGame_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET PluginGame_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")
set_property(TARGET PluginGame_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1")
set_property(TARGET PluginGame_Editor APPEND PROPERTY COMPILE_DEFINITIONS "_INTERNAL_DLL")
