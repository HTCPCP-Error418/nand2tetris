/*
 * This file contains the common libraries, structures, and functions for
 * the HACK assembler
 */

 #ifndef HACKASSEM_H
 #define HACKASSEM_H	//begin HACKASSEM_H


 //common libraries
 #include <stdio.h>


/*
 * The first three bits of a 16-bit C-instruction are constant (all set to 1).
 * The decimal value for the first three bits is 57344 and is defined here for
 * readability purposes and to avoid creating unneeded global variables.
 */
#define CHEADER 57344


/*
 * The definitions below are the escape codes for coloring text output in C.
 * These are added for some extra fun and may or may not be used.
 *
 * USAGE: printf(RED "This text is red." RESET "\n");
 *
 * NOTE: Adding a set of empty quotes before the color will allow Atom to
 * still use the syntax highlighting for printf()
 * EXAMPLE: printf("" RED "This text is red." RESET "\n");
 */
#define RED		"\x1b[31m"
#define GREEN	"\x1b[32m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define MAGENTA	"\x1b[35m"
#define CYAN	"\x1b[36m"
#define RESET	"\x1b[0m"


/*
 * This function prints a basic usage message and exits. This function will be
 * called if the program is executed with the '-h' or '--help' options, as
 * well as no options
 */
void usage(char *progname);


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
int to_bin(char *outfile_name, unsigned short decimal);

#endif	//end HACKASSEM_H
