#include <stdlib.h>
#include <stdio.h>
#include "generic_vector.h"
#include "generic.h"
#include "my_string.h"
#include "associative_array.h"

struct node;
typedef struct node Node;

struct node {
	GENERIC_VECTOR data;
	MY_STRING key;
	Node* pLeft;
	Node* pRight;
	int height;
};

struct associative_array {
	Node* head;
	
}; typedef struct associative_array A_array;

void destroy_avl_tree(Node* pNode);
int get_balance(Node* head);
Node* rightRotate(Node* pNode);
Node* leftRotate(Node* pNode);
Node* node_insert(Node* head, MY_STRING hString_key, MY_STRING hString);
int height_of_node(Node* pNode);
void destroy_avl_tree(Node* pNode);
void print_avl_tree(Node* pNode);





ASSOCIATIVE_ARRAY associaive_array_init_default(void)
{
	A_array* pA_array = (A_array*)malloc(sizeof(A_array));
	if (pA_array == NULL)
	{
		printf("All hell broke loose."); exit(1);

	}
	pA_array->head = NULL;
	return (ASSOCIATIVE_ARRAY)pA_array;
}

int get_balance(Node* head)
{
	
	if (head->pLeft != NULL && head->pRight != NULL) // neither are null
	{
		return (head->pRight->height - head->pLeft->height);
	}
	else if (head->pLeft == NULL && head->pRight == NULL) // both are null
	{
		return 0;
	}
	else //one null
	{
		return (head->pLeft != NULL) ? 0 - head->pLeft->height : head->pRight->height;
	}
	
}

Node* rightRotate(Node* A)
{
	Node* B = A->pLeft;
	

	// Rotation
	A->pLeft = B->pRight;
	B->pRight = A;
	

	// update their heights
	A->height = ((height_of_node(A->pLeft) >= height_of_node(A->pRight)) ? height_of_node(A->pLeft) : height_of_node(A->pRight)) + 1;
	B->height = ((height_of_node(B->pLeft) >= height_of_node(B->pRight)) ? height_of_node(B->pLeft) : height_of_node(B->pRight)) + 1;

	return B;
}

Node* leftRotate(Node* A)
{
	Node* B = A->pRight;
	//Node* T2 = B->pLeft;

	// Rotation
	A->pRight = B->pLeft;
	B->pLeft = A;

	// update their heights
	A->height = ((height_of_node(A->pLeft) >= height_of_node(A->pRight)) ? height_of_node(A->pLeft) : height_of_node(A->pRight)) + 1;
	B->height = ((height_of_node(B->pLeft) >= height_of_node(B->pRight)) ? height_of_node(B->pLeft) : height_of_node(B->pRight)) + 1;

	return B;
}

Node* balance_node(Node* pNode, int balance)
{
	if (balance > 1)
	{
		
		if (get_balance(pNode->pRight) > 0)
		{
			return leftRotate(pNode);
		}

		if (get_balance(pNode->pRight) < 0) {
			pNode->pRight = rightRotate(pNode->pRight);
			return leftRotate(pNode);
		}
	}
	if (balance < -1)
	{
		
		if (get_balance(pNode->pLeft) < 0)
		{
			return rightRotate(pNode);
		}



		
		if (get_balance(pNode->pLeft) > 0) {
			pNode->pLeft = leftRotate(pNode->pLeft);
			return rightRotate(pNode);
		}
	}
	return NULL;
	

	

}
Node* node_insert(Node* head, MY_STRING hString_key, MY_STRING hString)

