@echo off

setlocal enabledelayedexpansion

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

rem Change directory to the project root
popd

if not exist etc mkdir etc
if not exist obj mkdir obj
if not exist bin mkdir bin

del /S /Q obj\*.* > nul
del /S /Q bin\*.* > nul

rem/||(
    Store the absolute ^path of the project root directory in a variable 
    followed by a slash to stay consistent with `~dp0` when using 
    functions ^for splitting strings. ^)
)
set root=%cd%\
set cmp=!root:~0,-1!

pushd obj

rem Store all relative file paths of *.c files into a variable for compilation
for /r ..\src %%f in (*.c) do ( 
    set "abspath=%%f"
    set "relpath=!abspath:%cmp%=!"
    call set "srcs=%%srcs%% ..!relpath!"
)

rem Compile *.c files
cl /c -Zi /std:c11 %srcs:~1%

popd
pushd bin

rem Store all *.obj file names only for the linker
for /r ..\obj %%f in (*.obj) do (
    call set "objs=%%objs%% ..\obj\%%~nxf"
)

rem Link object files
LINK /DEBUG %objs:~1% /OUT:main.exe user32.lib gdi32.lib

popd
