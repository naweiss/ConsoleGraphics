@echo off
cd %1
set home=C:\Users\nadav\Desktop\SoloProjects\ConsoleGraphics
call "%vs140comntools%vsvars32.bat"
if %1 == "%home%\Library" (
	for /r %1 %%F in (*.cpp) do (
		call cl /c /EHsc "%%F" /FoOBJECT\
	)
	pause
	exit
)
if not exist OBJECT\ mkdir OBJECT
for /r %1 %%F in (*.cpp) do (
	call cl /c /EHsc "%%F" /FoOBJECT\ /I "%home%\Library"
)
for /r %1\OBJECT\ %%F in (*.obj) do call set "list=%%list%% "%%F""
for /r "%home%\Library\OBJECT\" %%F in (*.obj) do call set "list=%%list%% "%%F""
set str=%2
call set str=%%str%:cpp=exe%%
link %list% user32.lib gdi32.lib msimg32.lib /OUT:%str%
pause
start "" %str%