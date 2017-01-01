#include <iostream>

void print_int(int n)
{
    std::cout << n << std::endl;
}

int assembly_pow(int base, int exponent)
{
    _asm {
        mov eax, 1;
        mov ecx, exponent;
    start:
        imul eax, base;
        loop start;
    }
}

int main()
{
    _asm {
        push 10;
        push 2;
        push eax;
        call assembly_pow;
        call print_int;
    never_ending:
        jmp never_ending;
    }
}