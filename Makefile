DEBUG = -g

6502.o: opcodes.h NEStypes.h 6502_mem.h opcode_map.h 6502.h 6502_mem.c 6502.c
	gcc ${DEBUG} -c 6502.c

6502_mem.o: 6502_mem.h 6502_mem.c
	gcc ${DEBUG} -c 6502_mem.c

ines.o: 6502_mem.h ines.h ines.c
	gcc ${DEBUG} -c ines.c

nes_ppu.o: nes_ppu.c nes_ppu.h NEStypes.h
	gcc ${DEBUG} -c nes_ppu.c

6502_debugger.o: 6502_mem.o 6502.o 6502_debugger.c 6502_debugger.h NEStypes.h \
	opcodes.h 6502.h
	gcc ${DEBUG} -c 6502_debugger.c

nes_emu: 6502_mem.h ines.h 6502.h nes_emu.c 6502.o 6502_mem.o ines.o 6502_debugger.o \
	nes_ppu.o
	gcc ${DEBUG} -o nes_emu nes_emu.c 6502_mem.o 6502.o ines.o 6502_debugger.o nes_ppu.o -lreadline

clean:
	rm -f *.o *~ nes_emu

test.nes: 
	cd testProgs; make test.nes