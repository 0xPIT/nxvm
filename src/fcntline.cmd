@echo off
if /i "%*"=="/nekolist" (echo FCNTLINE	�ļ�������ͳ��
goto EOF)
setlocal enabledelayedexpansion
set nmLineCount=0
for /f %%i in ('dir /a:-d /b /s %*') do (
	for /f "delims=" %%j in ('findstr /n .* %%i') do set /a nmLineCount+=1
)
echo !nmLineCount!
endlocal