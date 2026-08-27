/* SMART LIBRARY MANAGEMENT SYSTEM*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 500
#define MAX_STACK 100
#define TITLE_LEN 80
#define NAME_LEN 60
#define CAT_LEN 40

typedef struct {
    int id;
    char title[TITLE_LEN];
    char author[NAME_LEN];
    char category[CAT_LEN];
    int year;
    int available;
} Book;

typedef struct StudentNode {
    int id;
    char name[NAME_LEN];
    char department[NAME_LEN];
    struct StudentNode *next;
} StudentNode;

typedef struct StackNode {
    int bookId;
    struct StackNode *next;
} StackNode;

typedef struct QueueNode {
    int studentId;
    int bookId;
    struct QueueNode *next;
} QueueNode;

typedef struct TreeNode {
    int bookId;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

Book books[MAX_BOOKS];
int bookCount = 0;
StudentNode *studentHead = NULL;
StackNode *stackTop = NULL;
QueueNode *front = NULL, *rear = NULL;
TreeNode *bstRoot = NULL;

void readLine(char *s, int n) {
    if (fgets(s, n, stdin)) {
        s[strcspn(s, "\n")] = '\0';
    }
}

int findBookIndex(int id) {
    int i;
    for (i = 0; i < bookCount; i++)
        if (books[i].id == id) return i;
    return -1;
}

/* ---------------- BOOK ARRAY ---------------- */

void addBook(void) {
    if (bookCount >= MAX_BOOKS) {
        printf("Book storage is full.\n");
        return;
    }

    Book b;
    printf("Book ID: ");
    scanf("%d", &b.id);
    getchar();

    if (findBookIndex(b.id) != -1) {
        printf("Book ID already exists.\n");
        return;
    }

    printf("Title: ");
    readLine(b.title, TITLE_LEN);
    printf("Author: ");
    readLine(b.author, NAME_LEN);
    printf("Category: ");
    readLine(b.category, CAT_LEN);
    printf("Publication year: ");
    scanf("%d", &b.year);
    b.available = 1;

    books[bookCount++] = b;
    printf("Book added successfully.\n");
}

void displayBooks(void) {
    int i;
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }

    printf("\n%-6s %-25s %-20s %-15s %-6s %-20s\n",
           "ID", "Title", "Author", "Category", "Year", "Status");
    for (i = 0; i < bookCount; i++) {
        printf("%-6d %-25s %-20s %-15s %-6d %-10s\n",
               books[i].id, books[i].title, books[i].author,
               books[i].category, books[i].year,
               books[i].available ? "Available" : "Issued");
    }
}

void updateBook(void) {
    int id, idx;
    printf("Book ID to update: ");
    scanf("%d", &id);
    getchar();

    idx = findBookIndex(id);
    if (idx == -1) {
        printf("Book not found.\n");
        return;
    }

    printf("New title: ");
    readLine(books[idx].title, TITLE_LEN);
    printf("New author: ");
    readLine(books[idx].author, NAME_LEN);
    printf("New category: ");
    readLine(books[idx].category, CAT_LEN);
    printf("New year: ");
    scanf("%d", &books[idx].year);
    printf("Book updated.\n");
}

void deleteBook(void) {
    int id, idx, i;
    printf("Book ID to delete: ");
    scanf("%d", &id);
    idx = findBookIndex(id);

    if (idx == -1) {
        printf("Book not found.\n");
        return;
    }

    for (i = idx; i < bookCount - 1; i++)
        books[i] = books[i + 1];

    bookCount--;
    printf("Book deleted.\n");
}

/* ---------------- SEARCH ---------------- */

int linearSearch(int key) {
    int i;
    for (i = 0; i < bookCount; i++)
        if (books[i].id == key) return i;
    return -1;
}

