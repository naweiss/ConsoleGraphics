@echo off
REM cd %1
REM :: Load compilation environment
REM call "%vs140comntools%vsvars32.bat"
REM :: Invoke compiler with any options passed to this batch file
REM :: /Wall for warnings
REM call cl /EHsc %2 /I C:\Users\nadav\Desktop\SoloProjects\ConsoleGraphics user32.lib gdi32.lib msimg32.lib
REM set str=%2
REM call set str=%%str%:cpp=exe%%
REM pause
REM :: start the compiled exe
REM :: Note:start has problem with "" in the first argument
REM start "" %str%

cd %1
call "%vs140comntools%vsvars32.bat"
for /r %1 %%F in (*.cpp) do (
call cl /c /EHsc %%F
)
for /r %1 %%F in (*.obj) do (call set "list=%%list%% %%F")
set str=%2
call set str=%%str%:cpp=exe%%
link %list% user32.lib gdi32.lib msimg32.lib /OUT:%str%
pause
start "" %str%