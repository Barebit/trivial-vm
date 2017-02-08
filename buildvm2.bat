@ECHO OFF

CALL compileasm execute.asm

@CALL "%VS100COMNTOOLS%vsvars32.bat"

"%VCINSTALLDIR%\bin\cl" /MT /c /Od /FAs /TC /W0 /GS- vm2.c /nologo

"%VCINSTALLDIR%\bin\link" /nologo vm2.obj execute.obj LDE64.lib /section:.text,WE
