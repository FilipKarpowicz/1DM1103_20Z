DEPS = main.o pamiec.o uzytkownik.o mnozenia.o norma.o sumy.o

main:$(DEPS)
	gcc $(DEPS) -Wall --pedantic -o $@ -lm

%.o:%.c
	cc -c $^ -o $@

clean:
	rm -f main
	rm -f *.o

test: main
	./main sum m3.txt m4.txt
	./main subtract m3.txt m4.txt
	./main multiply m3.txt 3
	./main norm m3.txt
	./main prod m1.txt m2.txt
	./main sum m3.txt m4.txt wynik1.txt
	./main norm m3.txt wynik2.txt