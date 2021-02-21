@echo off

REM Путь к тестируемому файлу передается через 1-й аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" hello buy || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Copy non-empty multi-line document with empty lines
%MyProgram% NonEmpty.txt "%TEMP%\output.txt" hello buy || goto err
fc NonEmptyOut.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM Checking for looping
%MyProgram% LoopingCheck.txt "%TEMP%\output.txt" ma mama || goto err
fc LoopingCheckOut.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

REM Checking the situation with the return in case of an unsuccessful search
%MyProgram% ReturnSearchCheck.txt "%TEMP%\output.txt" 1231234 888 || goto err
fc ReturnSearchCheckOut.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

REM Replace empty string
%MyProgram% NonEmpty.txt "%TEMP%\output.txt" "" "buy" || goto err
fc NonEmpty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 passed

REM Copy missing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" hello buy && goto err
echo Test 6 passed

REM If count of arguments is less than 5, program must fail
%MyProgram% MissingFile.txt hello buy && goto err
echo Test 7 passed

REM If the number of arguments is greater than 4, program must fail
%MyProgram% NonEmpty.txt "%TEMP%\output.txt" hello buy SomeArgument && goto err
echo Test 8 passed

REM If no access to the output file, program must fail
%MyProgram% NonEmpty.txt "d:\output.txt" hello buy && goto err
echo Test 9 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1