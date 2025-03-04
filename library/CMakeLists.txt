cmake_minimum_required(VERSION 3.0)

if(FIRST_BOOST_INSTALL)
	if(WIN32)
		# Download boost library
		##execute_process(COMMAND powershell ##../library/download-boost.1.80.0-library.bat)

		# Check compiler
		if(MSVC)
			execute_process(COMMAND powershell "../library/install-boost.1.80.0-library.bat msvc")
		elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			execute_process(COMMAND powershell "../library/install-boost.1.80.0-library.bat gcc")
		else()
			message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
		endif()
	endif()
endif()