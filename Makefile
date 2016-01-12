DISTNAME = lab1-AdityaLake

all: simpsh

simpsh: main.o libutils.a libcommand.a libopenfile.a
	gcc -o simpsh main.o libutils.a libcommand.a libopenfile.a

main.o: main.c
	gcc -c main.c

libutils.a: utils.o
	ar rs libutils.a utils.o

utils.o: utils.c
	gcc -c utils.c

libcommand.a: command.o
	ar rs libcommand.a command.o

command.o: command.c
	gcc -c command.c

libopenfile.a: openFile.o
	ar rs libopenfile.a openFile.o

openFile.o: openFile.c
	gcc -c openFile.c

SOURCES = openFile.c openFile.h command.c command.h utils.c utils.h main.c Makefile README test.sh

dist: $(DISTNAME).tar.gz

$(DISTNAME).tar.gz: $(SOURCES)
	rm -fr $(DISTNAME)
	tar -czf $@.tmp --transform='s,^,$(DISTNAME)/,' $(SOURCES)
	mv $@.tmp $@

check: simpsh
	./test.sh
clean:
	rm -fr *.o *~ *.a *.tar.gz simpsh
