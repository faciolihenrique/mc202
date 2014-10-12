#!/bin/bash

alias gcc='gcc -ansi -pedantic -Wall -Werror -lm -std=c99'

tst() {
    baseDir=${PWD##*/}
    for file in tests/arq*.in; do
        baseFile=$(basename $file ".in")
        inFile="$baseFile.in"
        outFile="$baseFile.out"
        resFile="$baseFile.res"
        testId=$(echo $baseFile | grep -Po '(?<=arq).*');

        echo "Test $testId";

        "./$baseDir" < "testes/$inFile" > "testes/$outFile"
        diff "testes/$outFile" "testes/$resFile"
    done
}

cmp() {
    gcc *.c -o "${PWD##*/}"
}