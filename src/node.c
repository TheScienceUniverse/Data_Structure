#include "../lib/node.h"

Node *create_node (Node_Type type) {
	Node *node = (Node *) malloc (sizeof (Node));

	if (node != NULL) {
		node -> type = type;
		node -> name = NULL;
		node -> data = NULL;

		switch (node -> type) {		// setting up address list
			case N_Undefined:
				node -> address_list = NULL;
				break;
			case N_LinkedList:
			case N_Stack:
			case N_Queue:
				node -> address_list = create_list (2);		// previous address, next address (default count = 2)
				break;
			case N_Tree:
				node -> address_list = create_list (1);		// parent address + (Optional / zero or more) child addresses (default count = 1)
				break;
			case N_Graph:
				node -> address_list = create_list (0);		// no addresses by default + add when connected with others (default count = 0)
				break;
			default:
				break;
		}
	}

	return node;
}

Node* duplicate_node (Node *node) {
	if (node == NULL) {
		perror ("Given source node does not exist!\n");
		exit (1);
	}

	Node *new_node = create_node (node -> type);

	if (new_node != NULL) {
		new_node -> type = node -> type;
		new_node -> name = duplicate_string (node -> name);
		new_node -> data = duplicate_data (node -> data);
		new_node -> address_list = duplicate_list (node -> address_list);
	}

	return new_node;
}

void delete_node (Node **node_address) {
	if (*node_address == NULL) {
		perror ("Node doesn't exist to delete!");
		return;
	}

	Node *node = *node_address;

	delete_string (&node -> name);
	delete_list (&node -> address_list);
	delete_data (&node -> data);

	node = NULL;
	ERASE (node_address);
}

void set_node_name (Node *node, int length, char *name) {
	if (node == NULL) {
		perror ("Error! => Node doesn't exist.\n");
		exit (1);
	}

	String *string = create_string (length, name);
	node -> name = string;
}

void display_node (Node *node) {
	if (node == NULL) {
		perror ("Error! => Node doesn't exist.");
		return;
	}

	printf ("(");
	display_string (node -> name);
	printf (")");
}

void display_node_details (Node *node) {
	if (node == NULL) {
		perror ("Node doesn't exist to display");
		return;
	}

	printf ("Type => [");

	switch (node -> type) {
		case N_Undefined:
			printf ("Undefined Node");
			break;
		case N_LinkedList:
			printf ("Linked-List Node");
			break;
		case N_Stack:
			printf ("Stack Node");
			break;
		case N_Queue:
			printf ("Queue Node");
			break;
		case N_Tree:
			printf ("Tree Node");
			break;
		default:
			break;
	}

	printf ("] Address => [");
	printf ("%p", node);
	printf ("] Name => [\"");
	display_string (node -> name);
	printf ("\"] Data => [");
	display_data (node -> data);
	printf ("] ");
	display_list_addresses (node -> address_list);
	//printf ("\n");
}