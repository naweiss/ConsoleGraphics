@echo off
cd %1
:: Load compilation environment
call "%vs140comntools%vsvars32.bat"
:: Invoke compiler with any options passed to this batch file
:: /Wall for warnings
call cl %2 user32.lib gdi32.lib msimg32.LIB /EHsc /Fo:Output\ /Fe:Output\
set str=%2
call set str=%%str%:cpp=exe%%
pause
:: start the compiled exe
:: Note:start has problem with "" in the first argument
start Output/%str%