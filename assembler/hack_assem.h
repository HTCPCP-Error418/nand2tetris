/*
 * This file contains the common libraries, structures, and functions for
 * the HACK assembler
 */

 #ifndef HACKASSEM_H
 #define HACKASSEM_H	//begin HACKASSEM_H


 //common libraries
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>


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
 * Structure to be used for symbol table, destination, comparison, and jump
 * linked lists.
 *
 * Symbol Table
 * 	Pre-Defined Symbols:	val => assigned value
 * 	Labels:					val => line number
 * 	Variables:				val => counter value
 *
 * Destination-bits, Comparison-bits, Jump-bits linked lists:
 * 	*name => instruction mneumonic (ex. M+D)
 * 	val => decimal value of instruction
 */
typedef struct node_t {
	char			*name;
	unsigned short	val;
	struct node_t	*next;
}


/*
 * Head node pointers for symbol table, destination, comparison, and jump
 * linked lists
 *
 * I could not find any guidance on where these should go, so I am declaring
 * them in the header file. Hopefully this is how you are supposed to do it.
 */
node_t *sym_head = NULL;
node_t *dest_head = NULL;
node_t *comp_head = NULL;
node_t *jump_head = NULL;


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


/*
 * This function adds another node to the linked list of the head node that is
 * passed to it (i.e. passing sym_head as the head_node will add another node
 * to the symbol table linked list).
 *
 * This function will return a node pointer to the new head of whichever list
 * is passed to it; for example:
 *
 * sym_head = add_node(sym_head, name, strlen(name), 10) will create a new
 * symbol table node named "name" with the value "10" and return a pointer to
 * the new sym_head node
 */
node_t * add_node(node_t *head_node, char *name, int name_len, unsigned short value);


/*
 * This function takes all head nodes as arguments and will iterate through
 * each of the linked lists, freeing the allocated memory for node->name and
 * for the node itself. This function will return 0 on success.
 */
int delete_lists(node_t *sym_head, node_t *dest_head, node_t *comp_head, node_t *jump_head);


/*
 * This function takes all head nodes as arguments and will iterate through
 * each of the linked lists, printing each node name and value. This function
 * is meant for debugging purposes and will not be used in the final program
 */
int print_lists(node_t *sym_head, node_t *dest_head, node_t *comp_head, node_t *jump_head);


/*
 * This function is meant to initialize the assembler by loading all of the
 * Pre-Defined Symbols, Destination-Bits, Computation-Bits, and Jump-Bits
 * into their respective tables. It will return 0 on success.
 *
 * I couldn't figure out a really good way to do this (maybe creating and
 * loading some kind of config file?), so this function will be extremely
 * long and repetative.
 */
int assembler_init


#endif	//end HACKASSEM_H
