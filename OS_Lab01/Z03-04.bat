@echo off
echo -- all params: %1 %2 %3 %4 %5 %6 %7 %8 %9
echo -- param 1: %1
echo -- param 2: %2
echo -- param 3: %3

set /A a=%1
set /A b=%2
set /A c=%3

set /A sum=a+b
set /A mul=a*b
set /A div=c/b
set /A min=b-a
set /A min2=a-b
set /A expr=min*min2

echo -- %1 + %2 = %sum%
echo -- %1 * %2 = %mul%
echo -- %3 / %2 = %div%
echo -- %2 - %1 = %min%
echo -- (%2 - %1) * (%1 - %2) = %expr%