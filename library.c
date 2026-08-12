#include"stdio.h"

typedef struct

{

    int id;
    char title[50];
    char author[50];
    int year;
    int available;

} Book;

void addBook(Book *b)
{
	printf("\nEnter Book id:");
	scanf("%d",&b->id);
	printf("\nEnter Book title:");
	scanf(" %49[^\n]", b->title);
	printf("\nEnter Book author:");
        scanf(" %49[^\n]", b->author);
        printf("\nEnter Book year:");
        scanf("%d",&b->year);

	b->available=1;
	printf("\nBook added successfully!\n");

}

void showBook(Book b){
	printf("\n----------------------------------\n");
	printf(" Book Display\n");
	printf("-------------------------------------\n");
	printf("Book ID : %d\n", b.id);
	printf("Title : %s\n", b.title);
	printf("Author : %s\n", b.author);
	printf("Year : %d\n", b.year);
	if(b.available == 1)
	printf("Status : Available\n");
	else
	printf("Status : Not Available\n");
	printf("--------------------------------------\n");	

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
	int choices;
	do
	{
		showMenu();
		Book book;
		printf("Enter your choice: ");
		scanf("%d", &choices);
		switch(choices)
		{
			case 1:
				addBook(&book);
				break;
			case 2:
				showBook(book);
				break;
			case 3:
				printf("Delete book");
				break;
			case 4:
				printf("Search book");
				break;
			case 5:
				printf("Issue book");
				break;
			case 6:
				printf("Return book");
				break;
			case 7:
				printf("Display book");
				break;
			default :
				printf("Invalid ! Try Again.....\n");
		}
		
	}while(choices !=8 );
		return 0;
}

