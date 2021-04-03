#!/bin/bash

# Terminal colors
RED='\033[0;31m';
GREEN='\033[0;32m';
NC='\033[0m'; # No color

# Parse command-line options
OPTS=`getopt -o --long no-color`
while true; do
    case "$1" in
        --no-color ) RED=''; GREEN=''; NC=''; shift;;
        * ) break ;;
    esac
done

EXIT_CODE=0
for testname in $(find test/python_translation -type f -name \*.c -exec basename {} .c \;); do
    mkdir -p test/python_translation-results/$testname

    # Translate
    bin/c_compiler -t test/python_translation/$testname.c\
        -o test/python_translation-results/$testname/$testname.py\
        > test/python_translation-results/$testname/compiler_stdout\
        2> test/python_translation-results/$testname/compiler_stderr
    compiler_returned=$?

    if ! [ $compiler_returned -eq 0 ]; then
        echo -e "$RED$testname, failed$NC, compiler returned $python_returned"
        continue
    fi

    # Run
    python test/python_translation-results/$testname/$testname.py\
        > test/python_translation-results/$testname/stdout\
        2> test/python_translation-results/$testname/stderr
    python_returned=$?

    if [ $python_returned -eq 0 ]; then
        echo -e "$GREEN$testname, passed$NC"
    else
        echo -e "$RED$testname, failed$NC, returned $python_returned"
        EXIT_CODE=1
    fi
done

exit $EXIT_CODE
