#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

// Create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
void insertAtBeginning(int value) {
    struct Node *newNode = createNode(value);
    newNode->next = head;
    head = newNode;
    printf("%d inserted at beginning.\n", value);
}

// Insert at end
void insertAtEnd(int value) {
    struct Node *newNode = createNode(value);

    if (head == NULL) {
        head = newNode;
        printf("%d inserted as first node.\n", value);
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("%d inserted at end.\n", value);
}

// Insert after a given position (1-based)
void insertAtPosition(int value, int position) {
    if (position <= 0) {
        printf("Invalid position.\n");
        return;
    }

    if (position == 1) {
        insertAtBeginning(value);
        return;
    }

    struct Node *temp = head;
    int i = 1;
    while (temp != NULL && i < position - 1) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Position is out of range.\n");
        return;
    }

    struct Node *newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;

    printf("%d inserted at position %d.\n", value, position);
}

// Delete by value
void deleteByValue(int value) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    if (temp != NULL && temp->data == value) {
        head = temp->next;
        free(temp);
        printf("%d deleted from list.\n", value);
        return;
    }

    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value %d not found in list.\n", value);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("%d deleted from list.\n", value);
}

// Search value
void searchValue(int value) {
    struct Node *temp = head;
    int position = 1;
    while (temp != NULL) {
        if (temp->data == value) {
            printf("Value %d found at position %d.\n", value, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Value %d not found.\n", value);
}

// Display list
void displayList() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Delete all nodes
void deleteAll() {
    struct Node *temp = head;
    while (temp != NULL) {
        struct Node *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    head = NULL;
    printf("All nodes deleted. List is now empty.\n");
}

int main() {
    int choice, value, position;

    while (1) {
        printf("\n===== SINGLY LINKED LIST OPERATIONS =====\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete by Value\n");
        printf("5. Search Value\n");
        printf("6. Display List\n");
        printf("7. Delete Entire List\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            insertAtBeginning(value);
            break;

        case 2:
            printf("Enter value: ");
            scanf("%d", &value);
            insertAtEnd(value);
            break;

        case 3:
            printf("Enter value: ");
            scanf("%d", &value);
            printf("Enter position: ");
            scanf("%d", &position);
            insertAtPosition(value, position);
            break;

        case 4:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            deleteByValue(value);
            break;

        case 5:
            printf("Enter value to search: ");
            scanf("%d", &value);
            searchValue(value);
            break;

        case 6:
            displayList();
            break;

        case 7:
            deleteAll();
            break;

        case 8:
            printf("Exiting...\n");
            deleteAll();
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

