@ECHO OFF

set file=Lab2

ECHO Compilation...
tasm.exe /m8 /l %file%.asm
tlink.exe /v %file%.obj, _%file%.exe
ECHO Deleting unnecessary files...
::del %file%.lst
del %file%.obj
del _%file%.map
ECHO [START PROGRAM]
_%file%.exe
ECHO [END   PROGRAM]