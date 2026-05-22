#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ----------CONFIGURATION-----------
#define MAX_USERS 100
#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 50
#define MAX_HISTORY_LEN 200
#define FILE_NAME "game_rock.dat"

// -------------------- DATA STRUCTURES --------------------
typedef struct {
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    int wins;
    int losses;
    int draws;
    char history[MAX_HISTORY_LEN];
} User;

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

