#! /bin/bash

touch in.tmp
touch out.tmp
touch err.tmp

echo Contents >in.tmp

case1="./simpsh --rdonly in.tmp --wronly out.tmp --wronly err.tmp --command 0 1 2 cat"
$case1

out1=$(cat out.tmp)

if [[ $out1 == "Contents" ]]
then
    echo "SUCCEEDED: $case1"
else
    echo "FAILED: $case1"
fi


case2="./simpsh --rdonly in.tmp --wronly out.tmp --wronly err.tmp --command 0 1 2 head -n 1"
$case2

out2=$(cat out.tmp)

if [[ $out2 == "Contents" ]]
then
    echo "SUCCEEDED: $case2"
else
    echo "FAILED: $case2"
fi


case3="./simpsh --rdonly in.tmp --wronly out.tmp --wronly err.tmp --command 0 1 2 gib"
$case3

out3=$(cat err.tmp)

if [[ $out3 == "Error executing command gib" ]]
then
    echo "SUCCEEDED: $case3"
else
    echo "FAILED: $case3"
fi


case4="./simpsh --verbose --rdonly in.tmp"
touch case4.tmp
`$case4 >case4.tmp`

out4=$(cat case4.tmp)

if [[ $out4 == "--rdonly in.tmp" ]]
then
    echo "SUCCEEDED: $case4"
else
    echo "FAILED: $case4"
fi


case5="./simpsh --rdonly"
touch case5.tmp
`$case5 2>case5.tmp`

out5=$(cat case5.tmp)

if [[ $out5 == "Syntax error --rdonly" ]]
then
    echo "SUCCEEDED: $case5"
else
    echo "FAILED: $case5"
fi


case6="./simpsh --wronly in.tmp out.tmp"
touch case6.tmp
`$case6 2>case6.tmp`

out6=$(cat case6.tmp)

if [[ $out6 == "The number of arguments passed to --wronly was more than one, the first file was taken as input" ]]
then
    echo "SUCCEEDED: $case6"
else
    echo "FAILED: $case6"
fi


rm *.tmp
