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
	char hwask[10]={0};
	//char *hwask;
	__asm__ volatile ( 
			"mov $0, %%rax\n"   //system call number ->0(sys_read)
			"mov $0, %%rdi\n"   //move to 0 as stdin
			"mov %0, %%rsi\n"   //buffer start form 0
			"mov $1, %%rdx\n"		//count size as 1
			"syscall\n"
			//"mov %%rax, %0\n"
			//"mov %%eax, %0"
			//:  "=m"(ret), "=m"(hwask)
			:
			:"g" (hwask)
			//: "g" (hello_tc), "g" (len_tc)
			: "rax", "rdi", "rsi", "rdx");
	//printf("回傳值是：%ld\n", ret);
	printf("stdin is: %s\n",hwask);
}
