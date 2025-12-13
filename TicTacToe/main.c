//
//  main.c
//  TicTacToe
//
//  Created by Aiden Barrett on 12/10/25.
//

#include <stdlib.h>
#include <stdio.h>

struct Coordinates {
    int row;
    int col;
};

void display_board(char board[3][3]);

char get_current_player_icon(int turn_count);

struct Coordinates convert_selection_to_coordinates(int user_selection);

void execute_turn(char board[3][3], char current_player_icon, struct Coordinates coordinates);

int is_placement_legal(char board[3][3], struct Coordinates coordinates);

int is_game_won(char board[3][3], char current_player_icon);

int main(void) {
    // Start the program with a welcome message and directions.
    printf("Welcome to Tic Tac Toe!\n");
    printf("Enter 0 to quit the game or enter an integer corresponding to one of these spaces:\n");
    printf(" 1 | 2 | 3 \n");
    printf("---+---+---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---+---+---\n");
    printf(" 7 | 8 | 9 \n");
    
    int in_progress = 1;
    int turn_count = 0;
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    
    while (in_progress) {
        printf("Current board:\n");
        display_board(board);
        
        char current_player_icon = get_current_player_icon(turn_count);
        int user_selection;
        printf("Enter your selection player %c: ", current_player_icon);
        scanf("%d", &user_selection);
        struct Coordinates coordinates = convert_selection_to_coordinates(user_selection);
        
        if (user_selection >= 1 && user_selection <= 9) {
            execute_turn(board, current_player_icon, coordinates);
            if (turn_count >= 8 || is_game_won(board, current_player_icon)) {
                in_progress = 0;
            }
            turn_count++;
        } else if (user_selection == 0) {
            printf("Goodbye!\n");
            in_progress = 0;
        } else {
            printf("Invalid input. Try again.\n");
        }
    }
    return EXIT_SUCCESS;
}

void display_board(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf(" %c ", board[row][col]);
            if (col < 2) {
                printf("|");
            } else {
                printf("\n");
            }
        }
        if (row < 2) {
            printf("---+---+---\n");
        }
    }
}

char get_current_player_icon(int turn_count) {
    if (turn_count % 2) {
        return 'O';
    } else {
        return 'X';
    }
}

struct Coordinates convert_selection_to_coordinates(int user_selection) {
    struct Coordinates coordinates;
    coordinates.row = (user_selection - 1) / 3;
    coordinates.col = (user_selection - 1) % 3;
    return coordinates;
}

void execute_turn(char board[3][3], char current_player_icon, struct Coordinates coordinates) {
    if (is_placement_legal(board, coordinates)) {
        board[coordinates.row][coordinates.col] = current_player_icon;
    } else {
        printf("An %c cannot be placed there.", current_player_icon);
    }
}

int is_placement_legal(char board[3][3], struct Coordinates coordinates) {
    if (board[coordinates.row][coordinates.col] != 'X' && board[coordinates.row][coordinates.col] != 'O') {
        return 1;
    } else {
        return 0;
    }
}

int is_game_won(char board[3][3], char current_player_icon) {
    for (int row = 0; row<=2; row++) {
        if (board[row][0] == board[row][1] == board[row][2]) {
            return 1;
        }
        
        if (row == 0 && board[row][row] == board[row + 1][row + 1] == board[row + 2][row + 2]) {
            return 1;
        }
        
        if (row == 2 && board[row][row - 2] == board[row - 1][row + 1] == board[row - 2][row + 2]) {
            return 1;
        }
    }
    
    for (int col = 0; col<=2; col++) {
        if (board[0][col] == board[1][col] == board[2][col]) {
            return 1;
        }
    }
    
    return 0;
}
