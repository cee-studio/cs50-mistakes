#!/bin/bash
mypath=$(dirname $(readlink -f $0))

for i in *; do
    if [ -d $i ]; then
        echo "building .."
        cd $mypath/$i
        clang *.c -g -lcs50 -o b
        clang *.c -fsanitize=address -g -lcs50 -o b.asan
        cd $mypath
    fi
done
