#include <stdio.h>
#include <stdlib.h>

// Print the 3x3 board
void print_board(char b[9]) {
    printf("\n");
    printf(" %c | %c | %c\n", b[0], b[1], b[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", b[3], b[4], b[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", b[6], b[7], b[8]);
    printf("\n");
}

// Check winner, draw, or ongoing
char check_result(char b[9]) {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // columns
        {0,4,8}, {2,4,6} // diagonals
    };

    for (int i = 0; i < 8; i++) {
        int a = wins[i][0], c = wins[i][1], d = wins[i][2];
        if (b[a] == b[c] && b[c] == b[d] && b[a] != ' ') {
            return b[a];
        }
    }

    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') return 'N';
    }

    return 'D';
}

// Find a winning or blocking move
int find_winning_move(char b[9], char player) {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // columns
        {0,4,8}, {2,4,6} // diagonals
    };

    for (int i = 0; i < 8; i++) {
        int count = 0, empty = -1;
        for (int j = 0; j < 3; j++) {
            int idx = wins[i][j];
            if (b[idx] == player) count++;
            else if (b[idx] == ' ') empty = idx;
        }
        if (count == 2 && empty != -1) return empty;
    }
    return -1;
}

// Decide computer move
int computer_move(char b[9]) {
    int move = find_winning_move(b, 'O');
    if (move != -1) return move;

    move = find_winning_move(b, 'X');
    if (move != -1) return move;

    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') return i;
    }
    return -1;
}

int main() {
    char b[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char result = 'N';
    int position, scan_result;

    printf("Tic Tac Toe - Human (X) vs Computer (O)\n");
    print_board(b);

    while (result == 'N') {
        // Human move
        printf("Your move (1-9): ");
        scan_result = scanf("%d", &position);

        if (scan_result != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { ; }
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (position < 1 || position > 9) {
            printf("Out of range. Choose 1-9.\n");
            continue;
        }

        if (b[position - 1] != ' ') {
            printf("That spot is already taken!\n");
            continue;
        }

        b[position - 1] = 'X';
        print_board(b);

        result = check_result(b);
        if (result != 'N') break;

        // Computer move
        int comp = computer_move(b);
        if (comp == -1) {
            result = check_result(b);
            break;
        }
        b[comp] = 'O';
        printf("Computer chose position %d\n", comp + 1);
        print_board(b);

        result = check_result(b);
    }

    if (result == 'X') printf("You win!\n");
    else if (result == 'O') printf("Computer wins!\n");
    else printf("It's a draw!\n");

    printf("Game Over.\n");
    return 0;
}
