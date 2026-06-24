/*
    ROCK PAPER SCISSORS - SEMESTER PROJECT
    Part 1: Main Menu Only + login + register + Gameplay + file handling
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
void loadData(void);
void clearScreen(void);
void mainMenu(void);
void login(void);
void registerUser(void);
int findUser(char *username);
void addHistory(int idx, char *result);
void viewLeaderboard(void);
void saveData(void);

void gameDashboard(void);
void playSinglePlayer(void);
void playMultiplayer(void);

void profileMenu(void);
void updateProfile(void);
void deleteAccount(void);
void viewHistory(void);
void viewLeaderboard(void);
int readInt(void);
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
void addHistory(int idx, char *result) {
    char temp[MAX_HISTORY_LEN + 100];
    sprintf(temp, "%s | %s", result, users[idx].history);
    strncpy(users[idx].history, temp, MAX_HISTORY_LEN - 1);
    users[idx].history[MAX_HISTORY_LEN - 1] = '\0';
}
void saveData(void) {
    FILE *fp;
    fp = fopen(FILE_NAME, "wb");
    if (fp != NULL) {
        fwrite(&userCount, sizeof(int), 1, fp);
        fwrite(users, sizeof(User), userCount, fp);
        fclose(fp);
    }
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
    scanf("%49s", newUser);
    getchar();

    if (findUser(newUser) != -1) {
        printf("\nERROR: Username already exists!\n");
        getchar();
        return;
    }

    printf("Password: ");
    scanf("%49s", newPass);
    getchar();

    printf("Confirm Password: ");
    scanf("%49s", confirmPass);
    getchar();

    if (strcmp(newPass, confirmPass) != 0) {
        printf("\nERROR: Passwords do not match!\n");
        getchar();
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
    getchar();
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
    scanf("%49s", inputUser);
    
    printf("Password: ");
    scanf("%49s", inputPass);
    getchar();

    int idx = findUser(inputUser);

    if (idx == -1) {
        printf("\nERROR: Username not found!\n");
        getchar();
        return;
    }

    if (strcmp(users[idx].password, inputPass) != 0) {
        printf("\nERROR: Incorrect password!\n");
        getchar();
        return;
    }

    currentUserIndex = idx;
    printf("\n>> LOGIN SUCCESSFUL! Welcome, %s!\n", users[idx].username);
    getchar();
}

// ==========================================
//SINGLE PLAYER GAME
//===========================================

void playSinglePlayer(void) {
    int playerChoice, compChoice;
   char *choices[] = {"Rock", "Paper", "Scissors"};
    
 
    srand(time(NULL));

    clearScreen();
    printf("=================================\n");
    printf("       SINGLE PLAYER MODE\n");
    printf("=================================\n");
    printf("1. Rock\n");
    printf("2. Paper\n");
    printf("3. Scissors\n");
    printf("=================================\n");
    
    printf("Enter your choice (1-3): ");
playerChoice = readInt();
    if (playerChoice < 1 || playerChoice > 3) {
        printf("\nInvalid choice! Turn forfeited.\n");
        getchar();
        return;
    }
    compChoice = (rand() % 3) + 1;

    printf("\nYOU chose:     %s\n", choices[playerChoice - 1]);
    printf("COMP chose:    %s\n", choices[compChoice - 1]);

    int result = 0;

    if (playerChoice == compChoice) {
        printf("\n>>> IT'S A DRAW! <<<\n");
        result = 0;
    } else if ((playerChoice == 1 && compChoice == 3) ||
               (playerChoice == 2 && compChoice == 1) ||
               (playerChoice == 3 && compChoice == 2)) {
        printf("\n>>> YOU WIN! <<<\n");
        result = 1;
    } else {
        printf("\n>>> YOU LOSE! <<<\n");
        result = -1;
    }

    if (result == 1) {
        users[currentUserIndex].wins++;
    } else if (result == 0) {
        users[currentUserIndex].draws++;
    } else {
        users[currentUserIndex].losses++;
    }

    char logEntry[100];
    sprintf(logEntry, "Solo: %s vs %s [%c]", 
            choices[playerChoice - 1], 
            choices[compChoice - 1],
            result == 1 ? 'W' : (result == -1 ? 'L' : 'D'));
    
    addHistory(currentUserIndex, logEntry);
    saveData();

    printf("\nPress any key to continue...");
    getchar();
}

// ==========================================
// MULTIPLAYER GAME
// ==========================================
void playMultiplayer(void)
{
    char opponent[MAX_NAME_LEN];
    int playerChoice, player2Choice;
    char *choices[] = {"Rock", "Paper", "Scissors"};
    int opponentIdx;

    clearScreen();
    printf("=================================\n");
    printf("       MULTIPLAYER MODE\n");
    printf("=================================\n");
    printf("Enter opponent username: ");
    scanf("%49s", opponent);
    getchar();

    opponentIdx = findUser(opponent);

    if (opponentIdx == -1) {
        printf("\nERROR: Opponent not found!\n");
        getch();
        return;
    }

    if (opponentIdx == currentUserIndex) {
        printf("\nERROR: Cannot play against yourself!\n");
        getch();
        return;
    }

    clearScreen();
    printf("=================================\n");
    printf("   %s's TURN\n", users[currentUserIndex].username);
    printf("=================================\n");
    printf("1. Rock\n2. Paper\n3. Scissors\n");
    printf("Enter your choice (1-3): ");
  playerChoice = readInt();
    if (playerChoice < 1 || playerChoice > 3) {
        playerChoice = (rand() % 3) + 1;
    }
    clearScreen();
    printf("=================================\n");
    printf("   %s's TURN\n", opponent);
    printf("=================================\n");
    printf("1. Rock\n2. Paper\n3. Scissors\n");
    printf("Enter choice (1-3): ");
  playerChoice = readInt();
    if (player2Choice < 1 || player2Choice > 3) {
        player2Choice = (rand() % 3) + 1;
    }
    clearScreen();
    printf("=================================\n");
    printf("          RESULTS\n");
    printf("=================================\n");
    printf("%s chose:     %s\n", users[currentUserIndex].username, choices[playerChoice - 1]);
    printf("%s chose:    %s\n", opponent, choices[player2Choice - 1]);

    int result = 0;

    if (playerChoice == player2Choice) {
        printf("\n>>> IT'S A DRAW! <<<\n");
        result = 0;
    } else if ((playerChoice == 1 && player2Choice == 3) ||
               (playerChoice == 2 && player2Choice == 1) ||
               (playerChoice == 3 && player2Choice == 2)) {
        printf("\n>>> %s WINS! <<<\n", users[currentUserIndex].username);
        result = 1;
    } else {
        printf("\n>>> %s WINS! <<<\n", opponent);
        result = -1;
    }

    if (result == 1) {
        users[currentUserIndex].wins++;
        users[opponentIdx].losses++;
    } else if (result == -1) {
        users[currentUserIndex].losses++;
        users[opponentIdx].wins++;
    } else {
        users[currentUserIndex].draws++;
        users[opponentIdx].draws++;
    }

    char logEntry1[100], logEntry2[100];
    sprintf(logEntry1, "Dual: %s vs %s [%c]", 
            choices[playerChoice - 1], choices[player2Choice - 1],
            result == 1 ? 'W' : (result == -1 ? 'L' : 'D'));
    sprintf(logEntry2, "Dual: %s vs %s [%c]", 
            choices[player2Choice - 1], choices[playerChoice - 1],
            result == -1 ? 'W' : (result == 1 ? 'L' : 'D'));

    addHistory(currentUserIndex, logEntry1);
    addHistory(opponentIdx, logEntry2);
    saveData();

    printf("\nPress any key to continue...");
    getch();
}

/* ==========================================
   GAME DASHBOARD
   ========================================== */
