@echo off
tasm\tasm %1.asm
if errorlevel 1 goto end
tasm\tlink /t %1
if errorlevel 1 goto end
del %1.obj
%1.com
:end