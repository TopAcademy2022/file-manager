@echo off
setlocal EnableExtensions EnableDelayedExpansion

set "ADDRESS_MODEL=%~1"
if not defined ADDRESS_MODEL set "ADDRESS_MODEL=64"
set "TOOLSET_VERSION=%~2"
if not defined TOOLSET_VERSION set "TOOLSET_VERSION=14.3"
set "VS_INSTALL=%~3"

set "BOOST_DIR=%~dp0boost_1_80_0"
set "STAGE_DIR=%BOOST_DIR%\stage"
set "BUILD_STAMP=%STAGE_DIR%\.file-manager-v3-msvc-%TOOLSET_VERSION%-%ADDRESS_MODEL%.stamp"

call "%~dp0download-boost.1.80.0-library.bat"
if errorlevel 1 exit /b %ERRORLEVEL%

if exist "%BUILD_STAMP%" (
    echo Required Boost libraries are already built for %ADDRESS_MODEL%-bit targets.
    exit /b 0
)

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined VS_INSTALL if exist "!VSWHERE!" (
    for /f "usebackq delims=" %%I in (`"!VSWHERE!" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VS_INSTALL=%%I"
)
if not defined VS_INSTALL if defined VSINSTALLDIR set "VS_INSTALL=%VSINSTALLDIR%"
if not defined VS_INSTALL (
    echo A Visual Studio installation with C++ tools was not found.
    exit /b 1
)

set "VCVARSALL=!VS_INSTALL!\VC\Auxiliary\Build\vcvarsall.bat"
if not exist "!VCVARSALL!" (
    echo Visual Studio vcvarsall.bat was not found.
    exit /b 1
)

if "%ADDRESS_MODEL%"=="32" (
    set "VCVARS_ARCH=x86"
) else (
    set "VCVARS_ARCH=amd64"
)

where cl.exe >nul 2>nul
if errorlevel 1 (
    echo Activating the Visual Studio C++ toolchain...
    call "!VCVARSALL!" !VCVARS_ARCH!
    if errorlevel 1 (
        echo Visual Studio C++ toolchain activation failed.
        exit /b !ERRORLEVEL!
    )
)

if not exist "%BOOST_DIR%\b2.exe" (
    echo Bootstrapping Boost.Build...
    pushd "%BOOST_DIR%"
    call bootstrap.bat
    set "BOOTSTRAP_RESULT=!ERRORLEVEL!"
    popd

    if not "!BOOTSTRAP_RESULT!"=="0" (
        echo Boost.Build bootstrap failed.
        exit /b !BOOTSTRAP_RESULT!
    )
)

set "VCVARSALL_JAM=!VCVARSALL:\=/!"
(
    echo import option ;
    echo using msvc : %TOOLSET_VERSION% : cl.exe : ^<setup^>"!VCVARSALL_JAM!" ;
    echo option.set keep-going : false ;
) > "%BOOST_DIR%\project-config.jam"

set "JOBS=%NUMBER_OF_PROCESSORS%"
if not defined JOBS set "JOBS=2"

echo Building Boost.DateTime and Boost.Test for %ADDRESS_MODEL%-bit targets...
pushd "%BOOST_DIR%"
b2.exe ^
    --with-date_time ^
    --with-test ^
    toolset=msvc-%TOOLSET_VERSION% ^
    architecture=x86 ^
    address-model=%ADDRESS_MODEL% ^
    variant=debug,release ^
    link=static ^
    runtime-link=shared ^
    threading=multi ^
    --stagedir=stage ^
    -j%JOBS% ^
    stage
set "BUILD_RESULT=%ERRORLEVEL%"
popd

if not "%BUILD_RESULT%"=="0" (
    echo Building the required Boost libraries failed.
    exit /b %BUILD_RESULT%
)

if not exist "%STAGE_DIR%\lib\*boost_date_time*.lib" (
    echo Boost.DateTime was not created in the expected stage directory.
    exit /b 1
)

if not exist "%STAGE_DIR%\lib\*boost_unit_test_framework*.lib" (
    echo Boost.Test was not created in the expected stage directory.
    exit /b 1
)

type nul > "%BUILD_STAMP%"
echo Required Boost libraries are ready in "%STAGE_DIR%\lib".
