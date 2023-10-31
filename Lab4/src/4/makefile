main.out: main.o c_func.o cpp_func.o asm_func.o
	g++ -o main.out main.o c_func.o cpp_func.o asm_func.o -m32

c_func.o: c_func.c
	gcc -o c_func.o -c c_func.c -m32

cpp_func.o: cpp_func.cpp
	g++ -o cpp_func.o -c cpp_func.cpp -m32

asm_func.o: asm_func.asm
	nasm -o asm_func.o -f elf32 asm_func.asm

main.o: main.cpp
	g++ -o main.o -c main.cpp -m32

clean:
	rm -rf *.o *.out

run:
	./main.out