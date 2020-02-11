@echo off

set PROJECT_NAME=bleu
for /F "tokens=*" %%A in ('"git describe HEAD --abbrev=0"') do set PROJECT_VER=%%A

cd %~dp0

set COMPILER=ccrx
set OUTPUT_DIR=bin\%COMPILER%@%PROJECT_VER%
mkdir %OUTPUT_DIR% > NUL 2>&1
%COMPILER% -output=obj=%OUTPUT_DIR%/%PROJECT_NAME%.obj -lang=c99 -nostuff -isa=rxv3 ^
           -include=v1/ ^
           src/heap/%COMPILER%/heap.c ^
           src/heap/heap_usage.c ^
           src/io_data/io_data.c ^
           src/list/list_node.c ^
           src/list/list.c ^
           src/queue/queue.c ^
           src/rng/xorshift/xorshift.c ^
           src/rng/xorshift/xorshift32.c ^
           src/rng/xorshift/xorshift64.c ^
           src/rng/xorshift/xorshift96.c ^
           src/rng/xorshift/xorshift128.c ^
           src/rng/xorshift_plus/null_xorshift_plus.c ^
           src/rng/xorshift_plus/xorshift_plus.c ^
           src/rng/xorshift_plus/xorshift128plus.c
if %errorlevel% neq 0 exit /b
rlink -form=lib -output=%OUTPUT_DIR%/%PROJECT_NAME%.lib ^
      %OUTPUT_DIR%/%PROJECT_NAME%.obj
