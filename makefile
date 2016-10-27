random:random.c
	gcc random.c -o random.out
clean:
	rm random.out
	rm randomList
	rm *~
run: random
	./random.out
