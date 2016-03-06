#!/bin/bash
name=fundabot
"/home/$(whoami)/.wine/drive_c/Program Files (x86)/PICC/Ccsc.exe" \
+STDOUT +EA +FH +P3 +DF +Y9 +DC +STDOUT +J -T -Z +LNlst +O8hex ./src/fundabot.c
mv ./src/fundabot.hex .
