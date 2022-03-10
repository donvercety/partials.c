PROGN = speller
FLAGS = -Wall \
	-Werror \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-parameter \
	-Wno-unused-variable \
	-Wshadow

.SILENT: build clear

build: clear
	gcc -ggdb3 -O0 -std=c11 ${FLAGS} -c -o speller.o speller.c
	gcc -ggdb3 -O0 -std=c11 ${FLAGS} -c -o dictionary.o dictionary.c
	gcc -ggdb3 -O0 -std=c11 ${FLAGS} -o ${PROGN} speller.o dictionary.o -lm

clear:
	rm -f ${PROGN} speller.o dictionary.o

zip:
	zip -r ${PROGN}.zip .

run:
	$(info --- RUN --- ${PROGN})
	./${PROGN} dictionaries/small texts/cat.txt
