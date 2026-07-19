@echo off
setlocal enabledelayedexpansion

:: ANSI color setup
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "BLUE=%ESC%[34m"
set "GREEN=%ESC%[32m"
set "RED=%ESC%[31m"
set "RESET=%ESC%[0m"

echo %BLUE%leetcode-solutions run single test%RESET%
echo.

:: Step 1: Navigate to the ROOT of the repository 
:: (%~dp0 gets the script's current directory (tests/scripts/), \..\.. moves up two levels to the root)
cd /d "%~dp0\..\.."

:: Step 2: Compile the runner
echo %BLUE%Step 1: Compiling singleTestRunner.cpp...%RESET%
g++ -std=c++20 tests\singleTestRunner.cpp -o tests\singleTestRunner.exe

:: Check if compilation failed
if %errorlevel% neq 0 (
    echo.
    echo %RED%[ERROR] Compilation failed!%RESET%
    pause
    exit /b %errorlevel%
)
echo %GREEN%Compilation successful.%RESET%
echo.

:: Step 3: Run the executable from the ROOT directory
echo %BLUE%Step 2: Running Single Test%RESET%
tests\singleTestRunner.exe

:: Check execution result
if %errorlevel% neq 0 (
    echo.
    echo %RED%[FAILED] Some tests did not pass or the runner crashed.%RESET%
) else (
    echo.
    echo %GREEN%[SUCCESS] All tests passed!%RESET%
)

:: Step 4: Clean up the generated executable to keep your root directory clean
if exist singleTestRunner.exe del singleTestRunner.exe

echo.
:: Pause at the very end so the window stays open to read the results
pause