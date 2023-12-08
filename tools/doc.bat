@echo off

REM Call to generate documentation

popd
pushd doc

del /S /Q html\*

call "C:\Program Files\doxygen\bin\doxygen.exe" Doxyfile

popd
