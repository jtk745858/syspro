#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data);
int pop(struct node *top);
void printStack(struct node *top);

int main() {
	struct node *head = (struct node *)malloc(sizeof(struct node));
	head->next = NULL;
	head->data = 0;
	int input;
    int result;

	while(1) {
		result = scanf("%d", &input);
		if (result != 1 || input <= 0) {
            break;
        }
		push(head, input);
    }
	printf("\nPrint stack:\n");
    printStack(head);

	while(head->next != NULL) {
        pop(head);
    }
    free(head);

    return 0;
}
void push(struct node *top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
	newNode->next = top->next;
    top->next = newNode;
}

int pop(struct node *top) {
	if (top->next == NULL) {
        printf("Stack is empty.\n");
        return -1;
	}
	struct node *temp = top->next;
	int popData = temp->data;
	top->next = temp->next;
	free(temp);
	return popData;
}
void printStack(struct node *top) {
	struct node *curr = top->next;
	while (curr != NULL) {
        printf("%d\n", curr->data);
        curr = curr->next;
    }
}
