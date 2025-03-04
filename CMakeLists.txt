cmake_minimum_required(VERSION 3.2)

project(file-manager VERSION 0.0.1 LANGUAGES CXX)

set(
    START
        src/main.cpp
)

set(
    CORE
		src/far.h src/far.cpp
		src/status.h src/status.cpp
)

# Set DEFAULT install (README.md points to this line)
set (FIRST_BOOST_INSTALL ON)

if(FIRST_BOOST_INSTALL)
	# Include default library/boost_1_80_0
    include(./library/CMakeLists.txt)
endif()

# Only find static libs
set(Boost_USE_STATIC_LIBS ON)

# Ignore debug libs and
set(Boost_USE_DEBUG_LIBS OFF)

# Only find release libs
set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

if(WIN32)
	# Switch BOOST_ROOT and BOOST_LIBRARYDIR if FIRST_BOOST_INSTALL != ON
    set (BOOST_ROOT "./library/boost_1_80_0")
    set (BOOST_LIBRARYDIR "./library/boost_1_80_0/stage/lib")
endif()

add_executable(${PROJECT_NAME} ${START} ${CORE})

find_package(Boost 1.80.0 COMPONENTS date_time REQUIRED)

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

# Enable testing functionality
set(ENABLE_TESTING ON)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(./test)
endif()
