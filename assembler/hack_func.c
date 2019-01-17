/*
 * This file contains the definitions for the functions prototyped in
 * "hack_assem.h" and utilized for the HACK assembler program.
 * This file also contains the Symbol Table (sym_tbl) and C-instruction
 * Translation Table (c_tbl) linked list root nodes, declared as global
 * variables.
 */

#include "hack_assem.h"

/*
 * Global variable definitions
 * "sym_tbl" is the root node of the Symbol Table linked list
 * "c_tbl" is the root node of the C-instruction Translation Table linked list
 */
sym_node_t *sym_tbl = NULL;			//CHECK IF THIS IS THE CORRECT WAY TO CREATE A ROOT NODE
c_node_t *c_tbl = NULL;


/*
 * Recursive function that prints the binary representation of the provided
 * decimal number, which is assumed to be positive.
 * CAVEAT: Will not return any value and is currently not useful/used in the
 * HACK assembler. The function has not been removed, as it may be capable of
 * providing a cleaner version of "get_bin()" with some modification.
 */
void print_binary(unsigned int decimal) {
	if (decimal > 1) {
		print_binary(decimal / 2);
	}
	printf("%d ", decimal % 2);
}


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
void get_bin(unsigned int decimal, int bin_arr[15]) {
	for (int i = 14; i >= 0; i--) {
		if (decimal < 1) {
			bin_arr[i] = 0;
		} else {
			bin_arr[i] = decimal % 2;
			decimal /= 2;
		}
	}
}


/*
 * Function to create a new Symbol Table node, returning a pointer to the
 * new node.
 * MAY REQUIRE MORE WORK -- UNTESTED FUNCTION
 */
sym_node_t * add_sym(void) {
	sym_node_t *n = calloc(1, sizeof(sym_node_t));
	if (!n) {
		mem_error();
	}
	n->next = NULL;
	return n;
}


/*
 * Free the memory allocated for the Symbol Table and C-instruction Translation
 * table by iterating through both linked lists. This function uses the global
 * variables for the root node of each linked list and does not require the
 * pointers to be passed.
 * MAY REQUIRE MORE WORK -- UNTESTED FUNCTION
 */
bool free_mem(void) {
	sym_node_t *sym_tmp = sym_tbl;		//traversal pointer for sym_tbl
	while (sym_tbl) {
		sym_tmp = sym_tbl;
		sym_tbl = sym_tbl->next;
		if (sym_tmp->sym_name) {		//if symbol name is set, free that, too
			free(sym_tmp->sym_name);
			sym_tmp->sym_name = NULL;
		}
		sym_tmp->next = NULL;
		free(sym_tmp);
	}

	c_node_t *c_tmp = c_tbl;			//traversal pointer for c_tbl
	while (c_tbl) {
		c_tmp = c_tbl;
		c_tbl = c_tbl->next;
		if (c_tmp->inst_name) {
			free(c_tmp->inst_name);
			c_tmp->inst_name = NULL;
		}
		c_tmp->next = NULL;
		free(c_tmp);
	}

	return true;
}


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
void mem_error(void) {
	printf("Error allocating memory\n");
	free_mem();
	exit(1)
}


/*
 * Function that prints the usage information for the compiled program and
 * exits with an exit code of 0. This function was added to simplify the
 * main code while conducting testing and may be removed when the HACK
 * assembler is finished to make way for a more comprehensive message.
 */
void usage(void) {
	printf("Usage: assembler [] []\n");
	exit(0);
}
