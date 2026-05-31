:: Script to compile and link the core standard library on Windows.

:: MSVC Compiler and Linker Options
:: https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
:: https://learn.microsoft.com/en-us/cpp/build/reference/linker-options

:: Windows Commands
:: https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/windows-commands

:: Addition to the standard help documentation on Windows commands
:: https://ss64.com/nt/

:: Variable names in :DevEnv use Microsoft visual Studio project codenames
:: https://en.wikipedia.org/w/index.php?title=Visual_Studio&oldid=1356912898#History

@echo off

setlocal enabledelayedexpansion

set Err=

set ArgCount=0
for %%I in (%*) do (
    set /A ArgCount+=1
    set "ArgVec[!ArgCount!]=%%~I"
)

rem Default fallback if MSVC does not automatically set platform
if "%Platform%"=="" set Platform=x64

rem Default build configuration
set Config=Debug
set CompilerOpts=-DDEBUG=1
set LinkerOpts=/DEBUG

rem Set project root directory
set Root=%~dp0..
for %%I in ("%Root%") do set "Root=%%~fI"

rem Process command-line arguments arguments
for /L %%I in (1,1,%ArgCount%) do (
    
    set arg=!argVec[%%I]!

    if !Arg! EQU clean goto :clean

    if !Arg! EQU release (
        set CompilerOpts=-Od -DDEBUG=0
        set LinkerOpts=/OPT:REF
        set Config=Release
    )
    if !Arg! EQU x86 (
        rem Override platform set by MSVC if specified via command-line args
        set Platform=x86
    )

)

rem End of entry point procedure
goto :Main


::-----------------------------------------------------------------------------
:: Main
::-----------------------------------------------------------------------------
rem Main procedure that configurues the script environment and LSP compile flags
:Main

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

rem Define `compile_flags.txt` file for the LLVM Clang LSP
set CompileFlags=compile_flags.txt

rem Clear `compile_flags.txt` file
echo | set /p Clear="" > %CompileFlags%

rem Create required directories for library and test suite compilation
if not exist obj\win32\%Config%_%Platform% mkdir obj\win32\%Config%_%Platform%
if not exist lib\win32\%Config%_%Platform% mkdir lib\win32\%Config%_%Platform%
if not exist bin\win32\%Config%_%Platform% mkdir bin\win32\%Config%_%Platform%
if not exist tests\obj\win32\%config%_%Platform% mkdir tests\obj\win32\%Config%_%Platform%
if %ErrorLevel% neq 0 goto :error

call :Build
if %ErrorLevel% neq 0 goto :EOF
call :Test
if %ErrorLevel% neq 0 goto :EOF

rem End of :Main subroutine call
goto :EOF


::-----------------------------------------------------------------------------
:: Build
::-----------------------------------------------------------------------------
rem Orchestrates the entire build process
:Build

rem Define the engine dynamic link library and application executable filenames
set _lib=libcspd_%Platform%.lib &:: Prefix with `_` to avoid clash with LIB
set _dll=libcspd_%Platform%.dll &:: Stay consistent with scheme above
set _exe=libcspd_%Platform%.exe &:: Stay consistent with scheme(s) above

rem Set the core library `include` and `src` directories
set IncDir=%Root%\include
set SrcDir=%Root%\src

rem Set the core library `obj` and `bin` directories
set ObjDir=%Root%\obj\win32\%Config%_%Platform%
set LibDir=%Root%\lib\win32\%Config%_%Platform%
set BinDir=%Root%\bin\win32\%Config%_%Platform%

rem Clear variables to store source, include, and object filenames.
set Srcs=
set Incs=
set Objs=

rem Reference Platform and Win32 header files
call :IncludeDirs %IncDir%
if %ErrorLevel% neq 0 goto :Error

rem Reference Platform and Win32 source files
call :SourceFiles %SrcDir%
if %ErrorLevel% neq 0 goto :Error

rem Perform compile and linking
call :Compile

rem End of :Build subroutine call
goto :EOF


::-----------------------------------------------------------------------------
:: Compile
::-----------------------------------------------------------------------------
rem Performs a compilation of source files and subsequent linking of the resulting object files
:Compile

rem Compile core library `*.c` files
cl /c /MD -Zi -W4 -Wall /std:c17 /Fo%ObjDir%\ /Fd"%ObjDir%\vc140.pdb" %Incs% %Srcs%
if %ErrorLevel% neq 0 goto :error
echo Library source files compiled successfully & echo.

call :ObjectFiles %ObjDir%
if %ErrorLevel% neq 0 goto :Error

rem Link *.obj object files
LINK /nologo /DEBUG %Objs:~1% /DLL /OUT:%LibDir%\%_dll%
if %ErrorLevel% neq 0 goto :Error

call :RelativePath %LibDir%
echo Library file `%_lib%` created in `%RelPath%` successfully. & echo.

