@echo off
REM Cd to the code directory given in first argument
cd %1
REM Convert potentialy relative path to absolute path
set current=%cd%
REM Find this bat file parent folder
set library=%~dp0%Library
REM Require cl
set vs17comntools=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\
call "%vs17comntools%vcvars32.bat"
REM Cd to the code directory given in first argument
cd "%current%"
REM Create directory for obj files
if not exist OBJECT mkdir OBJECT
REM Compile the library itself
if "%current%" == "%library%" (
	for /r "%current%" %%F in (*.cpp) do (
		call cl /c /EHsc "%%F" /FoOBJECT\
	)
	pause
	exit
)
if not exist %2 (
	echo [!] Main file invalid
	pause
	exit
)
REM Create obj files
for /r "%current%" %%F in (*.cpp) do (
	call cl /c /EHsc "%%F" /FoOBJECT\ /I "%library%"
)
REM List all obj files
for /r "%current%\OBJECT\" %%F in (*.obj) do (
	call set "list=%%list%% "%%F""
)
for /r "%library%\OBJECT\" %%F in (*.obj) do (
	call set "list=%%list%% "%%F""
)
REM Choose name for exe file based on main file (second argumnet)
set str=%2
call set str=%%str%:cpp=exe%%
REM Link all the obj file to an exe file
link %list% user32.lib gdi32.lib msimg32.lib /OUT:%str%
pause
REM Run the code
start "" %str%