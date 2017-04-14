@ECHO OFF

set comeback=%~dp0%
set commitfoler="E:\TASM"

cd ..
robocopy "TASM" %commitfoler% *.asm *.inc *.bat /s

cd %comeback%