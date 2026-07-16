cmake_minimum_required(VERSION 3.14)

project(file-manager VERSION 0.0.1 LANGUAGES CXX)

# Keep FindBoost available on recent CMake versions. It locates the deterministic
# Boost tree and staged libraries prepared by the repository scripts.
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()
if(POLICY CMP0144)
    cmake_policy(SET CMP0144 NEW)
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/library/CMakeLists.txt")

add_library(
    file-manager-core
    src/far.cpp
    src/far.h
    src/status.cpp
    src/status.h
)
target_include_directories(
    file-manager-core
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(file-manager-core PUBLIC Boost::date_time)
target_compile_features(file-manager-core PUBLIC cxx_std_17)
set_target_properties(file-manager-core PROPERTIES CXX_EXTENSIONS OFF)

add_executable(file-manager src/main.cpp)
target_link_libraries(file-manager PRIVATE file-manager-core)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()
