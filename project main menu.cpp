#include <stdio.h>

void registerUser();
void loginUser();

int main()
{
    int choice;

    while(1)
    {
        printf("\nROCK PAPER SCISSORS GAME\n");

        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                printf("Exiting Program...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

void registerUser()
{
    printf("Register system\n");
}

void loginUser()
{
    printf("Login system\n");
}

