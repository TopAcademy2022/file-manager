option(
    FILE_MANAGER_AUTO_INSTALL_BOOST
    "Download and build the required Boost libraries automatically on Windows"
    ON
)

set(FILE_MANAGER_BOOST_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/library/boost_1_80_0"
)
set(FILE_MANAGER_BOOST_LIBRARY_DIR
    "${FILE_MANAGER_BOOST_ROOT}/stage/lib"
)

# The repository scripts own the complete Windows dependency workflow. CMake
# only invokes them and then points FindBoost at their deterministic output.
if(WIN32 AND FILE_MANAGER_AUTO_INSTALL_BOOST)
    if(NOT MSVC)
        message(FATAL_ERROR
            "Automatic Boost installation currently supports MSVC on Windows. "
            "Disable FILE_MANAGER_AUTO_INSTALL_BOOST to use another toolchain."
        )
    endif()

    math(EXPR FILE_MANAGER_ADDRESS_MODEL "${CMAKE_SIZEOF_VOID_P} * 8")
    if(MSVC_TOOLSET_VERSION MATCHES "^([0-9][0-9])([0-9])$")
        set(FILE_MANAGER_BOOST_TOOLSET "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}")
    elseif(MSVC_VERSION GREATER_EQUAL 1930)
        set(FILE_MANAGER_BOOST_TOOLSET "14.3")
    elseif(MSVC_VERSION GREATER_EQUAL 1920)
        set(FILE_MANAGER_BOOST_TOOLSET "14.2")
    else()
        set(FILE_MANAGER_BOOST_TOOLSET "14.1")
    endif()
    set(FILE_MANAGER_BOOST_INSTALL_SCRIPT
        "${CMAKE_CURRENT_SOURCE_DIR}/library/install-boost.1.80.0-library.bat"
    )

    execute_process(
        COMMAND
            cmd.exe /d /c call
            "${FILE_MANAGER_BOOST_INSTALL_SCRIPT}"
            "${FILE_MANAGER_ADDRESS_MODEL}"
            "${FILE_MANAGER_BOOST_TOOLSET}"
            "${CMAKE_GENERATOR_INSTANCE}"
        RESULT_VARIABLE FILE_MANAGER_BOOST_INSTALL_RESULT
    )

    if(NOT FILE_MANAGER_BOOST_INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR
            "The Boost installation script failed with exit code "
            "${FILE_MANAGER_BOOST_INSTALL_RESULT}."
        )
    endif()

    set(BOOST_ROOT "${FILE_MANAGER_BOOST_ROOT}")
    set(BOOST_LIBRARYDIR "${FILE_MANAGER_BOOST_LIBRARY_DIR}")
    set(Boost_ROOT "${FILE_MANAGER_BOOST_ROOT}")
endif()

set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_WARN_NEW_VERSIONS ON)

find_package(
    Boost 1.75
    REQUIRED COMPONENTS
    date_time
    unit_test_framework
)

message(STATUS "Using Boost ${Boost_VERSION_STRING} from ${Boost_INCLUDE_DIRS}")