rem Copy DLL to where the test executable will be built
copy %LibDir%\%_dll% %BinDir% > nul

goto :EOF

rem End of :Compile subroutine
goto :EOF


::-----------------------------------------------------------------------------
:: Test
::-----------------------------------------------------------------------------
rem Compile test program and link library DLL
:Test

rem Set the core library `include` and `src` directories
set IncDir=%root%\tests\include
set SrcDir=%root%\tests\src

rem Clear `srcs` and `objs` variables to store new source and object filenames
set Srcs=
set Objs=

rem Reset the `obj` directory for the test project intermediary files
set ObjDir=%Root%\tests\obj\win32\%Config%_%Platform%

rem Reference Platform and Win32 header files
call :IncludeDirs %IncDir%
if %ErrorLevel% neq 0 goto :Error

rem Reference Platform and Win32 source files
call :SourceFiles %SrcDir%
if %ErrorLevel% neq 0 goto :Error

rem Compile *.test.c files
cl /nologo /c /MD -Zi -W4 -Wall /std:c17 /Fo%ObjDir%\ /Fd"%ObjDir%\vc140.pdb" %Incs% %Srcs:~1%
if %ErrorLevel% neq 0 goto :error
echo Test source files compiled successfully & echo.

call :ObjectFiles %ObjDir%
if %ErrorLevel% neq 0 goto :Error

rem Link *.test.obj object files
LINK /DEBUG %Objs:~1% /OUT:%BinDir%\%_exe% %LibDir%\%_lib%
if %ErrorLevel% neq 0 goto :error
echo Test source files compiled successfully & echo.

echo Build succeeded.
goto :EOF


::===========================================================================
:: Helper Routines
::===========================================================================


::---------------------------------------------------------------------------
:: Clean
::---------------------------------------------------------------------------
rem Deletes all intermediary and binary files generated by the previous build(s)
:Clean

del /S /Q bin\*.dll bin\*.exe bin\*.lib bin\*.pdb bin\*.ilk bin\*.exp > nul 2>&1
del /S /Q obj\*.obj obj\*.pdb > nul 2>&1
del /S /Q tests\obj\*.obj tests\obj\*.pdb > nul 2>&1 
del /S /Q tests\bin\*.dll tests\bin\*.exe tests\bin\*.lib tests\bin\*.pdb^
    tests\bin\*.ilk tests\bin\*.exp > nul 2>&1

rem End of :Clean subroutine call
goto :EOF


::-----------------------------------------------------------------------------
:: Relative Path
::-----------------------------------------------------------------------------
rem Gets the relative path from the given absolute path
:RelativePath

set "AbsPath=%1%"
set "RelPath=!AbsPath:%Root%=!"

rem End of :RelativePath subroutine call
goto :EOF


::-----------------------------------------------------------------------------
:: Add Compile Flags
::-----------------------------------------------------------------------------
rem Adds a compile flag to `compile_flags.txt` for the Clang LSP
:AddCompileFlag

set Flag=%1

rem Invert slashes for include paths to be compatible with the LSP
set FilePath=!Flag:\=/!

rem Write flag to `compile_flags.txt` file
echo -I>> %Root%\%CompileFlags%
echo .!FilePath!>> %Root%\%CompileFlags%

rem End of :AddCompileFlag subroutine call
goto :EOF


::-----------------------------------------------------------------------------
:: Include Files
::-----------------------------------------------------------------------------
rem Reference the absolute and relative paths of each `*.h` header file
:IncludeDirs

for /r %1 %%A in (*.h) do (

    call :RelativePath %%~dpA

    rem Prevent duplicate include directories
    if !Prev! neq !RelPath! (

        call set "Incs=%%Incs%% -I%Root%!RelPath:~0,-1!"
        call :AddCompileFlag !RelPath!

        set "Prev=!RelPath!"
    )
)

rem End of :IncludeDirs subroutine call
goto :EOF


::-----------------------------------------------------------------------------
:: Source Files
::-----------------------------------------------------------------------------
rem Reference source files to be compiled
:SourceFiles

for /r %1 %%I in (*.c) do (
    call set "Srcs=%%Srcs%% %%~fI"
)

rem End of :SourceFiles subroutine call
goto :EOF


::-----------------------------------------------------------------------------
:: Object Files
::-----------------------------------------------------------------------------
rem Reference intermediary object files
:ObjectFiles

for /r %1 %%I in (*.obj) do (
    call set "Objs=%%Objs%% %1\%%~nxI"
)

rem End of :ObjectFiles subroutine call
goto :EOF


::-----------------------------------------------------------------------------
:: Error
::-----------------------------------------------------------------------------
rem Error function to call when a build error is encountered
:Error

set Err=%ErrorLevel%
echo. 
echo Build failed.
echo Exited with error code: %ErrorLevel%

exit /b %ErrorLevel%
