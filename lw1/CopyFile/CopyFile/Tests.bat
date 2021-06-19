@echo off

REM Путь к тестируемому файлу передается через 1-й аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Copy non-empty file
%MyProgram% NonEmpty.txt "%TEMP%\output.txt" || goto err
fc NonEmpty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM Copy missing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto err
echo Test 3 passed

REM If output file is not specified, program must fail
%MyProgram% MissingFile.txt && goto err
echo Test 4 passed

REM If input and output files are not specified, program must fail
%MyProgram% && goto err
echo Test 5 passed

REM If the number of arguments is greater than 4, program must fail
%MyProgram% NonEmpty.txt "%TEMP%\output.txt" SomeArgument && goto err
echo Test 6 passed

REM If no access to the output file, program must fail
%MyProgram% NonEmpty.txt "d:\output.txt" && goto err
echo Test 7 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1