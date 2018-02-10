@echo off
REM Cd to the code directory given in first argument
cd %1
REM Choose name for exe file based on main file (second argumnet)
set str=%2
call set str=%%str%:cpp=exe%%
REM start the compiled exe
REM Note:start has problem with "%str%" in the first argument
start "" %str%