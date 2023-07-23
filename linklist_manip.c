#include "holberton.h"






/**
 * free_sep_list - deallocate the memory used by linked list nodes
 * @head: linked list head
 * Return: nothing.
 */
void free_sep_list(sep_list **head)
{
	sep_list *ptr_1 = *head;

	sep_list *temp_ptr;

	while (ptr_1 != NULL)
	{
		temp_ptr = ptr_1;
		ptr_1 = ptr_1->next;
		free(temp_ptr);
	}

	*head = NULL;
}



/**
 * free_line_list - frees the memory occupied by a linked list of
 * line_list nodes.
 * @head: head of the linked list.
 * Return: nothing
 */
void free_line_list(line_list **head)
{

	line_list *ptr_1 = *head;

	line_list *temp_ptr;

	if (head == NULL || *head == NULL)
	{
		return;
	}



	while (ptr_1 != NULL)
	{
		temp_ptr = ptr_1->next;
		free(ptr_1);
		ptr_1 = temp_ptr;
	}

	*head = NULL;

}



/**
 * add_sep_node_end -  adds a new node to the end of a linked list of
 * sep_list structures
 * @head: linked list head
 * @separat: value of the separator field in the new node to be added
 * Return: updated head pointer
 */
sep_list *add_sep_node_end(sep_list **head, char separat)
{
	sep_list *new_node = malloc(sizeof(sep_list));

	sep_list *temp_ptr;


	if (new_node == NULL)
		return (NULL);


	new_node->separator = separat;

	new_node->next = NULL;

	switch (*head == NULL)
	{
		case 1:
			*head = new_node;
			break;
		default:
			{
				temp_ptr = *head;
				while (temp_ptr->next != NULL)
					temp_ptr = temp_ptr->next;
				temp_ptr->next = new_node;
			}
	}

	return (*head);

}





/**
 * add_line_node_end - adds a new node to the end of a linked list elements
 * @head: linked list head
 * @ptr_line: pointer from the input is assigned to the line field of
 * the new node,
 * storing the string in the node.
 * Return:  updated head pointer
 */
line_list *add_line_node_end(line_list **head, char *ptr_line)
{
	line_list *new_node = malloc(sizeof(line_list));

	line_list **last_ptr;


	if (new_node == NULL)
	{

		return (NULL);
	}


	new_node->line = ptr_line;

	new_node->next = NULL;

	last_ptr = head;

	while (*last_ptr != NULL)
	{
		last_ptr = &((*last_ptr)->next);
	}

	*last_ptr = new_node;

	return (*head);

}


