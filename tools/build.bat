@echo off

setlocal enabledelayedexpansion
set arg=%1

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

rem Change directory to the project root
popd

if not exist obj mkdir obj
if not exist bin mkdir bin
if not exist tests\obj mkdir tests\obj
if not exist tests\bin mkdir tests\bin

if not defined arg goto :main

if %arg%==clean (
    del /S /Q bin\*.dll bin\*.exe bin\*.lib bin\*.pdb bin\*.ilk bin\*.exp > nul 2>&1
    del /S /Q obj\*.obj obj\*.pdb > nul 2>&1
    del /S /Q tests\obj\*.obj tests\obj\*.pdb > nul 2>&1 
    del /S /Q tests\bin\*.dll tests\bin\*.exe tests\bin\*.lib tests\bin\*.pdb^
        tests\bin\*.ilk tests\bin\*.exp > nul 2>&1

    goto :eof
)

:main

set dll=libcspd.dll
set exe=libcspd.exe
set flags=compile_flags.txt

rem/||(
Store the absolute ^path of the project root directory in a variable 
followed by a slash to stay consistent with `~dp0` when using 
functions ^for splitting strings and ^set the comparator variable. ^)
)
set root=%cd%\
set cmp=!root:~0,-1!

echo | set /p clear="" > %flags%

rem Recursively call all include directories
for /r include %%F in (*.h) do (
    call :include %%F
)

rem Recursively call required lib includes
for /r lib\logc %%F in (*.h) do (
    call :include %%F
)

rem End of entry point procedure
goto :main

rem Set all relative include directory paths
:include
rem Reference the absolute and relative paths of the header file
set "abspath=%~dp1"
set "relpath=!abspath:%cmp%=!"

rem Prevent duplicate include directories
if !prev! neq !relpath! (
    call set "incs=%%incs%% -I..!relpath:~0,-1!"

    rem Invert slashes for include paths to be compatible with the LSP
    set cpath=!relpath:\=/!
    echo -I>> %flags%
    echo .!cpath!>> %flags%

    set "prev=!relpath!"
)

rem Terminate :include subroutine call
goto :eof

:main
pushd obj

rem Recursively set all relative file paths of *.c source files
for /r ..\src %%F in (*.c) do ( 
    call :sources %%F
)

rem Recursively set all relative file paths of *.c lib\logc *c files
for /r ..\lib\logc %%F in (*.c) do ( 
    call :sources %%F
)

goto :compile

:sources
    set "abspath=%1"
    set "relpath=!abspath:%cmp%=!"
    call set "srcs=%%srcs%% ..!relpath!"

rem Terminate :sources subroutine call
goto :eof

:compile
rem Compile *.c files
cl /c /MD -Zi -W4 -Wall %incs% /std:c17 %srcs:~1%

popd
pushd bin

rem Store all *.obj file names only for the linker
for /r ..\obj %%F in (*.obj) do (
    call set "objs=%%objs%% ..\obj\%%~nxF"
)

:link
rem Link *.obj object files
LINK /nologo /DEBUG %objs:~1% /DLL /OUT:%dll% /DEF:..\libcspd.defs

rem Copy DLL to where the test executable will be built
copy ..\bin\%dll% ..\tests\bin\%dll% > nul

rem Store all *.test.c source files in a variable
for /r ..\tests %%F in (*.test.c) do ( 
    call set "testsrcs=%%testsrcs%% %%~nxF"
)

popd
pushd tests

rem Compile test program and link DLL

rem Compile *.test.c files
cl /nologo /Fo"obj\\" /Fd"obj\\" /c /MD -Zi -W4 -Wall /std:c17 %testsrcs% %incs%

rem Store all *.test.obj file names only for the linker
for /r obj %%F in (*.test.obj) do (
    call set "testobjs=%%testobjs%% obj\%%~nxF"
)

rem Link *.test.obj object files
LINK /DEBUG %testobjs:~1% /OUT:bin\%exe% ..\bin\libcspd.lib 

popd
