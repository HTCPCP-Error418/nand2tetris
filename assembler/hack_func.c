/*
 * This file contains the definitions for the functions prototyped in
 * "hack_assem.h" and is utilized for the HACK assembler program.
 */

 #include "hack_assem.h"

/*
 * This function prints a basic usage message and exits. This function will be
 * called if the program is executed with the '-h' or '--help' options, as
 * well as no options
 */
void usage(char *progname) {
	printf("" CYAN "Usage: %s [options]" RESET "\n", progname);
	printf("" CYAN "Options:" RESET "\n");
	printf("" CYAN "\t-i, --infile\t[filename]\t: File to translate to machine code" RESET "\n");
	printf("" CYAN "\t-o, --outfile\t[filename]\t: File to save machine code to" RESET ""\n");
	printf("" CYAN "\t-h, --help\t\t\t: Print this help dialoge and exit" RESET "\n");
}


/*
 * This function takes two arguments: the filename to write the output to and
 * the decimal value of the instruction to translate into machine code. This
 * function will convert the instruction's decimal value into its binary
 * representation and append the binary to the specified outfile.
 *
 * When converting the decimal to binary, the loop is iterated down to reverse
 * the order in which the values are saved. If the loop is iterated up, the
 * binary representation will be in the reverse order.
 *
 * Returns 0 on success, 2 on error opening outfile
 */
int to_bin(char *outfile_name, unsigned short decimal) {
	int bin_arr[16] = {0};			//array to store binary representation of decimal

	//convert decimal to binary
	for (int i = 16; i >= 0; i--) {
		if (decimal < 1) {
			bin_arr[i] = 0;
		} else {
			bin_arr[i] = decimal % 2;
			decimal /= 2;
		}
	}

	//open outfile
	FILE *outptr = fopen(outfile_name, "a");
	if (outptr == NULL) {
		fprintf(stderr, "Could not open output file: %s\n", outfile_name);
		return 2;
	}

	//write binary command to file
	for (int i = 0; i < 16; i++) {
		fprintf(outptr, "%d", bin_arr[i]);
	}
	fprintf(outptr, "\n");			//start a new line for next command
	fclose(outptr);

	//return 0 on success
	return 0;
}
