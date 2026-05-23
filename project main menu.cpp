/*
    ROCK PAPER SCISSORS - SEMESTER PROJECT
    Part 1: Main Menu Only
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* ==========================================
   FUNCTION PROTOTYPES
   ========================================== */

void clearScreen(void);
void mainMenu(void);

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

void clearScreen(void) {
    system("cls");
}

void mainMenu(void) {
    int choice;
    
    clearScreen();
    printf("=================================\n");
    printf("   ROCK PAPER SCISSORS - MAIN MENU\n");
    printf("=================================\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("=================================\n");
    printf("Enter choice: ");

    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        /* TODO: Add login() */
        printf("\n[Login module - coming soon]");
        getch();
    } else if (choice == 2) {
        /* TODO: Add registerUser() */
        printf("\n[Register module - coming soon]");
        getch();
    } else if (choice == 3) {
        /* TODO: Add saveDataToFile() before exit */
        printf("Thanks for playing!\n");
        exit(0);
    } else {
        printf("Invalid choice!\n");
        getch();
    }
    
    /* Loop back to menu */
    mainMenu();
}

/* ==========================================
   MAIN FUNCTION
   ========================================== */

int main(void) {
    mainMenu();
    return 0;
}
