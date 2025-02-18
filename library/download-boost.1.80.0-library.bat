:: Remarks Print all information on console
@echo ON

:: Remarks Source file location
set source='https://sourceforge.net/projects/boost/files/boost/1.80.0/boost_1_80_0.zip/download'

:: Remarks File name
set fileName="boost_1_80_0.zip"

:: Remarks Directory for extracting Boost library
set extractedFolderPath="../library"

:: Remarks Download the file
powershell -Command "(New-Object Net.WebClient).DownloadFile(%source%, %fileName%)"

:: Remarks Extract library
where 7z >nul 2>nul
if %errorlevel% equ 0 (
    echo Using 7-Zip to extract "%fileName%"...
    7z x "%fileName%" -o"%extractedFolderPath%"
    if %errorlevel% neq 0 (
        echo Failed to extract with 7-Zip.
        exit /b 1
    )
) else (
    echo 7-Zip not found. Using default extraction...
    powershell Expand-Archive %fileName% -DestinationPath %extractedFolderPath%
    if %errorlevel% neq 0 (
        echo Failed to extract with default method.
        exit /b 1
    )
)