cmake_minimum_required(VERSION 3.26)
project("OITools::Source-Wrapper")

# settings
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
	message("Release mode.")
	add_compile_options(-O3 -Wall -DNDEBUG)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build/Release/)
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
	message("Debug mode.")
	add_compile_options(-g -Wall)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build/Debug/)
else()
	message(FATAL_ERROR "Unknown build type.")
endif()

# requires
find_package(Boost COMPONENTS filesystem REQUIRED)

# main
aux_source_directory(src/core core_src_list)
include_directories(src/base)
add_executable(oit-wrap src/main.cpp ${core_src_list})
target_link_libraries(oit-wrap ${Boost_LIBRARIES})

# installing
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(CMAKE_INSTALL_PREFIX "C:/Program Files/OITools/")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_INSTALL_PREFIX "/usr/local/")
endif()
install(TARGETS oit-wrap RUNTIME DESTINATION bin/)
