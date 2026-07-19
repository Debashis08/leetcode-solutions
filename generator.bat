@echo off
setlocal enabledelayedexpansion

:: ANSI color setup
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "BLUE=%ESC%[34m"
set "GREEN=%ESC%[32m"
set "RED=%ESC%[31m"
set "RESET=%ESC%[0m"

echo %BLUE%Compiling Generator...%RESET%

:: Navigate to the script's directory (Repo Root)
cd /d "%~dp0"

:: Compile the C++ generator using C++17 (required for <filesystem>)
g++ -std=c++17 generator.cpp -o generator.exe

:: Check if compilation failed
if %errorlevel% neq 0 (
    echo.
    echo %RED%[ERROR] Compilation failed! Check generator.cpp.%RESET%
    pause
    exit /b %errorlevel%
)

:: Clear the screen and run the generator
cls
generator.exe

:: Clean up the executable after it runs
del generator.exe

echo.
pause