export SHELL := /bin/bash
name=RTOS_HID_TERMINAL
default:
	bash makefile.sh $(name)
clean:
	rm -f ./src/*.{sta,sym,tre,lst,cof,err,esym,bak,cod} *.hex
write2550:
	bash programpic.sh 2550
write4550:
	bash programpic.sh 4550

