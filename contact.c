#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// #include "populate.h"

void listContacts(AddressBook *addressBook)
{
    // Main function to list contacts
    void sortname(AddressBook*);
    void sortphone(AddressBook*);
    void sortemail(AddressBook*);
    void displayall(AddressBook*);
    int choice;
    do
        {
            printf("\nSort Contacts:\n");
            printf("1. By Name\n");
            printf("2. By Number\n");
            printf("3. By Email\n");
            printf("4. Display all contacts\n");
            printf("5. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                sortname(addressBook);
                break;
            case 2:
                sortphone(addressBook);
                break;
            case 3:
                sortemail(addressBook);
                break;
            case 4:
                displayall(addressBook);
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 5);
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
     loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    int flag;
    char Name[30];
    char number[20];
    char mail[50];


    // FOR VALIDATION CRESATED SEPERATE FUNCTIONS
    int valid_name(char* );
    int valid_phone(char* ,AddressBook*);
    int valid_mail(char* ,AddressBook*);


    // FOR NAME VALIDATION
    do
    { 
        flag = valid_name(Name);

    }while(!flag);
    


    // FOR NUMBER VALIDATION 

    do
    {
        flag = valid_phone(number, addressBook);
    }while(!flag);



    // FOR EMAIL VALIDATION 

    do
    {
        flag = valid_mail(mail,addressBook);

    }while(!flag);

    //AFTER VALIDATING ALL DATA (NAME , NUMBER , EMAIL) STORED IN ARRAY OF STRUCTURES

    int index = addressBook->contactCount;
    strcpy(addressBook->contacts[index].name,Name);
    strcpy(addressBook->contacts[index].phone,number);
    strcpy(addressBook->contacts[index].email,mail);

    addressBook->contactCount++;
     
}

void searchContact(AddressBook *addressBook)
{
        void byName(AddressBook*);
        void byPhone(AddressBook*);
        void byEmail(AddressBook*);
        int choice;
        do
        {
            printf("\nSearch Contacts:\n");
            printf("1. By Name\n");
            printf("2. By Number\n");
            printf("3. By Email\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");
            
            if((scanf("%d",&choice)) != 1)
            {
                while(getchar() != '\n');       // CONDITION USED FOR CLEARING THE BUFFER TO HANDLE INVALID INPUT(LIKE STRINGS)
                choice = -1;
            }
            else
            {
                while(getchar() != '\n');       // CONSUME LEFTOVER NEWLINE
            }
       

            switch (choice)                     // SWITCH CASE FOR SEARCHING CONTACT OPTIONS
            {
            case 1:
                byName(addressBook);
                break;
            case 2:
                byPhone(addressBook);
                break;
            case 3:
                byEmail(addressBook);
                break;
            case 4:
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
            }
        } while (choice != 4);

        
}

void editContact(AddressBook *addressBook)
{
    searchContact(addressBook);                     //FOR EDITING THE CONTACT SEARCH THE THAT CONTACT TO KNOW ID NUMBER

    void editName(AddressBook*);
    void editPhone(AddressBook*);
    void editEmail(AddressBook*);
    int choice;
    do
    {
            printf("\nEdit Contact:\n");
            printf("1. Edit Name\n");
            printf("2. Edit Number\n");
            printf("3. Edit Email\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");
            
            if((scanf("%d",&choice)) != 1)          // HANDLES INVALID INPUT LIKE STRINGS
            {
                while(getchar() != '\n');
                choice = -1;
            }
            else
            {
                while(getchar() != '\n');           // CONSUME LEFTOVER NEWLINE
            }

            switch (choice)                        // SWITCH CASE FOR CHOOSING EDIT OPTIONS
            {
            case 1:
                editName(addressBook);
                break;
            case 2:
                editPhone(addressBook);
                break;
            case 3:
                editEmail(addressBook);
                break;
            case 4:
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
            }
        } while(choice != 4);
    
}

void deleteContact(AddressBook *addressBook)
{
    searchContact(addressBook);
    int start;
    printf("Enter ID number to delete : ");

    if((scanf("%d",&start)) != 1)               // CONDITION USED FOR CLEARING THE BUFFER TO HANDLE INVALID INPUT(LIKE STRINGS)
            {
                while(getchar() != '\n');       // CLEAR BUFFER
                start = -1;
            }
            else
            {
                while(getchar() != '\n');       // CONSUME LEFTOVER NEWLINE
            }
    if(start >= addressBook->contactCount || start <0)
    {
        printf("ERROR : Enter valid ID");
        return ;
    }
    for(int i=start;i<addressBook->contactCount;i++)        // SHIFT ELEMENTS LEFT TO DELETE CONTACT
    {
        addressBook->contacts[start] = addressBook->contacts[start+1];
    }
    addressBook->contactCount--;                // REDUCE CONTACT COUNT
    printf("\nCONTACT DELETED SUCCESSFULLY...!\n");

}




//---------------------------------------VALIDATION PART----------------------------------------------------------


int valid_name(char* Name)
{
        int flag = 1;                           // FLAG TO CHECK NAME IS VALID
        printf("Enter the user name :   ");
        scanf("%[^\n]",Name);
        getchar();                              // CLEAR LEFTOVER NEWLINE FROM INPUT BUFFER
        int i=0;
        while(Name[i] != '\0')
        {
            //CHECK IF CHARACTER IS UPPERCASE LETTER OR IF CHARACTER IS LOWERCASE LETTER OR IF CHARACTER IS SPACE AND ENSURE NAME DOESN’T START WITH SPACE
            if((Name[i] >= 65 && Name[i] <= 90 || Name[i] >= 97 && Name[i] <= 122 || Name[i] == ' ')&& Name[0] != ' ')
            {
                i++;
            }
            else
            {
                flag = 0;                       // INVALID CHARACTER → FLAG SET TO 0
                printf("\nError : Enter valid name\n");
                return flag;                    // EXIT FUNCTION IMMEDIATELY
            }
        }
        return flag;                            // RETURN 1 IF VALID, 0 IF INVALID
}

int valid_phone(char* number,AddressBook* addressBook)
{
        int flag = 1;                           // FLAG TO CHECK IF PHONE NUMBER IS VALID
        printf("Enter 10 digit number : ");
        scanf("%s",number);
        getchar();                              // CLEAR LEFTOVER NEWLINE FROM INPUT BUFFER
        int i = 0;
        while(number[i] >= '0' && number[i] <= '9')     // LOOP WHILE CURRENT CHARACTER IS A DIGIT
        {
            i++;
        }
        if(i == 10)                             // CHECK IF EXACTLY 10 DIGITS WERE ENTERED
        {
            for(int i=0; i<addressBook->contactCount; i++)
            {
                int res= strcmp(addressBook->contacts[i].phone,number);         // COMPARE ENTERED NUMBER WITH EACH STORED NUMBER
                if(res==0)                                                      // IF MATCH FOUND THEN DUPLICATE NUMBER
                {
                    printf("\nError : Enter unique number\n\n");
                    flag = 0;                                                   // SET FLAG TO INVALID
                    return flag;
                }
            }
        }
        else
        {
            printf("\nError : Number should be 10 digits\n\n");
            flag = 0;                                                           // SET FLAG TO INVALID
            return flag;
        }
        return flag;                                                            // RETURN 1 IF VALID, 0 IF INVALID

}

int valid_mail(char* mail,AddressBook* addressBook)
{
        int flag =1;                                    // FLAG TO CHECK IF EMAIL IS VALID
        printf("Enter valid email :     ");
        scanf("%s",mail);
        getchar();                                      // CLEAR INPUT BUFFER
        int i=0,countat = 0,countdot=0;
        while(mail[i] != '\0')
        {
            // CHECK VALID CHARACTERS (LOWERCASE, '.' OR '@')
            if((mail[0] != '@' && mail[i] >= 97 && mail[i] <= 122 && mail[0] != '.') || (mail[i] == '.' || mail[i] == '@') )
            {
                i++;
                if(mail[i] == '@' )                     // COUNT HOW MANY '@' USED
                    countat++;
                if(mail[i] == '.')                      // COUNT HOW MANY '.' USED
                    countdot++;
            }
            else                                        // INVALID CHARACTER CASE
            {
                flag = 0;                               // SET FLAG TO INVALID
                if(mail[0] == '@')                      // ERROR IF '@' AT START
                {
                    printf("\n@ Should not be used first\n\n");
                }
                else if(mail[0] == '.')                 // ERROR IF '.' AT START
                {
                    printf("\n. Should not be used first\n\n");
                }
                else                                    // ERROR IF UPPERCASE OR INVALID SYMBOL
                {
                    printf("\nLetters Sholud be lowercase\n\n");
                }
                break;
            }
        }
        if(countat > 1 || countat < 1)                  // '@' MUST BE USED EXACTLY ONCE
        {
            flag = 0;
            printf("\nError : @ Should be used once\n");
        }
        if(countdot > 1)                                // '.' SHOULD NOT BE USED MORE THAN ONCE
        {
            flag = 0;
            printf("\nError : . Should be used once\n");
        }
        
        int len = strlen(mail);                         // GET LENGTH OF EMAIL
        int com = strcmp(mail+(len-4),".com");          
        if(com != 0)                                    // CHECK IF EMAIL ENDS WITH ".com"
        {
            flag =0;
            printf("\nError : '.com' should used at last\n\n");
        }
        char* dot = strchr(mail,'@');                   // FIND POSITION OF '@'
        int loc = ((mail+(len-4)) - dot);               // DISTANCE BETWEEN '@' AND ".com"
        if(loc == 1)                                    // CHECK IF DOMAIN NAME EXISTS
        {
            flag = 0;
            printf("\nError : Enter Domain name\n\n");
        }

        for(int i=0; i<addressBook->contactCount; i++)
            {
                int res = strcmp(addressBook->contacts[i].email,mail);          // CHECK FOR DUPLICATE EMAILS IN ADDRESS BOOK
                if(res==0)
                {
                    printf("\nError : Enter unique mail\n\n");
                    flag = 0;
                    return flag;                        // EXIT IF DUPLICATE FOUND
                }
            }

        return flag;                                    // RETURN 1 IF VALID, 0 IF INVALID
}


// --------------------SORTING FUNCTIONS---------------------------------------


void sortname(AddressBook* addressBook)                 //SORT BY NAME
{
    for(int i=0; i<addressBook->contactCount-1; i++)    // OUTER LOOP FOR BUBBLE SORT
    {
        for(int j=0; j<addressBook->contactCount - i - 1; j++)      // INNER LOOP FOR COMPARING CONTACTS 
        {
            if(strcmp (addressBook->contacts[j].name , addressBook->contacts[j+1].name) > 0)        // COMPARE TWO NAMES IF NAME[j] > NAME[j+1], SWAP
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }

    printf("\nAFTER SORTING BY NAME - \n\n");
    printf("%-5s %-25s %-15s %-30s\n","Sr.", "NAME", "PHONE", "EMAIL");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)                 // LOOP TO DISPLAY ALL CONTACTS
        {
            printf("%-5d %-25s %-15s %-30s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }
}
void sortphone(AddressBook* addressBook)                            //SORT BY NUMBER
{
    for(int i=0; i<addressBook->contactCount-1; i++)                // OUTER LOOP FOR BUBBLE SORT
    {
        for(int j=0; j<addressBook->contactCount - i - 1; j++)      // INNER LOOP FOR COMPARING CONTACTS 
        {
            if(strcmp (addressBook->contacts[j].phone , addressBook->contacts[j+1].phone) > 0)      // COMPARE TWO PHONES NUMBERS IF PHONE[j] > PHONE[j+1], SWAP
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    printf("\nAFTER SORTING BY PHONE NUMBER - \n\n");
    printf("%-5s %-25s %-15s %-30s\n","Sr.", "NAME", "PHONE", "EMAIL");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)             // LOOP TO DISPLAY ALL CONTACTS
        {
            printf("%-5d %-25s %-15s %-30s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }
}
void sortemail(AddressBook* addressBook)                            //SORT BY EMAIL
{
    for(int i=0; i<addressBook->contactCount-1; i++)                // OUTER LOOP FOR BUBBLE SORT
    {
        for(int j=0; j<addressBook->contactCount - i - 1; j++)      // INNER LOOP FOR COMPARING CONTACTS 
        {
            if(strcmp (addressBook->contacts[j].email , addressBook->contacts[j+1].email) > 0)           // COMPARE TWO EMAILS IF EMAIL[j] > EMAIL[j+1], SWAP
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    printf("\nAFTER SORTING BY EMAIL ID - \n\n");
    printf("%-5s %-25s %-15s %-30s\n","Sr.", "NAME", "PHONE", "EMAIL");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)             // LOOP TO DISPLAY ALL CONTACTS
        {
            printf("%-5d %-25s %-15s %-30s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }
}

void displayall(AddressBook* addressBook)                           // DISPLAY ALL CONTACTS
{
    printf("\nALL CONTACTS - \n\n");
    printf("%-5s %-25s %-15s %-30s\n","Sr.", "NAME", "PHONE", "EMAIL");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++) 
        {
            printf("%-5d %-25s %-15s %-30s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }

}



//----------------------------------SEARCHING FUNCTIONS----------------------------------------------------


void byName(AddressBook* addressBook)
{
    char name[30];                                       // VARIABLE TO STORE NAME TO SEARCH
    printf("Enter name to search : ");
    scanf("%[^\n]",name);
    int flag = 1, print = 0;                               // FLAG = CHECK IF FOUND, PRINT = TO PRINT HEADER

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp (addressBook->contacts[i].name,name) == 0)     //COMPARE TO CHECK NAME FOUND IN CONTACT BOOK
        print = 1;                                              //SET 1 IF MATCH FOUND 

    }
    if(print)                                                   //PRINT HEADER IF MATCH FOUND
    {
        printf("\nSEARCHED CONTCACT - \n\n");
        printf("%-5s %-25s %-15s %-30s\n","ID.","NAME","PHONE","EMAIL");
        printf("-------------------------------------------------------------------------------\n");
    }
    for(int i=0; i<addressBook->contactCount; i++)                  // LOOP THROUGH ALL CONTACTS
    {
        if(strcmp(addressBook->contacts[i].name,name) == 0)         //COMPARE TO CHECK NAME FOUND IN CONTACT BOOK
        {
            flag = 0;
            printf("%-5d %-25s %-15s %-30s\n",
                i,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }
    }
    if(flag)                                                        //IF MATCH NO FOUND PRINT ERROR
    {
        printf("\nNO MATCH FOUND ENTER RIGHT NAME...!\n");
    }
    
}
void byPhone(AddressBook* addressBook)
{
    char number[30];                                    // VARIABLE TO STORE NUMBER TO SEARCH
    int flag = 1,print=0;                               // FLAG = CHECK IF FOUND, PRINT = PRINT = TO PRINT HEADER
    scanf("%[^\n]",number);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,number) == 0)       //COMPARE TO CHECK EMAIL FOUND IN CONTACT BOOK
        print = 1;                                                   //SET 1 IF MATCH FOUND

    }
    if(print)                                                       //PRINT HEADER IF MATCH FOUND
    {
        printf("\nSEARCHED CONTCACT - \n\n");
        printf("%-5s %-25s %-15s %-30s\n","ID.","NAME","PHONE","EMAIL");
        printf("-------------------------------------------------------------------------------\n");
    }
    

    for(int i=0; i<addressBook->contactCount; i++)                   // LOOP THROUGH ALL CONTACTS
    {
        if(strcmp(addressBook->contacts[i].phone,number) == 0)      //COMPARE TO CHECK NUMBER FOUND IN CONTACT BOOK
        {
            flag = 0;
            printf("%-5d %-25s %-15s %-30s\n",
                i,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }
    }
    if(flag)
    {
        printf("\nNO MATCH FOUND ENTER RIGHT NUMBER...!\n");          //IF MATCH NO FOUND PRINT ERROR
    }
}
void byEmail(AddressBook* addressBook)
{
    char mail[30];                                                    // VARIABLE TO STORE EMAIL TO SEARCH
    int flag = 1,print = 0;                                           // FLAG = CHECK IF FOUND, PRINT = TO PRINT HEADER
    printf("Enter email to search :");
    scanf("%[^\n]",mail);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,mail) == 0)          //COMPARE TO CHECK EMAIL FOUND IN CONTACT BOOK
        print = 1;                                                    //SET 1 IF MATCH FOUND

    }
    if(print)                                                         //PRINT HEADER IF MATCH FOUND
    {
        printf("\nSEARCHED CONTCACT - \n\n");
        printf("%-5s %-25s %-15s %-30s\n","ID.","NAME","PHONE","EMAIL");
        printf("-------------------------------------------------------------------------------\n");
    }
    for(int i=0; i<addressBook->contactCount; i++)                    // LOOP THROUGH ALL CONTACTS
    {
        if(strcmp(addressBook->contacts[i].email,mail) == 0)          //COMPARE TO CHECK EMAIL FOUND IN CONTACT BOOK
        {
            flag = 0;
            printf("%-5d %-25s %-15s %-30s\n",
                i,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }
    }
    if(flag)                                                                
    {
        printf("\nNO MATCH FOUND ENTER RIGHT EMAIL...!\n");           //IF MATCH NO FOUND PRINT ERROR
    }
}


// ------------------------EDIT FUNCTIONS----------------------------------
void editName(AddressBook* addressBook)
{
    int flag,i;                                // FLAG FOR VALIDATION, i FOR ID NUMBER
    char name[30];                             // VARIABLE TO STORE NEW NAME
    do
    {
        flag = valid_name(name);               // CALL VALID NAME FUNCTION TO VALIDATE NAME
    } while (!flag);
    do
    {
        printf("Enter the ID number : ");
        if((scanf("%d",&i)) != 1)               // CONDITION USED FOR CLEARING THE BUFFER TO HANDLE INVALID INPUT(LIKE STRINGS)
            {
                while(getchar() != '\n');       // CLEAR BUFFER
                i = -1;                         // SET i TO INVALID
            }
            else
            {
                while(getchar() != '\n');       //CLEAR LEFTOVER NEWLINE
            }
       
        if(i>=addressBook->contactCount || i<0 )        // CHECK IF ID IS VALID
        {
            printf("\nERROR : Enter valid ID number\n\n");  
        }
        else
        {
            strcpy(addressBook->contacts[i].name,name);         // COPY NEW NAME INTO CONTACT
            printf("\nUPDATED NAME IN CONTACTS....!\n");        
        }
    }while(i>=addressBook->contactCount || i<0);                // REPEAT UNTIL VALID ID ENTERED
   
}
void editPhone(AddressBook* addressBook)
{
    int flag,i;                                  // FLAG FOR VALIDATION, i FOR ID NUMBER
    char phone[30];                              // VARIABLE TO STORE NEW NUMBER
    do
    {
        flag = valid_phone(phone,addressBook);  // CALL VALID PHONE FUNCTION TO VALIDATE NAME
    } while (!flag);
    do
    {
        printf("Enter the ID number : ");
        if((scanf("%d",&i)) != 1)               // CONDITION USED FOR CLEARING THE BUFFER TO HANDLE INVALID INPUT(LIKE STRINGS)
            {
                while(getchar() != '\n');       // CLEAR BUFFER
                i = -1;                         //SET i TO INVALID
            }
            else
            {
                while(getchar() != '\n');
            }
       
        if(i>=addressBook->contactCount || i<0 )    // CHECK IF ID IS VALID
        {
            printf("\nERROR : Enter valid ID number\n\n");  
        }
        else
        {
            strcpy(addressBook->contacts[i].phone,phone);    // COPY NEW NUMBER INTO CONTACT
            printf("\nUPDATED NAME IN CONTACTS....!\n");
        }
    }while(i>=addressBook->contactCount || i<0);            // REPEAT UNTIL VALID ID ENTERED
}

void editEmail(AddressBook* addressBook)
{
    int flag,i;                                // FLAG FOR VALIDATION, i FOR ID NUMBER
    char mail[30];                             // VARIABLE TO STORE NEW MAIL
    do
    {
        flag = valid_mail(mail,addressBook);    // CALL VALID MAIL FUNCTION TO VALIDATE NAME
    } while (!flag);
    do
    {
        printf("Enter the ID number : ");
        if((scanf("%d",&i)) != 1)               // CONDITION USED FOR CLEARING THE BUFFER TO HANDLE INVALID INPUT(LIKE STRINGS)
            {
                while(getchar() != '\n');      // CLEAR BUFFER
                i = -1;                        //SET i TO INVALID
            }
            else
            {
                while(getchar() != '\n');
            }
       
        if(i>=addressBook->contactCount || i<0 )    // CHECK IF ID IS VALID
        {
            printf("\nERROR : Enter valid ID number\n\n");  
        }
        else
        {
            strcpy(addressBook->contacts[i].email,mail);     // COPY NEW MAIL INTO CONTACT
            printf("\nUPDATED NAME IN CONTACTS....!\n");
        }
    }while(i>=addressBook->contactCount || i<0);             // REPEAT UNTIL VALID ID ENTERED
}