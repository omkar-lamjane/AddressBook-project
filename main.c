#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    do
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        if((scanf("%d",&choice)) != 1)      // CONDITION USED FOR CLEARING THE BUFFER TO HANDLE INVALID INPUT(LIKE STRINGS)
        {
            while(getchar() != '\n');       // CLEAR BUFFER
            choice = -1;                    //SET CHOICE TO INVALID
        }
        else
        {
            while(getchar() != '\n');       //CLEAR LEFTOVER NEWLINE
        }
       
        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook);
            break;
        case 6:
            printf("Saving...\n");
            saveContactsToFile(&addressBook);
            break;
        case 7:
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
