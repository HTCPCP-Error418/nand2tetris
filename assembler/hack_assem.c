/*
 * This file contains the main code for the HACK assembler project and serves
 * as a record of my first attempt at following a syle guide for coding. This
 * file is currently being used for testing functions from "hack_func.c" and
 * for developing the overall logic of the program.
 */

#include "hack_assem.h"	//custom header file for assembler

int main(int argc, char *argv[]) {
	//check for command-line arguments
	if (argc != 1) {
		printf("Incorrect number of arguments provided\n");
		usage;
	}

	//get decimal from user
	unsigned int num;
	printf("Plesae enter a positive integer: ");
	scanf("%u", &num);
	printf("The number provided was: %u\n", num);

	//convert number to binary and print
	int bin_arr[15] = {0};
	get_bin(num, bin_arr);
	printf("The binary representation is:\n");
	for (int i = 0; i < 14; i++) {
		printf("%i ", bin_arr[i]);
	}
	printf("\n");

	exit(0);
}
