@echo OFF
set "DIR=%~dp0"
cd /d "%DIR%"
g++ -static main.cpp modules/colors.cpp -o out/buildcpp.exe
net session >nul 2>&1
if %errorLevel% neq 0 (
  echo Permiss pending...
  powershell Start-Process "%~f0" -Verb runAs
  exit
)
copy %DIR%out/buildcpp.exe C:\Windows\System32
start 