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
node_t * add_node(node_t *head_node, char *name, int name_len, unsigned short value) {
	//allocate memory for new node
	node_t *new_node = calloc(1, sizeof(node_t));
	if (new_node == NULL) {
		//error allocating memory for new node
		return NULL;
	}

	//allocate memory for name in new node, len + 1 due to terminating character
	new_node->name = calloc(name_len + 1, sizeof(char));
	if (new_node->name == NULL) {
		//error allocating memory for name
		return NULL;
	}

	new_node->val = value;

	//set new node as head of the linked list
	new_node->next = head_node;

	return new_node;
}


/*
 * This function takes all head nodes as arguments and will iterate through
 * each of the linked lists, freeing the allocated memory for node->name and
 * for the node itself. This function will return 0 on success.
 */
int delete_lists(node_t *sym_head, node_t *dest_head, node_t *comp_head, node_t *jump_head) {
	//create traversal pointer
	node_t *trav = NULL;

	//free memory from symbol table
	while (sym_head != NULL) {
		trav = sym_head;
		sym_head = sym_head->next;
		free(trav->name);
		free(trav);
	}

	//free memory from destination-bit linked list
	while (dest_head != NULL) {
		trav = dest_head;
		dest_head = dest_head->next;
		free(trav->name);
		free(trav);
	}

	//free memory from computation-bit linked list
	while (comp_head != NULL) {
		trav = comp_head;
		comp_head = comp_head->next;
		free(trav->name);
		free(trav);
	}

	//free memory from jump-bit linked list
	while (jump_head != NULL) {
		trav = jump_head;
		jump_head = jump_head->next;
		free(trav->name);
		free(trav);
	}

	return 0;
}


/*
 * This function takes all head nodes as arguments and will iterate through
 * each of the linked lists, printing each node name and value. This function
 * is meant for debugging purposes and will not be used in the final program
 */
int print_lists(node_t *sym_head, node_t *dest_head, node_t *comp_head, node_t *jump_head) {
	//create traversal pointer
	node_t *trav = sym_head;

	//print symbol table
	printf("Symbol Table:\n");
	while (trav != NULL) {
		printf("\t%s:\t%hu\n", trav->name, trav->val);
		trav = trav->next;
	}

	//print destination-bit linked list
	trav = dest_head
	printf("\nDestination Bits:\n");
	while (trav != NULL) {
		printf("\t%s:\t%hu\n", trav->name, trav->val);
		trav = trav->next;
	}

	//print computation-bit linked list
	trav = comp_head
	printf("\nComputation Bits:\n");
	while (trav != NULL) {
		printf("\t%s:\t%hu\n", trav->name, trav->val);
		trav = trav->next;
	}

	//print jump-bit linked list
	trav = jump_head
	printf("\nJump Bits:\n");
	while (trav != NULL) {
		printf("\t%s:\t%hu\n", trav->name, trav->val);
		trav = trav->next;
	}

	return 0;
}
