@echo off
REM Split the path given to directory and main file
set dir=%~dp1
set main=%~nx1

REM Check the main file exist
if not exist %1 (
	echo usage:
	echo    run.bat  ^<main_file_path^>
	echo.
	echo example:
	echo     - compile user code:
	echo         .\run.bat .\SomeCodeDir\main.cpp
	echo.
	exit
)

REM Cd to the code directory
cd %dir%
REM Choose name for exe file based on main file
call set out=%%main%:cpp=exe%%

REM start the compiled exe
REM Note:start has problem with "%out%" in the first argument
start "" "%out%"