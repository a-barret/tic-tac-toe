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

void display_welcome_message(void);

void wait_for_enter(void);

void display_board(char board[3][3]);

char get_current_player_icon(int turn_count);

void flush_line(void);

void convert_selection_to_coordinates(struct Coordinates* coordinates, int user_selection);

void execute_turn(char board[3][3], char current_player_icon, struct Coordinates coordinates);

int is_placement_legal(char board[3][3], struct Coordinates coordinates);

int is_game_won(char board[3][3], char current_player_icon);

void display_completion_message(int game_won, char current_player_icon);

void toggle_number_guides(char board[3][3], int* include_number_guides);

int main(void) {
    // Start the program with a welcome message and directions.
    display_welcome_message();
    
    int game_won = 0;
    int in_progress = 1;
    int turn_count = 0;
    int include_number_guides = 1;
    char current_player_icon;
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    
    while (in_progress) {
        display_board(board);
        
        current_player_icon = get_current_player_icon(turn_count);
        int user_selection;
        printf("Enter your selection player %c: ", current_player_icon);
        scanf("%d", &user_selection);
        flush_line();
        
        if (user_selection >= 1 && user_selection <= 9) {
            struct Coordinates* coordinates = malloc(sizeof(*coordinates));
            convert_selection_to_coordinates(coordinates, user_selection);
            execute_turn(board, current_player_icon, *coordinates);
            free(coordinates);
            game_won = is_game_won(board, current_player_icon);
            if (turn_count >= 8 || game_won) {
                in_progress = 0;
                if (include_number_guides) {
                    toggle_number_guides(board, &include_number_guides);
                }
                display_board(board);
                display_completion_message(game_won, current_player_icon);
            }
            turn_count++;
        } else if (user_selection == 10) {
            toggle_number_guides(board, &include_number_guides);
        } else if (user_selection == 11) {
            display_welcome_message();
        } else if (user_selection == 0) {
            printf("Goodbye!\n");
            in_progress = 0;
        } else {
            printf("Invalid input. Try again.\n");
        }
    }
    return EXIT_SUCCESS;
}

void display_welcome_message(void) {
    printf("Welcome to Tic Tac Toe!\n");
    printf("Once the game starts, here are your options:\n");
    printf(" - Enter 0 to quit.\n");
    printf(" - Enter 10 to toggle number guides.\n");
    printf(" - Enter 11 to view this message again.\n");
    printf(" - Enter an integer 1-9 to place your icon in the corresponding space:\n");
    printf(" 1 | 2 | 3 \n");
    printf("---+---+---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---+---+---\n");
    printf(" 7 | 8 | 9 \n");
    printf("Press ENTER to start:");
    wait_for_enter();
}

void wait_for_enter(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void display_board(char board[3][3]) {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nCurrent board:\n");
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

void flush_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Do nothing
    }
}

void convert_selection_to_coordinates(struct Coordinates* coordinates, int user_selection) {
    coordinates->row = (user_selection - 1) / 3;
    coordinates->col = (user_selection - 1) % 3;
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
    // Checks for three in a row horizontally
    for (int row = 0; row<=2; row++) {
        if (board[row][0] == current_player_icon &&
            board[row][1] == current_player_icon &&
            board[row][2] == current_player_icon) {
            return 1;
        }
    }
    
    // Checks for three in a row vertically
    for (int col = 0; col<=2; col++) {
        if (board[0][col] == current_player_icon &&
            board[1][col] == current_player_icon &&
            board[2][col] == current_player_icon) {
            return 1;
        }
    }
    
    // Checks for three in a row negative diagonally
    if (board[0][0] == current_player_icon && // [0][0] is top left       1 0 0
        board[1][1] == current_player_icon && // [1][1] is true center    0 1 0
        board[2][2] == current_player_icon) { // [2][2] is bottom right   0 0 1
        return 1;
    }
    
    // Checks for three in a row positive diagonally
    if (board[2][0] == current_player_icon && // [0][2] is bottom left    0 0 1
        board[1][1] == current_player_icon && // [1][1] is true center    0 1 0
        board[0][2] == current_player_icon) { // [2][0] is top right      1 0 0
        return 1;
    }
    return 0;
}

void display_completion_message(int game_won, char current_player_icon) {
    if (game_won) {
        printf("Congratulations %c! You win!\n", current_player_icon);
    } else {
        printf("Cats game! It's a tie!\n");
    }
}

void toggle_number_guides(char board[3][3], int* include_number_guides) {
    *include_number_guides = !*include_number_guides;
    
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] != 'X' && board[row][col] != 'O') {
                if (board[row][col] == ' ') {
                    board[row][col] = '0' + (row * 3 + col + 1);
                } else {
                    board[row][col] = ' ';
                }
            }
        }
    }
}


