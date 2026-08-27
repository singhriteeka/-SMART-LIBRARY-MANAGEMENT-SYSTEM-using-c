#include"stdio.h"
#include <stdlib.h>
#define MAX_BOOKS 100

typedef struct

{

    int id;
    char title[50];
    char author[50];
    int year;
    int available;

} Book;

void addBook(Book books[MAX_BOOKS], int *count)
{
    if (*count >= MAX_BOOKS)
    {
        printf("\nLibrary is full!\n");
        return;
    }

    printf("\nEnter details of the Book %d\n", *count + 1);

    printf("\nEnter Book id: ");
    scanf("%d", &books[*count].id);
    printf("Enter Book title: ");
    scanf(" %49[^\n]", books[*count].title);
    printf("Enter Book author: ");
    scanf(" %49[^\n]", books[*count].author);
    printf("Enter Book year: ");
    scanf("%d", &books[*count].year);

    books[*count].available = 1;
    (*count)++;
    printf("\nBook added successfully!\n");
}

void showBook(Book books[MAX_BOOKS],int count)
{
	printf("\n------------------------------------\n");
	printf(" Book Display\n");
	printf("-------------------------------------\n");
	int n;
	if (count == 0)

    {

        printf("\nNo books available.\n");
        return;

    }

    for (n = 0; n < count; n++)

    {

        printf("\nBOOK %d\n", n + 1);
        printf("Book ID : %d\n", books[n].id);
        printf("Title   : %s\n", books[n].title);
        printf("Author  : %s\n", books[n].author);
        printf("Year    : %d\n", books[n].year);

        if (books[n].available == 1)
            printf("Status  : Available\n");
        else
            printf("Status  : Not Available\n");

        printf("--------------------------------------\n");

    }
}

int searchBook(Book books[MAX_BOOKS],int count)
{
	int i;
	int key;

	printf("\nEnter Book ID to search: ");
	scanf("%d",&key);
	for(i=0;i<count;i++)
	{
		if(books[i].id==key)
		{
			printf("\nBook Found!\n");
            		printf("Book ID : %d\n", books[i].id);
            		printf("Title   : %s\n", books[i].title);
            		printf("Author  : %s\n", books[i].author);
            		printf("Year    : %d\n", books[i].year);
            		printf("Status  : %s\n",	
        	           books[i].available ? "Available" : "Not Available");

			return i;
		}
	}
	printf("\nBook Not Found\n");
	return -1;
}

void sort(Book books[MAX_BOOKS],int count)
{
	int i,j;
	Book temp;

	for(i=0;i<count-1;i++){
	  for(j=0;j<count-1-i;j++)
	    {
		if(books[j].id>books[j+1].id)
		{
			temp = books[j];
			books[j] = books[j+1];
			books[j+1] = temp;
		}
	    }
	}
}

void showMenu()
{
	printf("\n============================================\n");
	printf("🏆SMART LIBRARY MANAGEMENT SYSTEM🏆");
	printf("\n============================================\n");

	printf("1.ADD BOOK\n");
	printf("2.UPDATE BOOK\n");
	printf("3.DELETE BOOK\n");
	printf("4.SEARCH BOOK\n");
    printf("5.ISSUE BOOK\n");
    printf("6.RETURN BOOK\n");
	printf("7.DISPLAY BOOK\n");
	printf("8.EXIT\n");
	
	printf("\n=============================================\n");
}
int main()

{

    Book book[MAX_BOOKS];

    int count = 0;
    int choices;

    while(1)

    {

        showMenu();

        printf("Enter your choice: ");
        scanf("%d", &choices);
        switch(choices)

        {

            case 1:

                addBook(book,&count);
                break;

            case 2:

                printf("Updated Book");
                break;	
        
            case 3:

                printf("Delete Book");
                break;

            case 4:
            
                searchBook(book,count);
                break;

            case 5:

                printf("Issue Book");
                break;

            case 6:

                printf("Return Book");
                break;
        
            case 7:
   
                showBook(book,count);
                break;

            case 8:

                printf("\nThank you for using Smart Library Management System!\n");
                exit(1);

            default:

                printf("\nInvalid! Try Again.....\n");

        }

    }

    return 0;

}                                     


