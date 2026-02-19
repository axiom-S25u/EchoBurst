@echo off
echo [Axiom] starting full cycle...
geode build
if %errorlevel% neq 0 pause
geode package install .
pause