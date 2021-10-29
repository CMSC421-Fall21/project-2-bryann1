#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define SIZE_OF_BUFFER 20
#define __NR_hello 441
#define __NR_init_buffer_421 442
#define __NR_insert_buffer_421 443
#define __NR_print_buffer_421 444
#define __NR_delete_buffer_421 445

long hello_syscall(void){
	return syscall(__NR_hello);
}

long init_buffer_syscall(void){
	return syscall(__NR_init_buffer_421);
}

long insert_buffer_syscall(int i){
	return syscall(__NR_insert_buffer_421, i);
}

long print_buffer_syscall(void){
	return syscall(__NR_print_buffer_421);
}

long delete_buffer_syscall(void){
	return syscall(__NR_delete_buffer_421);
}

int main(int argc, char *argv[]){
	int i;
	// initialize buffer
	if(init_buffer_syscall() < 0)
		perror("Initialize syscall failed.\n");
	else
		printf("Initialize buffer syscall ran successfully, check dmesg output\n");

	// printing buffer with length of 0
	if(print_buffer_syscall() < 0)
		perror("Print syscall failed.\n");
	else
		printf("Print syscall ran successfully, check dmesg output\n");

	// insert 20 items
	for(i = 0; i < SIZE_OF_BUFFER; i++){
		if(insert_buffer_syscall(i) < 0)
			perror("Insert syscall failed.\n");
		else
			printf("Insert syscall ran successfully, check dmesg output\n");
	}

	// edge case for inserting into full buffer
	if(insert_buffer_syscall(666) < 0)
		perror("Insert syscall failed.\n");
	else
		printf("Insert syscall ran successfully, check dmesg output\n");

	if(print_buffer_syscall() < 0)
		perror("Print syscall failed.\n");
	else
		printf("Print syscall ran successfully, check dmesg output\n");

	// free memory
	if(delete_buffer_syscall() < 0)
		perror("Delete syscall failed.\n");
	else
		printf("Delete syscall ran successfully, check dmesg output\n");
	
	// edge case for printing a nonexistent buffer
	if(print_buffer_syscall() < 0)
		perror("Print syscall failed.\n");
	else
		printf("Print syscall ran successfully, check dmesg output\n");

	return 0;
}

