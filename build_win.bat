@echo off

@REM Example use: ./build_win.bat release mingw-release-17 

set BUILD_TYPE_ARG=release
set CONAN_PROFILE=default

if not "%~1" == "" (
    set BUILD_TYPE_ARG=%~1
)

if not "%~2" == "" (
    set CONAN_PROFILE=%~2
)

echo Building with configuration: %BUILD_TYPE_ARG%
echo Using Conan profile: %CONAN_PROFILE%
echo.

echo [1/3] Running conan install...
conan install . -pr:a %CONAN_PROFILE% -b missing
if %errorlevel% neq 0 (
    echo Error: conan install failed
    exit /b %errorlevel%
)

echo [2/3] Configuring CMake...
cmake --preset conan-%BUILD_TYPE_ARG%
if %errorlevel% neq 0 (
    echo Error: cmake configure failed
    exit /b %errorlevel%
)

echo [3/3] Building project...
cmake --build --preset conan-%BUILD_TYPE_ARG%
if %errorlevel% neq 0 (
    echo Error: cmake build failed
    exit /b %errorlevel%
)

echo "CGL-Graphics build done!"

echo "Running app.."
start "" "build\%BUILD_TYPE_ARG%\cglg.exe"

exit /b 0