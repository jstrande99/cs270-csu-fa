# generic Makefile for LC3 asm code

# # rule to assemble .asm file to .obj file
# %.obj: %.asm
	~cs270/lc3tools/lc3as $<

default: $(patsubst %.asm, %.obj, $(wildcard *.asm))
                 
clean:
	rm -f *.obj *.sym

