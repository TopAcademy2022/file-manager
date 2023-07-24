cmake_minimum_required(VERSION 3.0)

if(FIRST_BOOST_INSTALL)
	if(WIN32)
		execute_process(COMMAND powershell ../library/download-boost.1.80.0-library.bat)
		execute_process(COMMAND powershell ../library/install-boost.1.80.0-library.bat)
	endif()
endif()