void gameDashboard(void) {
    int choice;
    while (1) {
        clearScreen();
        printf("=================================\n");
        printf("        GAME DASHBOARD\n");
        printf("=================================\n");
        printf("1. Single Player (vs Computer)\n");
        printf("2. Multiplayer (vs Another User)\n");
        printf("3. Back to Main Menu\n");
        printf("=================================\n");
        printf("Enter choice: ");
        choice = readInt();
        if (choice == 1) {
            playSinglePlayer();
        } else if (choice == 2) {
            playMultiplayer();
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice!\n");
            getch();
        }
    }
}
/* ==========================================
   MAIN MENU
   ========================================== */
void profileMenu(void)
{
    int choice;

    while(1)
    {
        clearScreen();

        printf("=================================\n");
        printf("        PROFILE MENU\n");
        printf("=================================\n");
        printf("1. View Stats\n");
        printf("2. View History\n");
        printf("3. View Leaderboard\n");
        printf("4. Update Password\n");
        printf("5. Delete Account\n");
        printf("6. Back\n");
        printf("=================================\n");
        printf("Enter choice: ");

        choice = readInt();

        switch(choice)
        {
            case 1:
                clearScreen();
                printf("Username: %s\n", users[currentUserIndex].username);
                printf("Wins: %d\n", users[currentUserIndex].wins);
                printf("Losses: %d\n", users[currentUserIndex].losses);
                printf("Draws: %d\n", users[currentUserIndex].draws);
                getch();
                break;

            case 2:
                viewHistory();
                break;

            case 3:
                viewLeaderboard();
                break;

            case 4:
                updateProfile();
                break;

            case 5:
                deleteAccount();
                break;

            case 6:
                return;

            default:
                printf("Invalid choice!\n");
                getch();
        }
    }
}
void mainMenu(void)
 {
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
printf("2. Profile & Stats\n");
printf("3. Logout\n");
printf("4. Exit\n");
        }
        printf("=================================\n");
        printf("Enter choice: ");
        choice = readInt();
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
                getchar();
            }
        }
        
         else
{
    if (choice == 1)
    {
        gameDashboard();
    }
    else if (choice == 2)
    {
        profileMenu();
    }
    else if (choice == 3)
    {
        currentUserIndex = -1;
    }
    else if (choice == 4)
    {
        break;
    }
    else
    {
        printf("Invalid choice!\n");
        getch();
    }
}
    }
}
// ==========================================
// MAIN FUNCTION
// ==========================================

