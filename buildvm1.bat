@ECHO OFF

CALL compileasm execute.asm

@CALL "%VS100COMNTOOLS%vsvars32.bat"

"%VCINSTALLDIR%\bin\cl" /MD /c /Od /FAs /TC /W0 /GS- vm1.c /nologo

"%VCINSTALLDIR%\bin\link" /nologo vm1.obj execute.obj LDE64.lib /section:.text,WE