void binarySearchMenu(void) {
    int key, low = 0, high = bookCount - 1, mid, found = -1;
    int i, j;
    Book temp;

    /* Make a temporary sorted copy */
    Book tempBooks[MAX_BOOKS];
    for (i = 0; i < bookCount; i++) tempBooks[i] = books[i];

    for (i = 0; i < bookCount - 1; i++)
        for (j = 0; j < bookCount - i - 1; j++)
            if (tempBooks[j].id > tempBooks[j+1].id) {
                temp = tempBooks[j];
                tempBooks[j] = tempBooks[j+1];
                tempBooks[j+1] = temp;
            }

    printf("Book ID to search: ");
    scanf("%d", &key);

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (tempBooks[mid].id == key) {
            found = mid;
            break;
        } else if (tempBooks[mid].id < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    if (found != -1)
        printf("Found: %d - %s\n", tempBooks[found].id, tempBooks[found].title);
    else
        printf("Book not found.\n");
}

/* ---------------- SORTING ---------------- */

void bubbleSort(void) {
    int i, j;
    Book temp;
    for (i = 0; i < bookCount - 1; i++)
        for (j = 0; j < bookCount - i - 1; j++)
            if (books[j].id > books[j+1].id) {
                temp = books[j];
                books[j] = books[j+1];
                books[j+1] = temp;
            }
    printf("Books sorted using Bubble Sort.\n");
}

void selectionSort(void) {
    int i, j, min;
    Book temp;
    for (i = 0; i < bookCount - 1; i++) {
        min = i;
        for (j = i + 1; j < bookCount; j++)
            if (books[j].id < books[min].id) min = j;
        if (min != i) {
            temp = books[i];
            books[i] = books[min];
            books[min] = temp;
        }
    }
    printf("Books sorted using Selection Sort.\n");
}

void insertionSort(void) {
    int i, j;
    Book key;
    for (i = 1; i < bookCount; i++) {
        key = books[i];
        j = i - 1;
        while (j >= 0 && books[j].id > key.id) {
            books[j+1] = books[j];
            j--;
        }
        books[j+1] = key;
    }
    printf("Books sorted using Insertion Sort.\n");
}

/* ---------------- STUDENT LINKED LIST ---------------- */

void addStudent(void) {
    StudentNode *n = (StudentNode*)malloc(sizeof(StudentNode));
    if (!n) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Student ID: ");
    scanf("%d", &n->id);
    getchar();
    printf("Name: ");
    readLine(n->name, NAME_LEN);
    printf("Department: ");
    readLine(n->department, NAME_LEN);

    n->next = studentHead;
    studentHead = n;
    printf("Student added.\n");
}

void displayStudents(void) {
    StudentNode *p = studentHead;
    if (!p) {
        printf("No students found.\n");
        return;
    }

    printf("\nID\tName\t\t\tDepartment\n");
    while (p) {
        printf("%d\t%-20s\t%s\n", p->id, p->name, p->department);
        p = p->next;
    }
}

StudentNode* findStudent(int id) {
    StudentNode *p = studentHead;
    while (p) {
        if (p->id == id) return p;
        p = p->next;
    }
    return NULL;
}

void deleteStudent(void) {
    int id;
    StudentNode *p = studentHead, *prev = NULL;

    printf("Student ID to delete: ");
    scanf("%d", &id);

    while (p && p->id != id) {
        prev = p;
        p = p->next;
    }

    if (!p) {
        printf("Student not found.\n");
        return;
    }

    if (prev) prev->next = p->next;
    else studentHead = p->next;

    free(p);
    printf("Student deleted.\n");
}

/* ---------------- STACK ---------------- */

void pushReturn(int bookId) {
    StackNode *n = (StackNode*)malloc(sizeof(StackNode));
    if (!n) return;
    n->bookId = bookId;
    n->next = stackTop;
    stackTop = n;
}

void displayRecentReturns(void) {
    StackNode *p = stackTop;
    if (!p) {
        printf("No returned books in stack.\n");
        return;
    }
    printf("Recently returned books (TOP first):\n");
    while (p) {
        printf("%d\n", p->bookId);
        p = p->next;
    }
}

/* ---------------- QUEUE ---------------- */

void enqueue(int studentId, int bookId) {
    QueueNode *n = (QueueNode*)malloc(sizeof(QueueNode));
    if (!n) return;
    n->studentId = studentId;
    n->bookId = bookId;
    n->next = NULL;

    if (!rear) front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
}

void displayQueue(void) {
    QueueNode *p = front;
    if (!p) {
        printf("Waiting queue is empty.\n");
        return;
    }
    printf("Waiting queue:\n");
    while (p) {
        printf("Student %d -> Book %d\n", p->studentId, p->bookId);
        p = p->next;
    }
}

/* ---------------- BST ---------------- */

TreeNode* createTreeNode(int id) {
    TreeNode *n = (TreeNode*)malloc(sizeof(TreeNode));
    if (!n) return NULL;
    n->bookId = id;
    n->left = n->right = NULL;
    return n;
}

TreeNode* bstInsert(TreeNode *root, int id) {
    if (!root) return createTreeNode(id);
    if (id < root->bookId)
        root->left = bstInsert(root->left, id);
    else if (id > root->bookId)
        root->right = bstInsert(root->right, id);
    return root;
}

int bstSearch(TreeNode *root, int key) {
    if (!root) return 0;
    if (root->bookId == key) return 1;
    if (key < root->bookId) return bstSearch(root->left, key);
    return bstSearch(root->right, key);
}

void inorder(TreeNode *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->bookId);
    inorder(root->right);
}

void preorder(TreeNode *root) {
    if (!root) return;
    printf("%d ", root->bookId);
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->bookId);
}

