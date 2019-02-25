// Program made by Patrick J. Sherbondy
// February 8, 2019
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

// This function inserts a node with the integer data inside of it.
// It points to whatever node the "next" parameter is pointing to.
// It returns the address of the newly-allocated node.
node *insertNode(int data, node *next)
{
	node *node = malloc(sizeof(node));

	// node is only NULL if malloc() did not allocate enough space.
	if (node == NULL)
	{
		fprintf(stderr, "Could not allocate enough space in insertNode()\n");
		exit(1);
	}

	// Set up the struct members.
	node->data = data;
	node->next = next;

	return node;
}

// This function sorts through the array, and allocates a new node to place data into.
void findPlace(node **head, int data)
{
	node *temp;
	int previous;

	// If no node exists yet, make the first node - a head.
	if (*head == NULL)
	{
		*head = insertNode(data, NULL);
		return;
	}

	// If data is less than or equal to the data in head, create a new node and place it before
	// head. This new node becoems the new head of the linked list.
	if (data <= (*head)->data)
	{
		*head = insertNode(data, *head);
		return;
	}

	// For all other cases, we must loop through the linked list to find the appropriate spot for
	// data.
	for (temp = *head; temp != NULL; temp = temp->next)
	{
		// Inserts at the tail of the list.
		if (temp->next == NULL)
		{
			temp->next = insertNode(data, NULL);
			return;
		}
		// Inserts a node between two pre-existing nodes.
		else if (previous < data && data <= temp->next->data)
		{
			temp->next = insertNode(data, temp->next);
			return;
		}

		// Update previous to reflect what was in the data member of the previous node.
		previous = temp->data;
	}
}

// This function loops through the linked list and prints out the data stored in each node.
void printList(node *head)
{
	node *temp;

	// If head is NULL, then there is no data to print out.
	if (head == NULL)
	{
		printf("The linked list is empty!\n");
		return;
	}

	// Loop through the list and print out every data member.
	// The output terminates with a newline character.
	for (temp = head; temp != NULL; temp = temp->next)
	{
		printf("%d%c", temp->data, (temp->next != NULL) ? ' ' : '\n');
	}

	return;
}

// This function gets rid of all dynamically-allocated memory before the program terminates.
void destroyNodes(node **head)
{
	node *temp;

	while (*head != NULL)
	{
		temp = (*head)->next;
		free(*head);

		*head = temp;
	}
}

// This function takes input from the user, and calls various functions to sort and display the
// data passed to it.
void userInput(void)
{
	int data, size;
	node *head = NULL;

	printf("Input as many integers as you would like, and this program will automatically");
	printf(" sort them for you!\n\n");

	printf("How many integers do you want to input?\n");
	scanf("%d", &size);

	while (size > 0)
	{
		printf("Please input an integer: ");
		scanf("%d", &data);

		// Pass the address of head to easily allow head to be modified across multiple functions.
		findPlace(&head, data);
		printList(head);
		size--;
	}

	// Clean up after yourself.
	destroyNodes(&head);
}

int main(void)
{
	userInput();

	return 0;
}
