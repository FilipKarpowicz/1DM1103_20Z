DEPS = main.o studenci.o dziekanat.o

zad5:$(DEPS)
	gcc $(DEPS) -Wall --pedantic -o $@

%.o:%.c
	cc -c $^ -o $@

clean:
	rm -f zad5
	rm -f *.o

test: zad5
	./zad5 std.txt najlepsza ocena
	./zad5 std.txt najgorsza ocena
	./zad5 std.txt najlepszy student
