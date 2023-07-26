:: Remarks Print all information on console
@echo ON

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
	powershell -Command "./b2 -a install"
)