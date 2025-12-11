//
//  main.c
//  TicTacToe
//
//  Created by Aiden Barrett on 12/10/25.
//

#include <stdlib.h>
#include <stdio.h>

int is_player_o_turn(int turn_count);

char get_current_player_icon(int turn_count);

void execute_turn(char board[9], char current_player_icon, int user_selection);

int main(void) {
    // Start the program with a welcome message and directions.
    printf("Welcome to Tic Tac Toe!");
    printf("Enter 0 to quit the game or enter an integer corresponding to one of these spaces:");
    printf(" 1 | 2 | 3 \n");
    printf("---+---+---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---+---+---\n");
    printf(" 7 | 8 | 9 \n");
    
    int in_progress = 1;
    int turn_count = 0;
    
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    
    while (in_progress) {
        char current_player_icon = get_current_player_icon(turn_count);
        int user_selection;
        printf("Enter your selection player %c: ", current_player_icon);
        scanf("%d", &user_selection);
        
        
        
        if (user_selection >= 1 && user_selection <= 9) {
            execute_turn(board, current_player_icon, user_selection);
            if (turn_count >= 9) { // also add code to check if game is won.
                in_progress = 0;
            }
        } else if (user_selection == 0) {
            printf("Goodbye!");
            in_progress = 0;
        } else {
            printf("Invalid input. Try again.");
        }
    }
    return EXIT_SUCCESS;
}

int is_player_o_turn(int turn_count) {
    return turn_count % 2;
}

char get_current_player_icon(int turn_count) {
    if (is_player_o_turn(turn_count)) {
        return 'O';
    } else {
        return 'X';
    }
}

void execute_turn(char board[9], char current_player_icon, int user_selection) {
    
}
