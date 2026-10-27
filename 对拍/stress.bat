@echo off
g++ gen.cpp -std=c++20 -O2 -o gen.exe
g++ std.cpp -std=c++20 -O2 -o std.exe
g++ my.cpp -std=c++20 -O2 -o my.exe

set /a i=0
:loop
set /a i+=1
echo Testing %i%

echo Generating...
gen.exe > in.txt
if errorlevel 1 goto error

echo Running std...
std.exe < in.txt > std.txt
if errorlevel 1 goto error

echo Running my...
my.exe < in.txt > my.txt
if errorlevel 1 goto error

echo Comparing...
fc std.txt my.txt > nul
if not errorlevel 1 goto loop

echo ===== Input =====
type in.txt
echo ===== Std =====
type std.txt
echo ===== My =====
type my.txt
pause
exit /b

:error
echo Program failed!
pause