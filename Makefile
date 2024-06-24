all: speller

helper.o: helper.c helper.h
	gcc -g -c helper.c -o helper.o

main.o: helper.h main.c
	gcc -c -g main.c -o main.o

spellcheck.o: spellcheck.c spellcheck.h
	gcc -g -c spellcheck.c -o spellcheck.o

speller: helper.o main.o spellcheck.o
	gcc -g helper.o main.o spellcheck.o -o speller

clean: 
	rm -rf helper.o main.o spellcheck.o speller