int main(void) {
    loadData();
    mainMenu();
    return 0;
}
int readInt(void)
{
    char line[100];
    int value;

    if(fgets(line,sizeof(line),stdin)==NULL)
        return -1;
   if(sscanf(line,"%d",&value)!=1)
        return -1;

    return value;
}
void loadData(void)
{
    FILE *fp;

    fp = fopen(FILE_NAME, "rb");

    if(fp != NULL)
    {
        fread(&userCount,sizeof(int),1,fp);
        fread(users,sizeof(User),userCount,fp);
        fclose(fp);
    }
}
void updateProfile(void) {
    char newPass[MAX_PASS_LEN], confirmPass[MAX_PASS_LEN];
    printf("Enter new password: ");
    scanf("%s", newPass);
    printf("Confirm password: ");
    scanf("%s", confirmPass);
    
    if (strcmp(newPass, confirmPass) == 0) {
        strcpy(users[currentUserIndex].password, newPass);
        saveData();
        printf("\n>> Password changed!\n");
    } else {
        printf("\n>> Passwords don't match!\n");
    }
    getch();
}void deleteAccount(void) {
    char confirm, inputPass[MAX_PASS_LEN];
    printf("Enter password to confirm: ");
    scanf("%s", inputPass);
    
    if (strcmp(users[currentUserIndex].password, inputPass) != 0) {
        printf("\n>> Wrong password!\n");
        getch();
        return;
    }
    
    printf("Delete account? (y/n): ");
    scanf(" %c",&confirm);
    scanf(" %c", &confirm);
    if (confirm == 'y') {
        int i;
        for (i = currentUserIndex; i < userCount - 1; i++) {
            users[i] = users[i + 1];
        }
        userCount--;
        saveData();
        printf("\n>> Deleted!\n");
        exit(0);
    }
}void viewHistory(void) {
    printf("\nUsername: %s\n", users[currentUserIndex].username);
    printf("Wins: %d | Losses: %d | Draws: %d\n",
           users[currentUserIndex].wins,
           users[currentUserIndex].losses,
           users[currentUserIndex].draws);
    printf("History: %s\n", users[currentUserIndex].history);
    getch();
}
void viewLeaderboard(void)
{
    User sorted[MAX_USERS];
    User swap;
    int i,j;

    for(i=0;i<userCount;i++)
        sorted[i]=users[i];

    for(i=0;i<userCount-1;i++)
    {
        for(j=0;j<userCount-1-i;j++)
        {
            if(sorted[j].wins < sorted[j+1].wins)
            {
                swap=sorted[j];
                sorted[j]=sorted[j+1];
                sorted[j+1]=swap;
            }
        }
    }

    clearScreen();

    printf("=================================\n");
    printf("          LEADERBOARD\n");
    printf("=================================\n");

    printf("%-20s %6s %6s %6s\n",
           "Name","Wins","Loss","Draw");

    for(i=0;i<userCount;i++)
    {
        printf("%-20s %6d %6d %6d\n",
               sorted[i].username,
               sorted[i].wins,
               sorted[i].losses,
               sorted[i].draws);
    }

    getch();
}
