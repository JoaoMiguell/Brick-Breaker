# CMakeList.txt : CMake project for GnsTwo, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GnsTwo "GnsTwo.cpp" "GnsTwo.h")
add_custom_command(
    TARGET ${PROJECT_NAME}  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/GnsTwo/assets
            ${PROJECT_BINARY_DIR}/GnsTwo/assets)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GnsTwo PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
find_package(raylib CONFIG REQUIRED)
target_link_libraries(GnsTwo PRIVATE raylib)