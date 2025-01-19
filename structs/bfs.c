#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Define the structure for a queue node
typedef struct QueueNode {
    TreeNode *treeNode;
    struct QueueNode *next;
} QueueNode;

// Define the structure for the queue
typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

// Function to create a new tree node
TreeNode* createTreeNode(int value) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to initialize a queue
Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// Function to enqueue a tree node
void enqueue(Queue *q, TreeNode *node) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = node;
    newNode->next = NULL;
    if (q->rear) {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (q->front == NULL) {
        q->front = q->rear;
    }
}

// Function to dequeue a tree node
TreeNode* dequeue(Queue *q) {
    if (isEmpty(q)) {
        return NULL;
    }
    QueueNode *temp = q->front;
    TreeNode *node = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return node;
}

// Breadth-First Search function
void bfs(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    Queue *q = createQueue();
    enqueue(q, root);
    while (!isEmpty(q)) {
        TreeNode *current = dequeue(q);
        printf("%d ", current->value);
        if (current->left) {
            enqueue(q, current->left);
        }
        if (current->right) {
            enqueue(q, current->right);
        }
    }
    free(q);
}

// Main function to test the BFS implementation
int main() {
    // Create a sample tree
    TreeNode *root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    printf("BFS Traversal: ");
    bfs(root);
    printf("\n");

    return 0;
}

// with a linked list

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Define the structure for a linked list node
typedef struct ListNode {
    TreeNode *treeNode;
    struct ListNode *next;
} ListNode;

// Function to create a new tree node
TreeNode* createTreeNode(int value) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to add a node to the end of the linked list
void append(ListNode **head, TreeNode *treeNode) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    ListNode *temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to remove the first node from the linked list
TreeNode* pop(ListNode **head) {
    if (*head == NULL) {
        return NULL;
    }
    ListNode *temp = *head;
    TreeNode *node = temp->treeNode;
    *head = (*head)->next;
    free(temp);
    return node;
}

// Breadth-First Search function
void bfs(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    ListNode *frontier = NULL; // Initialize the linked list as empty
    append(&frontier, root);   // Add the root node to the list
    while (frontier != NULL) {
        TreeNode *current = pop(&frontier); // Pop the first node
        printf("%d ", current->value);     // Print the node's value
        if (current->left) {
            append(&frontier, current->left); // Add the left child
        }
        if (current->right) {
            append(&frontier, current->right); // Add the right child
        }
    }
}

// Main function to test the BFS implementation
int main() {
    // Create a sample tree
    TreeNode *root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    printf("BFS Traversal: ");
    bfs(root);
    printf("\n");

    return 0;
}

////3rd case

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} *TreeNode;  // TreeNode is now a pointer to struct TreeNode

// Define the structure for a linked list node
typedef struct ListNode {
    TreeNode treeNode;
    struct ListNode *next;
} ListNode;

// Function to create a new tree node
TreeNode createTreeNode(int value) {
    TreeNode newNode = (TreeNode)malloc(sizeof(struct TreeNode)); // Allocate memory for a TreeNode
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to add a node to the end of the linked list
void append(ListNode **head, TreeNode treeNode) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    ListNode *temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to remove the first node from the linked list
TreeNode pop(ListNode **head) {
    if (*head == NULL) {
        return NULL;
    }
    ListNode *temp = *head;
    TreeNode node = temp->treeNode;
    *head = (*head)->next;
    free(temp);
    return node;
}

// Breadth-First Search function
void bfs(TreeNode root) {
    if (root == NULL) {
        return;
    }
    ListNode *frontier = NULL; // Initialize the linked list as empty
    append(&frontier, root);   // Add the root node to the list
    while (frontier != NULL) {
        TreeNode current = pop(&frontier); // Pop the first node
        printf("%d ", current->value);     // Print the node's value
        if (current->left) {
            append(&frontier, current->left); // Add the left child
        }
        if (current->right) {
            append(&frontier, current->right); // Add the right child
        }
    }
}

// Main function to test the BFS implementation
int main() {
    // Create a sample tree
    TreeNode root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    printf("BFS Traversal: ");
    bfs(root);
    printf("\n");

    return 0;
}

