@echo off

REM Путь к тестируемому файлу передается через 1-й аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM If count of arguments is less than 4, program must fail
%MyProgram% 16 10 && goto err
echo Test 1 passed

REM If the number of arguments is greater than 4, program must fail
%MyProgram% 16 10 1F SomeArgument && goto err
echo Test 2 passed

REM If the second argument contains non-numeric characters, program must fail
%MyProgram% 16r 10 1F && goto err
echo Test 3 passed

REM If the third argument contains non-numeric characters, program must fail
%MyProgram% 16 1t0 1F && goto err
echo Test 4 passed

REM If the second argument is a number less than 2, program must fail
%MyProgram% 1 10 1 && goto err
echo Test 5 passed

REM If the third argument is a number less than 2, program must fail
%MyProgram% 2 1 1 && goto err
echo Test 6 passed

REM If the second argument is a number greater than 36, program must fail
%MyProgram% 37 10 1F && goto err
echo Test 7 passed

REM If the third argument is a number greater than 36, program must fail
%MyProgram% 2 37 1 && goto err
echo Test 8 passed

REM If the <value> argument contains characters that do not belong to source notation, program must fail
%MyProgram% 16 10 1f && goto err
echo Test 9 passed

REM Converting a number from hexadecimal to decimal
%MyProgram% 16 10 1F > "%TEMP%\output.txt" || goto err
fc Test10.txt "%TEMP%\output.txt" > nul || goto err
echo Test 10 passed

REM Converting a number from binary to thirty-six
%MyProgram% 2 36 1010001001 > "%TEMP%\output.txt" || goto err
fc Test11.txt "%TEMP%\output.txt" > nul || goto err
echo Test 11 passed

REM Converting a number from decimal to thirty-three
%MyProgram% 10 33 2375930 > "%TEMP%\output.txt" || goto err
fc Test12.txt "%TEMP%\output.txt" > nul || goto err
echo Test 12 passed

REM Converting the INT_MAX from binary to thirty-three 
%MyProgram% 2 33 1111111111111111111111111111111 > "%TEMP%\output.txt" || goto err
fc Test13.txt "%TEMP%\output.txt" > nul || goto err
echo Test 13 passed

REM Overflow (INT_MAX + 1), program must fail
%MyProgram% 5 30 13344223434043 && goto err
echo Test 14 passed

REM Converting a negative number from hexadecimal to decimal
%MyProgram% 16 10 -1F > "%TEMP%\output.txt" || goto err
fc Test15.txt "%TEMP%\output.txt" > nul || goto err
echo Test 15 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1