#!/usr/bin/env bash
#
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

echo "Test,LOLnope,GCC,result"
EXIT_CODE=0
for testname in $(find compilation -type f -name \*.c -exec basename {} .c \; | sort); do
    mkdir -p compilation_results/$testname

    # Run our version
    if [ -f compilation_results/$testname.mips.bin ]; then
        { timeout 1 qemu-mips compilation_results/$testname.mips.bin; } \
            > compilation_results/$testname.stdout \
            2> compilation_results/$testname.stderr
        ours_returned=$?
    else
        ours_returned="-"
    fi

    # Run the gcc version
    if [ -f compilation_results/gcc/$testname.mips.bin ]; then
        timeout 1 qemu-mips compilation_results/gcc/$testname.mips.bin \
            > compilation_results/gcc/$testname.stdout \
            2> compilation_results/gcc/$testname.stderr
        gcc_returned=$?
    else
        gcc_returned="-"
    fi

    if [ $gcc_returned == 124 ]; then
        echo -e "$RED$testname,$ours_returned,$gcc_returned,GCC timed out$NC"
        EXIT_CODE=1
    elif [ $gcc_returned == "-" ]; then
        echo -e "$RED$testname,$ours_returned,$gcc_returned,GCC didn't run$NC"
        EXIT_CODE=1
    elif [ $ours_returned == "-" ]; then
        echo -e "$RED$testname,$ours_returned,$gcc_returned,Did not compile$NC"
        EXIT_CODE=1
    elif [ $ours_returned == 124 ]; then
        echo -e "$RED$testname,$ours_returned,$gcc_returned,LOLnope timed out$NC"
        EXIT_CODE=1
    elif [ $ours_returned == $gcc_returned ]; then
        echo -e "$GREEN$testname,$ours_returned,$gcc_returned,Passed$NC"
    else
        echo -e "$RED$testname,$ours_returned,$gcc_returned,failed$NC"
        EXIT_CODE=1
    fi
done

exit $EXIT_CODE
