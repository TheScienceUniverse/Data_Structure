#ifndef NODE_H
#define NODE_H

// ---------- x ----------

#include "./data.h"
#include "./list.h"

// ---------- x ----------

typedef enum NODE_TYPE {
	N_Undefined
	, N_LinkedList
	, N_Stack
	, N_Queue
	, N_Tree
	, N_Graph
} Node_Type;

typedef struct NODE {
	Node_Type type;
	String* name;
	List* address_list;
	Data* data;
} Node;

// ---------- x ----------

Node* create_node (Node_Type);
Node* duplicate_node (Node*);
void delete_node (Node**);
void set_node_name (Node*, int, char*);
void display_node (Node*);
void display_node_details (Node*);

#endif