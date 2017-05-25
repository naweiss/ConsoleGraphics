@echo off
cd %1
set str=%2
call set str=%%str%:cpp=exe%%
:: start the compiled exe
:: Note:start has problem with "" in the first argument
start "" %str%