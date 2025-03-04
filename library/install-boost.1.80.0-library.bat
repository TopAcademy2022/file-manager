:: Remarks Print all information on console
@echo ON

:: Remarks Get compile type
set compilerType=%1

:: Remarks Folder with Boost library name
set folderName=../library/boost_1_80_0

:: Remarks Init Boost library before install
set boostLibraryIniScriptName=bootstrap.bat

if exist '%folderName%' (
    echo Folder exist
) else (
	:: Remarks Call init script
	cd %folderName%
	
	
	:: Remarks Install Boost library
	if "%compilerType%" == "msvc" (
		:: Remarks Install Boost library
		for /f "delims=" %%i in ('where cl') do set CL_PATH=%%i
		set CL="%CL_PATH%"
		powershell -Command "./b2 --clean-all"
    	powershell -Command "./b2 toolset=msvc-14.0 address-model=64 -a install --release --with-date_time --with_unit_test_framework -j4"
	) else if "%compilerType%" == "%gcc%" (
		powershell -Command "./b2 --clean-all"
		powershell -Command "./b2 -j -a install --release"
	) else (
		echo The variable "%compilerType%" is neither equal.
	)
)