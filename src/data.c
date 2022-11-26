#include "../lib/data.h"

Data *create_data (Data_Type data_type, int block_size, void *address) {
	if (data_type == DT_Undefined || block_size == 0) {
		return NULL;
	}

	Data *data = (Data*) malloc (sizeof (Data));

	if (data != NULL) {
		data -> type = DT_Undefined;
		data -> size = 0;
		data -> address = NULL;
	}

	if (block_size > 0) {
		data -> type = data_type;
		data -> size = block_size;
		data -> address = malloc (block_size);

		if (data -> address != NULL) {
			if (data_type == DT_Address) {
				data -> address = address;
			} else {
				data -> address = memcpy (data -> address, address, block_size);
			}
		}
	}

	return data;
}

void forget_data (Data **data_address) {
	if (*data_address == NULL) {
		// perror ("Data does not exist to delete!");
		return;
	}

	Data *data = *data_address;

	if (data -> address != NULL) {
		data -> address = NULL;
		data -> type = DT_Undefined;
	}
}

void delete_data (Data **data_address) {
	if (*data_address == NULL) {
		// perror ("Data does not exist to delete!");
		return;
	}

	Data *data = *data_address;

	if (data -> address != NULL) {
		ERASE (&(data -> address));
	}

	data = NULL;
	ERASE (data_address);
}

Data* duplicate_data (Data *data) {
	if (data == NULL) {
		return NULL;
	}

	return create_data (data -> type, data -> size, data -> address);
}

void display_data (Data *data) {
	if (data == NULL) {
		// perror ("Data does not exist to display!");
		return;
	}

	if (data -> address == NULL) {
		// perror ("Address does not exist to display!");
		printf ("N/A");
		return;
	}

	switch (data -> type) {
		case DT_Undefined:
			printf ("N/A");
			break;
		case DT_Address:
			printf ("%p", data -> address);
			break;
		case DT_Binary:
			display_binary_data (data -> size, (BYTE*) data -> address);
			break;
		case DT_Integer:
			printf ("%d", *((int*) data -> address));
			break;
		case DT_String:
			display_raw_string (data -> size, data -> address);
			break;
		default:
			break;
	}
}

void display_data_properties (Data *data) {
	if (data == NULL) {
		perror ("Data is empty");
		exit (1);
	}

	switch (data -> type) {
		case DT_Binary:
			display_binary_data (data -> size, (BYTE*) data -> address);
			break;
		case DT_Integer:
			printf ("Data (Integer) : %d\n", *((int*) data -> address));
			break;
		case DT_String:
			printf ("Data (String) [%d]: ", data -> size);
			display_raw_string (data -> size, (char*) data -> address);
			printf ("\n");
			break;
		default:
			break;
	}
}

void display_binary_data (int size, BYTE *address) {
	for (int i = 0; i < size; i++) {
		printf ("%02x", *(address + i));
	}
}