#!/bin/bash
#export PATH
#name=$(echo ./src/*.hex)
#IN=$name
#arrIN=(${IN//;/ })
#pk2cmd -ppic18f2550 -f$arrIN -m
if [[ $1 = "4550" ]]; then
   echo "programming 4550"
   PATH=$PATH:/usr/share/pk2/ pk2cmd -ppic18f4550 -ffundabot.hex -m
elif [[ $1 = "2550" ]]; then
   echo "programming 2550"
   PATH=$PATH:/usr/share/pk2/ pk2cmd -ppic18f2550 -ffundabot.hex -m
fi