void rebuildBST(void) {
    int i;
    bstRoot = NULL;
    for (i = 0; i < bookCount; i++)
        bstRoot = bstInsert(bstRoot, books[i].id);
    printf("BST rebuilt from current books.\n");
}

/* ---------------- ISSUE / RETURN ---------------- */

void issueBook(void) {
    int bookId, studentId, idx;
    printf("Book ID: ");
    scanf("%d", &bookId);
    idx = findBookIndex(bookId);
    if (idx == -1) {
        printf("Book not found.\n");
        return;
    }

    printf("Student ID: ");
    scanf("%d", &studentId);
    if (!findStudent(studentId)) {
        printf("Student not found.\n");
        return;
    }

    if (!books[idx].available) {
        printf("Book is unavailable. Add student to waiting queue? (1=yes/0=no): ");
        int choice;
        scanf("%d", &choice);
        if (choice) enqueue(studentId, bookId);
        return;
    }

    books[idx].available = 0;
    printf("Book issued successfully.\n");
}

void returnBook(void) {
    int bookId, idx;
    printf("Book ID to return: ");
    scanf("%d", &bookId);
    idx = findBookIndex(bookId);

    if (idx == -1) {
        printf("Book not found.\n");
        return;
    }

    books[idx].available = 1;
    pushReturn(bookId);
    printf("Book returned successfully.\n");
}

/* ---------------- FILE HANDLING ---------------- */

void saveBooks(void) {
    FILE *fp = fopen("books.dat", "wb");
    if (!fp) {
        printf("Unable to save books.\n");
        return;
    }
    fwrite(&bookCount, sizeof(int), 1, fp);
    fwrite(books, sizeof(Book), bookCount, fp);
    fclose(fp);
    printf("Books saved.\n");
}

void loadBooks(void) {
    FILE *fp = fopen("books.dat", "rb");
    if (!fp) return;
    fread(&bookCount, sizeof(int), 1, fp);
    fread(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

void freeAll(void) {
    StudentNode *s;
    StackNode *st;
    QueueNode *q;

    while (studentHead) {
        s = studentHead;
        studentHead = studentHead->next;
        free(s);
    }
    while (stackTop) {
        st = stackTop;
        stackTop = stackTop->next;
        free(st);
    }
    while (front) {
        q = front;
        front = front->next;
        free(q);
    }
    rear = NULL;
}

/* ---------------- MENU ---------------- */

void menu(void) {
    printf("\n========== SMART LIBRARY MANAGEMENT ==========\n");
    printf("1. Add Book\n2. Display Books\n3. Update Book\n4. Delete Book\n");
    printf("5. Linear Search\n6. Binary Search\n");
    printf("7. Bubble Sort\n8. Selection Sort\n9. Insertion Sort\n");
    printf("10. Add Student\n11. Display Students\n12. Delete Student\n");
    printf("13. Issue Book\n14. Return Book\n");
    printf("15. Recent Returns (Stack)\n16. Waiting List (Queue)\n");
    printf("17. Rebuild BST\n18. BST Search\n19. Inorder\n20. Preorder\n21. Postorder\n");
    printf("22. Save Books\n23. Load Books\n0. Exit\n");
    printf("==============================================\n");
}

int main(void) {
    int choice, id, idx;

    loadBooks();

    do {
        menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: updateBook(); break;
            case 4: deleteBook(); break;

            case 5:
                printf("Book ID: ");
                scanf("%d", &id);
                idx = linearSearch(id);
                if (idx >= 0) printf("Found: %s\n", books[idx].title);
                else printf("Book not found.\n");
                break;

            case 6: binarySearchMenu(); break;
            case 7: bubbleSort(); break;
            case 8: selectionSort(); break;
            case 9: insertionSort(); break;

            case 10: addStudent(); break;
            case 11: displayStudents(); break;
            case 12: deleteStudent(); break;

            case 13: issueBook(); break;
            case 14: returnBook(); break;
            case 15: displayRecentReturns(); break;
            case 16: displayQueue(); break;

            case 17: rebuildBST(); break;
            case 18:
                printf("Book ID: ");
                scanf("%d", &id);
                printf(bstSearch(bstRoot, id) ? "Book ID exists in BST.\n"
                                              : "Book ID not found in BST.\n");
                break;
            case 19:
                printf("Inorder: ");
                inorder(bstRoot);
                printf("\n");
                break;
            case 20:
                printf("Preorder: ");
                preorder(bstRoot);
                printf("\n");
                break;
            case 21:
                printf("Postorder: ");
                postorder(bstRoot);
                printf("\n");
                break;

            case 22: saveBooks(); break;
            case 23: loadBooks(); printf("Books loaded.\n"); break;
            case 0: saveBooks(); freeAll(); printf("Thank you.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
 
