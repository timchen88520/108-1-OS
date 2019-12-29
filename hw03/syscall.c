#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv) {
    char* hello = "hello world\n";
    char* hello_tc = "全世界，你好\n";
    int len = strlen(hello)+1;
    long len_tc = strlen(hello_tc)+1; //注意我宣告為long，因為long是64位元
    long ret;
    
    printf("使用 'int 0x80' 呼叫system call\n");
    __asm__ volatile ( 
        "mov $4, %%rax\n"
        "mov $2, %%rbx\n"
        "mov %1, %%rcx\n"
        "mov %2, %%rdx\n"
        "int $0x80\n"
        "mov %%rax, %0"
        :  "=m"(ret)
        : "g" (hello), "g" (len)
        : "rax", "rbx", "rcx", "rdx");
    printf("回傳值是：%ld\n", ret);

    printf("使用 'syscall' 呼叫system call\n");
    char hwask;
		__asm__ volatile ( 
        "mov 0x0, %%rdi\n"
				//"lea rsi, [rsp+8]\n"
				"mov 0xa, %%rdx\n"
				"mov 0x0, %%rax\n"
				"syscall\n"
				//"mov $0, %%rcx\n"   //stdin char
				//try to add stdin above
				"mov $1, %%rax\n"   //system call number
        "mov $2, %%rdi\n"   //stderr
        "mov %1, %%rsi\n"   //
        "mov %2, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        :  "=m"(ret)
        : "g" (hello_tc), "g" (len_tc),"g" (hwask)
        : "rax", "rbx", "rcx", "rdx");
    printf("回傳值是：%ld\n", ret);
		printf("stdin char is: %c\n",hwask);
}
