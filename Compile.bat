@ECHO OFF

ECHO Compilation...
tasm.exe %~1.asm
tlink.exe /v %~1.obj, _%~1.exe
ECHO Deleting unnecessary files...
del %~1.lst
del %~1.obj
del _%~1.map
ECHO [START PROGRAM]
_%~1.exe
ECHO [END   PROGRAM]