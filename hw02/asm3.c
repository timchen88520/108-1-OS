#include <stdio.h>
int main(int argc, char** argv) {
	int a=10, b=20, c=90, d=100;
	printf("a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
	__asm__ volatile (
			"movl %1, %%eax\n" //  rax = a
			"movl %2, %%ebx\n" //  rbx = b
			//"mov $0, %%rcx\n" //  rcx = 0
			//"mov %%rax, %%rcx\n" // rcx += rax
			"add %%eax, %%ebx\n" // rcx += rbx
			//"mov %%rax, %%rcx\n" // c = rax
			"mov %%ebx, %0\n"
			: "=m" (c)//output
			: "g" (b), "g" (a) //input
			: "ebx", "eax" //搞爛掉的暫存器
			);
	printf("c = a + b\n");
	printf("a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
}
