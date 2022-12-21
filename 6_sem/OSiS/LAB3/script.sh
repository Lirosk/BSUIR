#! /usr/bin/bash

printf  "This is input file:\n"
cat $1
printf  "\nThis is output file:\n"
sed 's/\<\([[:lower:]]\)\([^[:punct:]]*\)/\u\1\2/g' $1 | tee $2
# s/ - replacing
# /g - (global replacement) replace all the occurrences of the string in the line
