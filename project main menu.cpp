 /*
    ROCK PAPER SCISSORS - SEMESTER PROJECT
    Part 1: Main Menu Only + login + register
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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
//------------------GLOBAL VARIABLE-------------
User users[MAX_USERS];
int userCount = 0;
int currentUserIndex = -1;


/* ==========================================
   FUNCTION PROTOTYPES
   ========================================== */

void clearScreen(void);
void mainMenu(void);
void login(void);
void registerUser(void);
int findUser(char *username);
// ==========================================
// HELPER FUNCTIONS
// ==========================================

int findUser(char *username) {
	int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
    
}
void clearScreen(void) {
    system("cls");
}
// ==========================================
// REGISTER FUNCTION
// ==========================================

void registerUser(void) {
    char newUser[MAX_NAME_LEN];
    char newPass[MAX_PASS_LEN];
    char confirmPass[MAX_PASS_LEN];
    FILE *fp;

    clearScreen();
    printf("=================================\n");
    printf("         REGISTER\n");
    printf("=================================\n");
    
    printf("Username: ");
    scanf("%s", newUser);
    getchar();

    if (findUser(newUser) != -1) {
        printf("\nERROR: Username already exists!\n");
        getchar();
        return;
    }

    printf("Password: ");
    scanf("%s", newPass);
    getchar();

    printf("Confirm Password: ");
    scanf("%s", confirmPass);
    getchar();

    if (strcmp(newPass, confirmPass) != 0) {
        printf("\nERROR: Passwords do not match!\n");
        getch();
        return;
    }

    strcpy(users[userCount].username, newUser);
    strcpy(users[userCount].password, newPass);
    users[userCount].wins = 0;
    users[userCount].losses = 0;
    users[userCount].draws = 0;
    strcpy(users[userCount].history, "New User");
    
userCount++;
    
    fp = fopen(FILE_NAME, "wb");
    if (fp != NULL) {
        fwrite(&userCount, sizeof(int), 1, fp);
        fwrite(users, sizeof(User), userCount, fp);
        fclose(fp);
    }
    printf("\n>> Registration Successful!\n");
    getch();
}
// ==========================================
// LOGIN FUNCTION
// ==========================================

void login(void) {
    char inputUser[MAX_NAME_LEN];
    char inputPass[MAX_PASS_LEN];

    clearScreen();
    printf("=================================\n");
    printf("           LOGIN\n");
    printf("=================================\n");
    printf("Username: ");
    scanf("%s", inputUser);
    
    printf("Password: ");
    scanf("%s", inputPass);
    getchar();

    int idx = findUser(inputUser);

    if (idx == -1) {
        printf("\nERROR: Username not found!\n");
        getch();
        return;
    }

    if (strcmp(users[idx].password, inputPass) != 0) {
        printf("\nERROR: Incorrect password!\n");
        getch();
        return;
    }

    currentUserIndex = idx;
    printf("\n>> LOGIN SUCCESSFUL! Welcome, %s!\n", users[idx].username);
    getch();
}



/* Add more prototypes here as we add modules:
void login(void);
void registerUser(void);
void gameDashboard(void);
void playGame(int mode);
void showHistory(void);
void showLeaderboard(void);
void crudMenu(void);
void saveDataToFile(void);
void loadDataFromFile(void);
*/

/* ==========================================
   MAIN MENU
   ========================================== */
   

void mainMenu(void) {
    int choice;
    
     while (1) {
	 clearScreen();
    printf("=================================\n");
    printf("   ROCK PAPER SCISSORS - MAIN MENU\n");
    printf("=================================\n");
    
    if (currentUserIndex == -1) {
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
} else {
 printf("Logged in as: %s\n", users[currentUserIndex].username);
            printf("1. Play Game\n");
            printf("2. Logout\n");
            printf("3. Exit\n");
        }
    printf("=================================\n");
    printf("Enter choice: ");

    scanf("%d", &choice);
    getchar();
    if (currentUserIndex == -1) {
    printf("1. Login\n");
            printf("2. Register\n");
            printf("3. Exit\n");
        } else {
            printf("Logged in as: %s\n", users[currentUserIndex].username);
            printf("1. Play Game\n");
            printf("2. Logout\n");
            printf("3. Exit\n");
        }
printf("=================================\n");
        if (currentUserIndex == -1) {
            if (choice == 1) {
                login();
            } else if (choice == 2) {
            	registerUser();
            } else if (choice == 3) {
                printf("Thanks for playing!\n");
                break;
            } else {
                printf("Invalid choice!\n");
                getch();
            }
            } else {
            if (choice == 1) {
                printf("\n[Game module - coming soon]");
                getch();
            } else if (choice == 2) {
                currentUserIndex = -1;
                printf("Logged out!\n");
                getch();
            } else if (choice == 3) {
            	printf("Thanks for playing!\n");
                break;
            } else {
                printf("Invalid choice!\n");
                getch();
            }
        }
		}
}

/* ==========================================
   MAIN FUNCTION
   ========================================== */

int main(void) {
    mainMenu();
    return 0;
}
