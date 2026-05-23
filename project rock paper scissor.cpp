/*
    ROCK PAPER SCISSORS - SEMESTER PROJECT
    C90 Compliant for Dev-C++
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

/* ==========================================
   GLOBAL VARIABLES & STRUCTURES
   ========================================== */

#define MAX_USERS 100
#define MAX_HISTORY 500

struct User {
    char username[30];
    char password[30];
    int score;
    int isAdmin;
};

struct GameLog {
    char playerName[30];
    char opponentName[30];
    char playerMove[10];
    char compMove[10];
    char result[10];
    int pointsEarned;
};

/* Global Arrays */
struct User users[MAX_USERS];
struct GameLog history[MAX_HISTORY];
int userCount = 0;
int historyCount = 0;
int currentUserIndex = -1;

/* ==========================================
   FUNCTION PROTOTYPES
   ========================================== */

void clearScreen(void);
void mainMenu(void);
void login(void);
void registerUser(void);
void gameDashboard(void);
void playGame(int mode);
void showHistory(void);
void showLeaderboard(void);
void crudMenu(void);
void saveDataToFile(void);
void loadDataFromFile(void);

/* ==========================================
   MODULE 1: MENU SYSTEM
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
        login();
    } else if (choice == 2) {
        registerUser();
    } else if (choice == 3) {
        saveDataToFile();
        printf("Thanks for playing!\n");
        exit(0);
    } else {
        printf("Invalid choice!\n");
        getch();
        mainMenu();
    }
}

void gameDashboard(void) {
    int choice;
    
    clearScreen();
    printf("=================================\n");
    printf("   WELCOME, %s (Score: %d)\n", users[currentUserIndex].username, users[currentUserIndex].score);
    printf("=================================\n");
    printf("1. Play Single Player (vs Computer)\n");
    printf("2. Play Multiplayer (vs Player)\n");
    printf("3. View History\n");
    printf("4. View Leaderboard\n");
    printf("5. CRUD Operations (Admin Only)\n");
    printf("6. Logout\n");
    printf("=================================\n");
    printf("Enter choice: ");

    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        playGame(1);
    } else if (choice == 2) {
        playGame(2);
    } else if (choice == 3) {
        showHistory();
    } else if (choice == 4) {
        showLeaderboard();
    } else if (choice == 5) {
        crudMenu();
    } else if (choice == 6) {
        currentUserIndex = -1;
        mainMenu();
    } else {
        printf("Invalid choice!");
        getch();
        gameDashboard();
    }
}

/* ==========================================
   MODULE 2: LOGIN / REGISTER
   ========================================== */

void registerUser(void) {
    clearScreen();
    printf("--- Register New User ---\n");
    
    if (userCount >= MAX_USERS) {
        printf("Database full!\n");
        getch();
        mainMenu();
        return;
    }

    printf("Enter username (max 29 chars): ");
    scanf("%29s", users[userCount].username);
    printf("Enter password (max 29 chars): ");
    scanf("%29s", users[userCount].password);
    
    if (userCount == 0) {
        users[userCount].isAdmin = 1;
        printf("You are registered as ADMIN.\n");
    } else {
        users[userCount].isAdmin = 0;
        printf("You are registered as PLAYER.\n");
    }
    
    users[userCount].score = 0;
    userCount++;

    printf("Registration Successful! Press any key...");
    getch();
    mainMenu();
}

void login(void) {
    char u[30];
    char p[30];
    int found;
    int i;
    
    clearScreen();
    printf("--- Login ---\n");
    printf("Username: ");
    scanf("%29s", u);
    printf("Password: ");
    scanf("%29s", p);

    found = 0;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, u) == 0 && strcmp(users[i].password, p) == 0) {
            found = 1;
            currentUserIndex = i;
            break;
        }
    }
    
    if (found == 1) {
        printf("Login Successful! Press any key...");
        getch();
        gameDashboard();
    } else {
        printf("Invalid credentials!\n");
        getch();
        mainMenu();
    }
}

/* ==========================================
   MODULE 3: GAMEPLAY
   ========================================== */

