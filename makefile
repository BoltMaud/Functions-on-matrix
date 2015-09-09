main: main.o minicas.o matrice.o gaussetcie.o
	gcc -o $@ $^

main.o: main.c minicas.h
	gcc -g -o $@ -c $<
	
minicas.o: minicas.c minicas.h matrice.h gaussetcie.h
	gcc -g -o $@ -c $<

matrice.o: matrice.c matrice.h
	gcc -g -o $@ -c $<
	
gaussetcie.o: gaussetcie.c gaussetcie.h matrice.h
	gcc -g -o $@ -c $<

clean:
	rm -fr main *.o *.gz

archive:
	tar -cvf Projet.tar.gz *.c *.h makefile
