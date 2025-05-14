@echo OFF
set "DIR=%~dp0"
cd /d "%DIR%"

if not exist out mkdir out
g++ -static main.cpp modules/colors.cpp -o out/cbuild.exe

net session >nul 2>&1
if %errorLevel% neq 0 (
  echo Permiss pending...
  powershell Start-Process "%~f0" -Verb runAs
  exit /b
)

copy /Y "%DIR%out\cbuild.exe" "C:\Windows\System32"
start