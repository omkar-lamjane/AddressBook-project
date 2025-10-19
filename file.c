#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{

    FILE* fptr;                                         // FILE POINTER DECLARATION
    fptr = fopen("contacts.csv","r+");                  // OPEN FILE IN READ+WRITE MODE
    fprintf(fptr,"%d\n",addressBook->contactCount);     // WRITE TOTAL CONTACT COUNT AS FIRST LINE
    for(int i=0; i<addressBook->contactCount; i++)
    {
        // WRITE CONTACT DETAILS TO FILE IN CSV FORMAT
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);                                       // CLOSE FILE AFTER WRITING
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE* fptr;                                     // FILE POINTER DECLARATION
    fptr = fopen("contacts.csv","r+");              // OPEN FILE IN READ+WRITE MODE
    fscanf(fptr,"%d\n",&addressBook->contactCount); // READ TOTAL CONTACT COUNT FROM FIRST LINE
    for(int i=0;i<addressBook->contactCount; i++)
    {
        // READ NAME, PHONE, EMAIL SEPARATED BY COMMAS
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);                                   // CLOSE FILE AFTER READING
}
