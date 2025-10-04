#include <stdio.h>  
#include <stdlib.h> 

// print the board in a 3x3 layout
void print_board(char b[9]) {
    printf("\n");
    printf(" %c | %c | %c\n", b[0], b[1], b[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", b[3], b[4], b[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", b[6], b[7], b[8]);
    printf("\n");
}

// check the result of the game
char check_result(char b[9]) {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // columns
        {0,4,8}, {2,4,6}           // diagonals
    };

    for (int i = 0; i < 8; i++) {
        int a = wins[i][0], c = wins[i][1], d = wins[i][2];
        if (b[a] == b[c] && b[c] == b[d] && b[a] != ' ') {
            return b[a]; // winner found
        }
    }

    // check if there is still an empty space
    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') {
            return 'N'; //still have to continue
        }
    }
    return 'D'; // draw
}

int main() {
    // Initializing the board
    char b[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char turn = 'X';
    char result = 'N';
    int position;
    int scan_results;

    printf("Tic Tac Toe - Human vs Human\n");
    print_board(b);

    while (result == 'N') {
        printf("Player %c, enter position (1-9): ", turn);
        scan_results = scanf("%d", &position);

        if (scan_results != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { ; }
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (position < 1 || position > 9) {
            printf("Position out of range. Choose 1-9.\n");
            continue;
        }

        if (b[position - 1] != ' ') {
            printf("That spot is already taken!\n");
            continue;
        }

        b[position - 1] = turn;
        print_board(b);

        result = check_result(b);

        if (result == 'X' || result == 'O') {
            printf("Player %c wins!\n", result);
            break;
        } else if (result == 'D') {
            printf("It's a draw!\n");
            break;
        }

        turn = (turn == 'X') ? 'O' : 'X';
    }

    printf("Game Over.\n");
    return 0;
}
