@ECHO OFF

set comeback=%~dp0%

cd %~1

set program=%PROGRAMFILES%\Notepad++\notepad++.exe

start "" "%program%" *.inc
start "" "%program%" *.asm

cd %comeback%