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
	call %boostLibraryIniScriptName%
	
	:: Remarks Install Boost library
	if "%compilerType%" == "msvc" (
    	powershell -Command "./b2 toolset=msvc-14.0 address-model=64 -a install"
	) else if "%compilerType%" == "%gcc%" (
		powershell -Command "./b2 -a install"
	) else (
		echo The variable "%compilerType%" is neither equal.
	)
)