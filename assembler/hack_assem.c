/*
 * This file contains the main code for the HACK assembler project and serves
 * as a record of my first attempt at following a syle guide for coding. This
 * file is currently being used for testing functions from "hack_func.c" and
 * for developing the overall logic of the program.
 */

#include "hack_assem.h"	//custom header file for assembler
#include <ctype.h>

bool load_sym(const char *sym_file);

int main(int argc, char *argv[]) {
	//check for command-line arguments
	if (argc != 1) {
		printf("Incorrect number of arguments provided\n");
		printf("\tUsage: ./assembler [symbol file]\n");
		exit(0);
	}
	char string[50];

	printf("Enter string: ");
	scanf("%s", string);
	printf("\n");

	printf("String is:\n\t%s\n\n", string);

	char *ptr;
	unsigned long num;
	num = strtoul(string, &ptr, 10);
	printf("Num is: %u\nString is: %s\n",num, ptr);

/*	printf("Loading Symbol File: %s\n", argv[1]);
	load_sym(argv[1]);
	printf("\n");

	printf("Printing Loaded Symbols:\n");
	print_symbol_table();
	printf("\n");

	printf("Freeing Allocated Memory:\n");
	free_mem();
	printf("\n");

	printf("Done.\n\n");
*/
	exit(0);
}

bool load_sym(const char *sym_file) {
	//open file with symbols as read only
	FILE *inptr = fopen(sym_file, "r");
	if (inptr == NULL) {
		fprintf(stderr, "[!] Error opening symbol file (%s)\n", sym_file);
		return false;
	}

	char name[50] = {0};			//50 character buffer for symbol name
	int len = 0;					//length of symbol name
	unsigned int value = 0;			//value of symbol
	bool symbol_name = true;		//first field (true) is name, second is value

	//get line 1 character at a time, remove \n and whitespace
	//symbols are formatted as [name value]
	for (int c = fgetc(inptr); c != EOF; c = fgetc(inptr)) {
		if (isspace(c)) {	//split the symbols according to space (isspace() detects all whitespace)
			symbol_name = false;
			name[len] = '\0';	//nul terminate name
			len++;				//account for nul
		} else if (symbol_name == true && (isalpha(c) || isdigit(c))) {	//name field
			//is letter or number
			name[len] = c;
			len++;
		} else if (symbol_name == false && isdigit(c)) {				//value field
			char val_tmp[6] = {0};	//temp array to hold whole value before using atoi() -- 5 digits available
			int index = 0;
			while ((c = fgetc(inptr)) != EOF && isdigit(c) && index <= 5) {
				if (index == 5) {
					//if 1 spot left in array, terminate
					val_tmp[5] = '\0';
					break;
				} else {
					//while there are numbers and array is not full
					val_tmp[index] = c;
					index++;
				}
			}
//			value = strtoul(val_tmp);
			printf("\t\tval_tmp = %s -- int = %u\n", val_tmp);
			index = 0;

		} else {
			//line is done, make node and start over
			printf("\tFound \" %s \" : %u\n", name, value);
			add_sym(name, len, value);
			symbol_name = true;
			len = 0;
		}
	}
	//close file
	fclose(inptr);
	printf("\tSymbols Loaded.\n");
	return true;
}