void playGame(int mode) {
    char opponentName[30];
    int opponentIndex;
    int playerMove;
    int opponentMove;
    char playerMoveStr[10];
    char compMoveStr[10];
    int result;
    char resultStr[10];
    int points;
    char pName[30];
    char oName[30];
    int i;
    
    clearScreen();
    strcpy(opponentName, "Computer");
    opponentIndex = -1;
    
    if (mode == 2) {
        printf("--- MULTIPLAYER MODE ---\n");
        printf("Enter opponent's username: ");
        scanf("%29s", opponentName);
        
        opponentIndex = -1;
        for (i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, opponentName) == 0) {
                opponentIndex = i;
                break;
            }
        }
        
        if (opponentIndex == -1) {
            printf("Opponent not found!\n");
            getch();
            gameDashboard();
            return;
        }
        
        if (opponentIndex == currentUserIndex) {
            printf("You cannot play against yourself!\n");
            getch();
            gameDashboard();
            return;
        }
        
        printf("Playing against %s!\n", opponentName);
        getch();
    }

    clearScreen();
    printf("--- GAME START ---\n");
    printf("Choose your move:\n");
    printf("1. Rock\n");
    printf("2. Paper\n");
    printf("3. Scissors\n");
    
    scanf("%d", &playerMove);
    
    if (mode == 1) {
        opponentMove = (rand() % 3) + 1;
    } else {
        printf("\nPass device to opponent...\n");
        printf("Press any key...");
        getch();
        
        clearScreen();
        printf("Opponent %s, choose your move:\n", opponentName);
        printf("1. Rock\n");
        printf("2. Paper\n");
        printf("3. Scissors\n");
        scanf("%d", &opponentMove);
    }
    
    if (playerMove < 1 || playerMove > 3 || opponentMove < 1 || opponentMove > 3) {
        printf("Invalid move!\n");
        getch();
        gameDashboard();
        return;
    }

    if (playerMove == 1) strcpy(playerMoveStr, "Rock");
    else if (playerMove == 2) strcpy(playerMoveStr, "Paper");
    else strcpy(playerMoveStr, "Scissors");
    
    if (opponentMove == 1) strcpy(compMoveStr, "Rock");
    else if (opponentMove == 2) strcpy(compMoveStr, "Paper");
    else strcpy(compMoveStr, "Scissors");

    result = 0;
    
    if (playerMove == opponentMove) {
        result = 0;
    } else if ((playerMove == 1 && opponentMove == 3) || 
               (playerMove == 2 && opponentMove == 1) || 
               (playerMove == 3 && opponentMove == 2)) {
        result = 1;
    } else {
        result = -1;
    }

    strcpy(pName, users[currentUserIndex].username);
    strcpy(oName, (mode == 1) ? "Computer" : opponentName);
    
    if (result == 1) {
        strcpy(resultStr, "WIN");
        points = 10;
        users[currentUserIndex].score += 10;
    } else if (result == -1) {
        strcpy(resultStr, "LOSE");
        points = -5;
        users[currentUserIndex].score -= 5;
    } else {
        strcpy(resultStr, "DRAW");
        points = 2;
        users[currentUserIndex].score += 2;
    }

    if (mode == 2 && opponentIndex != -1) {
        if (result == 1) {
            users[opponentIndex].score -= 5;
        } else if (result == -1) {
            users[opponentIndex].score += 10;
        } else {
            users[opponentIndex].score += 2;
        }
    }

    if (historyCount < MAX_HISTORY) {
        strcpy(history[historyCount].playerName, pName);
        strcpy(history[historyCount].opponentName, oName);
        strcpy(history[historyCount].playerMove, playerMoveStr);
        strcpy(history[historyCount].compMove, compMoveStr);
        strcpy(history[historyCount].result, resultStr);
        history[historyCount].pointsEarned = points;
        historyCount++;
    }

    clearScreen();
    printf("--- RESULT ---\n");
    printf("Player: %s chose %s\n", pName, playerMoveStr);
    printf("Opponent: %s chose %s\n", oName, compMoveStr);
    printf("Result: %s\n", resultStr);
    printf("Points: %d\n", points);
    printf("Your New Score: %d\n", users[currentUserIndex].score);
    
    if (mode == 2 && opponentIndex != -1) {
        printf("Opponent New Score: %d\n", users[opponentIndex].score);
    }
    
    printf("\nPress any key to continue...");
    getch();
    gameDashboard();
}

/* ==========================================
   MODULE 7: HISTORY
   ========================================== */

void showHistory(void) {
    int found;
    int i;
    
    clearScreen();
    printf("--- GAME HISTORY ---\n");
    printf("%-15s %-15s %-10s %-10s %s\n", "Player", "Opponent", "P_Move", "O_Move", "Result");
    printf("---------------------------------------------------------------------------------\n");
    
    found = 0;
    for (i = 0; i < historyCount; i++) {
        if (strcmp(history[i].playerName, users[currentUserIndex].username) == 0) {
            printf("%-15s %-15s %-10s %-10s %s\n", 
                history[i].playerName, 
                history[i].opponentName,
                history[i].playerMove, 
                history[i].compMove, 
                history[i].result);
            found = 1;
        }
    }
    
    if (found == 0) {
        printf("No history found!\n");
    }
    
    printf("\nPress any key to continue...");
    getch();
    gameDashboard();
}

/* ==========================================
   MODULE 5: LEADERBOARD
   ========================================== */

