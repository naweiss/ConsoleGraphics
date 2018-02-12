@echo off
REM - Split the path given to directory and main file
REM - Determine the library path
set dir=%~dp1
set main=%~nx1
set library=%~dp0%Library

REM If main file given check it exists
if "%main%" neq "" (
	if not exist %1 (
		echo usage:
		echo    compile.bat  ^<main_file_path^>
		echo.
		echo example:
		echo     - compile the library itself:
		echo         .\compile.bat .\Library\
		echo.
		echo     - compile user code:
		echo         .\compile.bat .\SomeCodeDir\main.cpp
		echo.
		exit
	)
)

REM Require cl
set vs17comntools=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\
call "%vs17comntools%vcvars32.bat"

REM Cd to the code directory
cd "%dir%"
REM Create directory for obj files
if not exist OBJECT mkdir OBJECT

REM Compile the library itself
if "%dir%" == "%library%\" (
	for /r "%dir%" %%F in (*.cpp) do (
		call cl /c /EHsc "%%F" /FoOBJECT\
	)
	pause
	exit
)

REM Create obj files
for /r "%dir%" %%F in (*.cpp) do (
	call cl /c /EHsc "%%F" /FoOBJECT\ /I "%library%"
)
REM List all obj files
for /r "%dir%OBJECT\" %%F in (*.obj) do (
	call set "list=%%list%% "%%F""
)
for /r "%library%\OBJECT\" %%F in (*.obj) do (
	call set "list=%%list%% "%%F""
)

REM Choose name for exe file based on main file
call set out=%%main%:cpp=exe%%
REM Link all the obj file to an exe file
link %list% user32.lib gdi32.lib msimg32.lib /OUT:%out%
pause
REM Run the code
start "" "%out%"