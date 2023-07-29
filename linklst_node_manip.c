#include "main.h"

/**
 * freeVarLstF - frees the memory allocated for a linked list nodes.
 * @head: linked list head
 * Return: nothing
 */
void freeVarLstF(r_var **head)
{
	r_var *list_node = *head;

	r_var *next_node;


	while (list_node != NULL)
	{
		next_node = list_node->next;

		free(list_node);
		list_node = next_node;
	}

	*head = NULL;

}




/**
 * add_rvar_node - add a new node to a singly linked list of custom data type
 * @head: head of the linked list.
 * @var_len: variable length
 * @var_val: variable value
 * @val_len: value length.
 * Return:  updated head of the list.
 */
r_var *add_rvar_node(r_var **head, int var_len, char *var_val, int val_len)
{
	r_var *temp_ptr;
	r_var *new_node = malloc(sizeof(r_var));

	if (new_node == NULL)
		return (NULL);

	new_node->len_var = var_len;

	new_node->val = var_val;

	new_node->len_val = val_len;

	new_node->next = NULL;

	switch (*head == NULL)
	{
		case 1:
			*head = new_node;
			break;

		case 0:
		{
			temp_ptr = *head;

			while (temp_ptr->next != NULL)
				temp_ptr = temp_ptr->next;
			temp_ptr->next = new_node;
			break;
		}
	}


	return (*head);

}
