@echo off

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

if not exist etc mkdir etc
if not exist obj mkdir obj
if not exist bin mkdir bin

del /S /Q obj\*.* > nul
del /S /Q bin\*.* > nul

pushd obj

for /r ..\src %%f in (*.c) do (
    call set "srcs=%%srcs%% ..\src\%%~nxf"
)

cl /c -Zi /std:c11 %srcs:~1%

popd
pushd bin

for /r ..\obj %%f in (*.obj) do (
    call set "objs=%%objs%% ..\obj\%%~nxf"
)

LINK /DEBUG %objs:~1% /OUT:main.exe user32.lib gdi32.lib

popd