{

	if (head == NULL)//empty tree
	{
		Node* temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			printf("There was an error creating new tree node."); exit(1); // causes a memory leak but I'll fix it later
		}
		temp->pLeft = NULL;
		temp->pRight = NULL;
		temp->key = my_string_init_c_string("");
		my_string_assignment((ITEM*)&temp->key , (ITEM)hString_key);
		temp->data = generic_vector_init_default(&my_string_assignment, &my_string_destroy);
		temp->height = 1;
		head = temp;
		generic_vector_push_back(head->data, (ITEM)hString);
		return head;
	}
	else
	{
		if (my_string_compare(hString_key, head->key) < 0)//new key is less than current node
		{
			//Node* temp = head->pLeft;
			head->pLeft = node_insert(head->pLeft, hString_key, hString);
			head->height = (height_of_node(head->pRight) >= height_of_node(head->pLeft) ? height_of_node(head->pRight) : height_of_node(head->pLeft))+ 1;		//we added a node and it returns one indicating it got deeper
		}
		else if (my_string_compare(hString_key, head->key) == 0)//keys match, add the word to that keys list
		{
			generic_vector_push_back(head->data, (ITEM)hString);
		}
		else//new key is lexicographically greater than current node key
		{ 
			//Node* temp = head->pLeft;
			head->pRight = node_insert(head->pRight, hString_key, hString);
			head->height = (height_of_node(head->pRight) >= height_of_node(head->pLeft) ? height_of_node(head->pRight) : height_of_node(head->pLeft)) + 1;
		}
		int balance = get_balance(head);

		return (-1 <= balance && balance <= 1) ? head : balance_node(head, balance);
		
	}
}
void set_largest_node(Node* pNode,int* max, MY_STRING hString)
{
	if (pNode == NULL)
	{
		return;
	}
	set_largest_node(pNode->pLeft, max, hString);
	if (generic_vector_get_size(pNode->data) > *max)
	{
		*max = generic_vector_get_size(pNode->data);
		my_string_assignment((ITEM*)&hString, (ITEM)pNode->key);
	}
	set_largest_node(pNode->pRight, max, hString);

}
int set_best_family(ASSOCIATIVE_ARRAY hA_array, MY_STRING hCurrent_family)
{
	A_array* pA_array = (A_array*)hA_array;
	MY_STRING Best_key;
	Best_key = my_string_init_c_string("");
	int max = 0;
	set_largest_node(pA_array->head, &max, Best_key);
	if(my_string_compare(Best_key, hCurrent_family) == 0)
	{
		my_string_destroy((ITEM*)&Best_key);
		return 0;
	}
	else
	{
		my_string_assignment((ITEM*)&hCurrent_family, (ITEM)Best_key);
		my_string_destroy((ITEM*)&Best_key);
		return 1;
	}

}

int get_word_count_of_key(ASSOCIATIVE_ARRAY hA_array, MY_STRING hCurrent_family)
{
	A_array* pA_array = (A_array*)hA_array;
	Node* temp = pA_array->head;
	if (pA_array->head == NULL)
	{
		return -1;
	}
	int comp = my_string_compare(hCurrent_family, temp->key );
	while (comp != 0)
	{
		if (comp == -1)
		{
			temp = temp->pLeft;
			comp = my_string_compare(hCurrent_family, temp->key);
		}
		else
		{
			temp = temp->pRight;
			comp = my_string_compare(temp->key, hCurrent_family);
		}
	}
	return (generic_vector_get_size(temp->data));
}

void associate_array_insert_word(ASSOCIATIVE_ARRAY hA_array, MY_STRING hString_key, MY_STRING hString)
{
	A_array* pA_array = (A_array*)hA_array;
	pA_array->head = node_insert(pA_array->head, hString_key, hString);
}

int height_of_node(Node* pNode)

{
	if (pNode == NULL)
	{
		return 0;
	}

	if (pNode->pLeft != NULL && pNode->pRight != NULL)
	{
		return ((pNode->pLeft->height >= pNode->pRight->height) ? pNode->pLeft->height : pNode->pRight->height) + 1;
	}
	else if(pNode->pLeft != NULL || pNode->pRight != NULL)//one or both of the children is equal to null
	{
		return ((pNode->pLeft != NULL) ? pNode->pLeft->height : pNode->pRight->height) + 1;
	}
	else // no chillens
	{
		return 1;
	}
}

void print_families(ASSOCIATIVE_ARRAY hA_array)
{
	A_array* pA_array = (A_array*)hA_array;
	print_avl_tree(pA_array->head);
}

ITEM associative_array_key_data_at_index(ASSOCIATIVE_ARRAY hA_array, MY_STRING hKey, int index)
{
	A_array* pA_array = (A_array*)hA_array;
	Node* temp = pA_array->head;
	if (pA_array->head == NULL)
	{
		return NULL;
	}
	int comp = my_string_compare(hKey, temp->key);
	while (comp != 0)
	{
		if (comp == -1)
		{
			temp = temp->pLeft;
			comp = my_string_compare(hKey, temp->key);
		}
		else
		{
			temp = temp->pRight;
			comp = my_string_compare(temp->key, hKey);
		}
	}
	return generic_vector_at(temp->data, index);
}



void print_avl_tree(Node* pNode)
{
	if (pNode == NULL)
	{
		return;
	}
	print_avl_tree(pNode->pLeft);
	my_string_insertion(pNode->key, stdout);
	printf(" %d\n", generic_vector_get_size(pNode->data));
	print_avl_tree(pNode->pRight);
}

void destroy_associative_array(ASSOCIATIVE_ARRAY* phA_array, Bool partial)
{
	A_array* pA_array = (A_array*)*phA_array;
	destroy_avl_tree(pA_array->head);
	pA_array->head = NULL;
	if (!partial)
	{
		free(pA_array); *phA_array = NULL;
	}
}

void destroy_avl_tree(Node* pNode)
{
	//post order traversal
	//LRS
	if (pNode == NULL)
	{
		return;
	}
	destroy_avl_tree(pNode->pLeft);
	destroy_avl_tree(pNode->pRight);
	generic_vector_destroy(&(pNode->data));
	my_string_destroy(&(pNode->key));
	free(pNode);
	pNode = NULL;
}
