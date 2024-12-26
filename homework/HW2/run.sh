#!/bin/bash

# 檢查是否提供了C檔案名稱
if [ "$#" -lt 1 ]; then
    echo "Usage: ./run.sh <source_file.c> [testcase1.txt testcase2.txt ...]"
    exit 1
fi

# 取得C檔案名稱
SOURCE_FILE=$1
EXECUTABLE="a"
shift

# 檢查檔案是否存在
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: File '$SOURCE_FILE' does not exist."
    exit 1
fi

# 編譯C檔案
echo "Compiling $SOURCE_FILE..."
gcc -o "$EXECUTABLE" "$SOURCE_FILE" 2> compile_errors.log

# 檢查是否成功編譯
if [ $? -ne 0 ]; then
    echo "Compilation failed. See errors below:"
    cat compile_errors.log
    exit 1
fi

echo "Compilation successful."

# 執行每個測試案例
for TESTCASE in "$@"; do
    if [ ! -f "$TESTCASE" ]; then
        echo "Error: Test case file '$TESTCASE' does not exist."
        continue
    fi

    echo "Running $EXECUTABLE with test case $TESTCASE..."
    ./"$EXECUTABLE" < "$TESTCASE" 2> runtime_errors.log

    # 檢查執行是否成功
    if [ $? -ne 0 ]; then
        echo "Runtime error occurred with test case $TESTCASE. See errors below:"
        cat runtime_errors.log
    else
        echo "Test case $TESTCASE completed successfully."
    fi
    echo
done