void showLeaderboard(void) {
    struct User sortedUsers[MAX_USERS];
    struct User temp;
    int i, j;
    
    clearScreen();
    printf("--- LEADERBOARD ---\n");
    printf("%-20s %s\n", "Username", "Score");
    printf("--------------------------\n");
    
    for (i = 0; i < userCount; i++) {
        sortedUsers[i] = users[i];
    }
    
    for (i = 0; i < userCount - 1; i++) {
        for (j = 0; j < userCount - i - 1; j++) {
            if (sortedUsers[j].score < sortedUsers[j+1].score) {
                temp = sortedUsers[j];
                sortedUsers[j] = sortedUsers[j+1];
                sortedUsers[j+1] = temp;
            }
        }
    }
    
    for (i = 0; i < userCount; i++) {
        printf("%-20s %d\n", sortedUsers[i].username, sortedUsers[i].score);
    }
    
    printf("\nPress any key to continue...");
    getch();
    gameDashboard();
}

/* ==========================================
   MODULE 6: CRUD (Admin Only)
   ========================================== */

void crudMenu(void) {
    int choice;
    int delId;
    int i;
    
    if (users[currentUserIndex].isAdmin != 1) {
        printf("Access denied! Admin only.\n");
        getch();
        gameDashboard();
        return;
    }

    clearScreen();
    printf("--- CRUD OPERATIONS (Admin) ---\n");
    printf("1. View All Users\n");
    printf("2. Delete User\n");
    printf("3. Reset Scores\n");
    printf("4. Back\n");
    printf("Enter choice: ");
    
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        clearScreen();
        printf("--- ALL USERS ---\n");
        for (i = 0; i < userCount; i++) {
            printf("ID: %d | User: %s | Score: %d | Admin: %s\n", 
                i, users[i].username, users[i].score, 
                users[i].isAdmin ? "Yes" : "No");
        }
        printf("\nPress any key...");
        getch();
        crudMenu();
    } else if (choice == 2) {
        printf("Enter user ID to delete: ");
        scanf("%d", &delId);
        getchar();
        
        if (delId >= 0 && delId < userCount && delId != currentUserIndex) {
            for (i = delId; i < userCount - 1; i++) {
                users[i] = users[i+1];
            }
            userCount--;
            printf("User deleted!\n");
        } else {
            printf("Invalid ID!\n");
        }
        getch();
        crudMenu();
    } else if (choice == 3) {
        for (i = 0; i < userCount; i++) {
            users[i].score = 0;
        }
        printf("All scores reset!\n");
        getch();
        crudMenu();
    } else {
        gameDashboard();
    }
}

/* ==========================================
   MODULE 4: FILE HANDLING
   ========================================== */

void saveDataToFile(void) {
    FILE *fpUser;
    FILE *fpHist;
    int i;
    
    fpUser = fopen("users.txt", "w");
    if (fpUser == NULL) return;
    
    for (i = 0; i < userCount; i++) {
        fprintf(fpUser, "%s %s %d %d\n", 
            users[i].username, users[i].password, 
            users[i].score, users[i].isAdmin);
    }
    fclose(fpUser);

    fpHist = fopen("history.txt", "w");
    if (fpHist == NULL) return;
    
    for (i = 0; i < historyCount; i++) {
        fprintf(fpHist, "%s %s %s %s %s %d\n", 
            history[i].playerName, history[i].opponentName,
            history[i].playerMove, history[i].compMove, 
            history[i].result, history[i].pointsEarned);
    }
    fclose(fpHist);
}

void loadDataFromFile(void) {
    FILE *fpUser;
    FILE *fpHist;
    int check;
    
    fpUser = fopen("users.txt", "r");
    if (fpUser != NULL) {
        while (userCount < MAX_USERS) {
            check = fscanf(fpUser, "%s %s %d %d", 
                users[userCount].username, 
                users[userCount].password, 
                &users[userCount].score, 
                &users[userCount].isAdmin);
            if (check != 4) break;
            userCount++;
        }
        fclose(fpUser);
    }

    fpHist = fopen("history.txt", "r");
    if (fpHist != NULL) {
        while (historyCount < MAX_HISTORY) {
            check = fscanf(fpHist, "%s %s %s %s %s %d", 
                history[historyCount].playerName, 
                history[historyCount].opponentName,
                history[historyCount].playerMove, 
                history[historyCount].compMove, 
                history[historyCount].result, 
                &history[historyCount].pointsEarned);
            if (check != 6) break;
            historyCount++;
        }
        fclose(fpHist);
    }
}

/* ==========================================
   MAIN FUNCTION
   ========================================== */

int main(void) {
    srand(time(0));
    loadDataFromFile();
    mainMenu();
    return 0;
}
