@echo off
REM Expected input: FULL_PATH\MAIN_CPP_FILE OR FULL_LIBRARY_PATH
REM - Split the path given to directory and main file
REM - Determine the library path
set dir=%~dp1
set main=%~nx1
set library=%~dp0%Library

REM If main file given check it exists
if not "%main%" == "" (
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
echo [*] Initializing... 
set vs17comntools=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\
call "%vs17comntools%vcvars32.bat" > nul
echo [+] Ready 


REM Cd to the code directory
cd "%dir%"
REM Create directory for obj files
if not exist OBJECT mkdir OBJECT

REM Compile the library itself
if "%dir%" == "%library%\" (
	echo [*] Compiling library files... 
	for /r "%dir%" %%F in (*.cpp) do (
		echo | set /p prefix="[*] "
		call cl /c /EHsc "%%F" /FoOBJECT\ 2> nul
	)
	echo [+] Done
	pause
	exit
)

echo [*] Compiling files...
REM Create obj files
for /r "%dir%" %%F in (*.cpp) do (
	echo | set /p prefix="[*] "
	call cl /c /EHsc "%%F" /FoOBJECT\ /I "%library%" 2> nul
)
echo [+] Done

REM List all obj files
for /r "%dir%OBJECT\" %%F in (*.obj) do (
	call set "list=%%list%% "%%F""
)
for /r "%library%\OBJECT\" %%F in (*.obj) do (
	call set "list=%%list%% "%%F""
)

echo [*] Linking...
REM Choose name for exe file based on main file
call set out=%%main%:cpp=exe%%
REM Link all the obj file to an exe file
link %list% user32.lib gdi32.lib msimg32.lib /OUT:%out% > nul
echo [+] Done

pause
REM Run the code
start /MAX "" "%out%"