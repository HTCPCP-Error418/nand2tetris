/*
 * This file contains the common libraries, structures, and functions for
 * the HACK assembler
 */

#ifndef HACKASSEM_H
#define HACKASSEM_H	//begin HACKASSEM_H

//common libraries
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
 * The first three bits of a 16-bit C-instruction are constant (all 1). The
 * decimal value for the first three bits is 57344 and is defined here for
 * readability purposes and to avoid creating another global variable.
 * DOES THIS GET DEFINED HERE, OR IN HACK_FUNC.C? -- CHECK
 */
#define CHEADER 57344

/*
 * Structure for symbol nodes to build the linked list for the assembler's
 * symbol table
 */
typedef struct sym_node_t {
	char				*sym_name;	//symbol name
	unsigned int		val;		//symbol value (line number, mem address, pre-defined value)
	struct sym_node_t	*next;		//pointer to next node in linked list
} sym_node_t;


/*
 * Structure for C-instruction nodes to build a linked list allowing the
 * assembler to search for instruction names and translate them into
 * machine code
 */
typedef struct c_node_t {
	char			*inst_name;		//C-instruction name
	unsigned short	val;			//decimal value of binary representation of C-instruction
	struct c_node_t	*next;			//pointer to next node in linked list
} c_node_t;


/*
 * Recursive function that prints the binary representation of the provided
 * decimal number, which is assumed to be positive.
 * CAVEAT: Will not return any value and is currently not useful/used in the
 * HACK assembler. The function has not been removed, as it may be capable of
 * providing a cleaner version of "get_bin()" with some modification.
 * FUTURE NOTE: providing an array or allocated memory did not work, as there
 * was no good way to implement a counter to place the values in the correct
 * spot.
 */
void print_binary(unsigned int decimal);


/*
 * This function converts a provided decimal, which is assumed to be positive,
 * to a 15-bit binary representation of the decimal, allowing the assembler to
 * prepend the required op code and output to the machine code file without
 * checking and padding the output.
 * INPUT: (assumed positive) decimal, 15-bit array to store results
 * CAVEAT: This process uses a decrementing counter due to the forward process
 * returning the binary representation in reverse. Using a decrementing counter
 * reverses the order digits in the array, outputing the correct (non-reversed)
 * binary representation. RECURSIVE FUNCTION IS A PREFERRED ALTERNATIVE, IF
 * POSSIBLE.
 */
void get_bin(unsigned int decimal, int bin_arr[15]);


/*
 * Function to create a new Symbol Table node, returning a pointer to the
 * new node.
 * MAY REQUIRE MORE WORK -- UNTESTED FUNCTION
 */
void add_sym(char *name, int len, unsigned int value);


void print_symbol_table(void);


/*
 * Free the memory allocated for the Symbol Table and C-instruction Translation
 * table by iterating through both linked lists. This function uses the global
 * variables for the root node of each linked list and does not require the
 * pointers to be passed.
 * MAY REQUIRE MORE WORK -- UNTESTED FUNCTION
 */
bool free_mem(void);


/*
 * Function to be called when NULL checking pointers after allocating memory.
 * This function prints an error message indicating that the error rose from
 * issues when allocating memory, then calls the "free_mem()" function in an
 * attempt to free any memory that was successfully allocated earlier in the
 * execution of the program. After the memory has been freed, this fuction
 * exits with an exit code of 1.
 * MAY REQUIRE MORE WORK -- SHOULD EXIT CODE BE REPLACED BY MACROS?
 * (EXIT_SUCCESS or EXIT_FAILURE)
 */
void mem_error(void);

#endif //end HACKSASSEM_H
