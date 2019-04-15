/*
 * This file contains the main code for the HACK assembler project and serves
 * as a record of my first attempt at following a style guide while coding.
 */

#include "hack_assem.h"	//custom header file for assembler


int main(int argc, char *argv[]) {

	char *infile;	//file name for input file
	char *outfile;	//file name for output file
	char tmpfile[] = "hack_assem_output_tmp_file.tmp" //file name for temp file

	//parse command line options, start at argv[1], since program name is argv[0]
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i]) {
				case "-h"			:
				case "--help"		:
					usage(argv[0]);
					return 0;
					break;
				case "-i"			:
				case "--infile"		:
					infile = argv[i + 1];
					break;
				case "-o"			:
				case "--outfile"	:
					outfile = argv[i + 1];
					break;
				default				:
					usage(argv[0]);
					return 1;
			}
		} else if (argc != 1 || != 4) {
			usage(argv[0]);
			return 1;
		}
	}

	//open input file (read only), check that file opened successfully
	FILE *inptr = fopen(infile, "r");
	if (inptr == NULL) {
		fprintf(stderr, RED "[!]\tError opening input file:\t%c" RESET "\n", infile);
		return 2;
	}



	//close open files
	fclose(inptr);
}
