@if exist %~n1.obj del %~n1.obj
@if exist %~n1.exe del %~n1.exe

call nasm -fwin32 %~n1.asm
@if not exist %~n1.obj pause
