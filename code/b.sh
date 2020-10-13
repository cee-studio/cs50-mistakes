#!/bin/bash
mypath=$(dirname $(readlink -f $0))

for i in *; do
    if [ -d $i ]; then
        echo "building $i .."
        cd $mypath/$i
        clang *.c -g -lcs50 -o b.exe
        clang *.c -fsanitize=address -g -lcs50 -o b.asan.exe
        cd $mypath
    fi
done
