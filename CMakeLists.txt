cmake_minimum_required(VERSION 3.25)
project(jeffs-adventure CXX)

set(JEFF_DEFAULT_BUILD_TYPE "Debug")

# Source: https://www.kitware.com/cmake-and-the-default-build-type/
# Set the build type if it was not specified (only in single-config generators).
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${JEFF_DEFAULT_BUILD_TYPE}' as none was specified.")
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "${JEFF_DEFAULT_BUILD_TYPE}")
endif()

# By default, install Jeff's Adventure inside the build directory.
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_BINARY_DIR}/out")
endif()

option(CMAKE_COLOR_DIAGNOSTICS "Enable colored diagnostics" YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

# Create the main executable.
add_executable(jeffs-adventure
	"Character.cpp"
	"Eraser.cpp"
	"Game.cpp"
	"Jeff.cpp"
	"Menu.cpp"
	"Platform.cpp"
	"Snippy.cpp"
	"Source.cpp"
)

# Require C++17 or later.
target_compile_features(jeffs-adventure PRIVATE cxx_std_17)

# No compiler-specific extensions (e.g. pass `-std=c++17` not `-std=gnu++17`):
set_target_properties(jeffs-adventure PROPERTIES CXX_EXTENSIONS NO)

# Search in `bin/` and `lib/` for libraries.
target_link_directories(jeffs-adventure PRIVATE "bin" "lib")

# Search in `include/` for headers.
target_include_directories(jeffs-adventure PRIVATE "include")

# Link against SFML's audio, graphics, windowing, and system libraries.
target_link_libraries(jeffs-adventure PRIVATE
	sfml-audio sfml-graphics sfml-window sfml-system
)

# Windows only: `sfml-main` provides the `WinMain()` entry point.
if(WIN32)
	# TODO: Remove the `find_library` call when SFML 3.1.0 is released:
	# https://github.com/SFML/SFML/pull/3431
	find_library(JEFF_SFML_MAIN
		NAMES "sfml-main" "sfml-main-s"
		NAMES_PER_DIR
		HINTS "${CMAKE_CURRENT_SOURCE_DIR}/lib"
		REQUIRED
	)
	target_link_libraries(jeffs-adventure PRIVATE "${JEFF_SFML_MAIN}")
endif()

# GCC/Clang only:
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	# Request additional warnings.
	target_compile_options(jeffs-adventure PRIVATE -Wall -Wextra -Wno-unused-parameter)

	# Debug only: enable extra debug information and UBSan.
	target_compile_options(jeffs-adventure PRIVATE $<$<CONFIG:Debug>:-g3 -fsanitize-trap=undefined>)
endif()

# Install the main executable directly inside the installation directory.
install(TARGETS jeffs-adventure DESTINATION ".")

# NOTE: "Directory names given as relative paths are interpreted [wrt] the current source directory."
# Source: https://cmake.org/cmake/help/latest/command/install.html#directory
install(
	# The final slash ensures that the contents of the `bin/` directory are
	# installed directly under the installation directory.
	DIRECTORY "bin/"
	DESTINATION "."
	PATTERN "bin/README.md" EXCLUDE
)

# Install the directories containing animation frames.
install(
	DIRECTORY "jeff_shooting" "jeff-walking" "Snippy"
	DESTINATION "."
)

# NOTE: "File names given as relative paths are interpreted [wrt] the current source directory."
# Source: https://cmake.org/cmake/help/latest/command/install.html#files
install(FILES
	"eraser.png"
	"jeff's-adventure-background-1.png"
	"jeff-standing-left.png"
	"jeff-standing.png"
	"mouseCursor.png"
	"Snippy-1.png"
	DESTINATION "."
)
