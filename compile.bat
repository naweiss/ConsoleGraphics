@echo off
cd %1
:: Load compilation environment
call "%vs140comntools%vsvars32.bat"
:: Invoke compiler with any options passed to this batch file
:: /Wall for warnings
call cl /EHsc %2 /IC:\Users\nadav\Desktop\SoloProjects\ConsoleGraphics user32.lib gdi32.lib msimg32.lib
set str=%2
call set str=%%str%:cpp=exe%%
pause
:: start the compiled exe
:: Note:start has problem with "" in the first argument
start "" %str%