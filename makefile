random:random.c
	gcc random.c -o random
clean:
	rm random
	rm *~
run:
	./random
