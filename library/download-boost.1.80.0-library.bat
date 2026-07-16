@echo off
setlocal

set "BOOST_URL=https://archives.boost.io/release/1.80.0/source/boost_1_80_0.7z"
set "BOOST_SHA256=D12A2AF721E22DBFB984EF061EE4C4AB2387F1904F6D65BC5ACEBAA34D6366EC"
set "BOOST_DIR=%~dp0boost_1_80_0"
set "CACHE_DIR=%~dp0.cache"
set "ARCHIVE=%CACHE_DIR%\boost_1_80_0.7z"
set "PART=%ARCHIVE%.part"

if exist "%BOOST_DIR%\boost\version.hpp" (
    echo Boost 1.80.0 is already available in "%BOOST_DIR%".
    exit /b 0
)

where cmake >nul 2>nul
if errorlevel 1 (
    echo CMake is required to extract the Boost archive.
    exit /b 1
)

if not exist "%CACHE_DIR%" mkdir "%CACHE_DIR%"

if not exist "%ARCHIVE%" (
    echo Downloading Boost 1.80.0...
    where curl.exe >nul 2>nul
    if not errorlevel 1 (
        curl.exe --fail --location --progress-bar --continue-at - --output "%PART%" "%BOOST_URL%"
    ) else (
        powershell -NoProfile -Command ^
            "$ProgressPreference = 'Continue'; Invoke-WebRequest -Uri '%BOOST_URL%' -OutFile '%PART%'"
    )
    if errorlevel 1 (
        echo Boost download failed. Re-run this script to retry.
        exit /b 1
    )
    move /y "%PART%" "%ARCHIVE%" >nul
)

for /f "usebackq delims=" %%H in (`powershell -NoProfile -Command "(Get-FileHash -Algorithm SHA256 -LiteralPath '%ARCHIVE%').Hash"`) do set "ACTUAL_SHA256=%%H"
if /i not "%ACTUAL_SHA256%"=="%BOOST_SHA256%" (
    echo The downloaded Boost archive has an invalid SHA256 checksum.
    exit /b 1
)

echo Extracting Boost 1.80.0...
pushd "%~dp0"
cmake -E tar xf "%ARCHIVE%"
set "EXTRACT_RESULT=%ERRORLEVEL%"
popd

if not "%EXTRACT_RESULT%"=="0" (
    echo Boost extraction failed.
    exit /b %EXTRACT_RESULT%
)

if not exist "%BOOST_DIR%\boost\version.hpp" (
    echo Boost extraction did not produce the expected directory.
    exit /b 1
)

echo Boost 1.80.0 sources are ready in "%BOOST_DIR%".
