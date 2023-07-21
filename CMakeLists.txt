cmake_minimum_required(VERSION 3.0)

project(file-manager VERSION 0.0.1 LANGUAGES CXX)

set(
    START
        src/main.cpp
)

set(
    CORE
		src/far.h
		src/far.cpp
		src/status.h
		src/status.cpp
)

# Only find static libs
set(Boost_USE_STATIC_LIBS ON)

# Ignore debug libs and
set(Boost_USE_DEBUG_LIBS OFF)

# Only find release libs
set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Set boost library dir (README.md points to the line)
set (BOOST_LIBRARYDIR "./libs/lib")

add_executable(${PROJECT_NAME} ${START} ${CORE})

find_package(Boost 1.45.0 COMPONENTS date_time REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::date_time)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    src/
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)