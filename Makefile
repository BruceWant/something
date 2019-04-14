objects = check.o check_crypto.o

check : $(objects)
	gcc -o check $(objects)
check.o : check.c check_crypto.h
	gcc -c check.c
check_crypto.o : check_crypto.c check_crypto.h
	gcc -c check_crypto.c
clean :
	rm check $(objects)
