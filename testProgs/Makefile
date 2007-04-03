

test.s: test.c
	cc65 test.c

test.o: test2.s
	ca65 -o test.o test2.s

test.nes: test.o
	ld65 --config nes.config -o test.nes test.o

sort.o: sort.s
	ca65 -o sort.o sort.s

sort.nes: sort.o
	ld65 --config nes.config -o sort.nes sort.o

fact-iter.o: fact-iter.s
	ca65 -o fact-iter.o fact-iter.s

fact-iter.nes: fact-iter.o
	ld65 --config nes.config -o fact-iter.nes fact-iter.o

clean:
	rm -f *.o *.nes