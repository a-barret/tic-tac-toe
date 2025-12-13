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

/**
 * @brief Displays the explanation of how to play the game.
 *
 * @details Uses printf() to display the controls for the game. It then calls
 * the "wait for enter" function to give reading time to the user(s).
 */
void display_welcome_message(void);

/**
 * @brief Waits for the user to press enter (input newline) to the terminal.
 *
 * @details Uses getchar() to see what the next item in the input stream and
 * continues grabbing the next item until that item is a "\n" character.
 */
void wait_for_enter(void);

/**
 * @brief An algorithm that displays a 2D board list that it recieves.
 *
 * @details Iterates through both the rows and columns of the 2D board list and
 * uses printf() to display each item separated by pipes and dashes to create a
 * tic tac toe board layout.
 *
 * @param[in] board This is a 2D list of char values.
 */
void display_board(char board[3][3]);

/**
 * @brief Based off the number of turns, returns a char 'X' or 'O'.
 *
 * @details Uses an integer value representing the number of turns taken in the
 * game so far and determines if it is even or odd (0 is even). The formula is
 * number MOD 2. Even means X is the current player. Odd means O. It returns
 * the icon as a char value.
 *
 * @param[in] turn_count Number of turns taken so far in the game.
 *
 * @return The char value representing the current player ('X' or 'O')
 */
char get_current_player_icon(int turn_count);

/**
 * @brief Clears out any whitespace characters from the input feed.
 *
 * @details Uses a while loop to pull the next character from the input feed
 * and then does nothing with it, moving to the next character until they are
 * all gone.
 */
void flush_line(void);

/**
 * @brief Converts a 1-9 integer value into a set of row, column coordinates.
 *
 * @details Takes a integer representing a location on a Tic Tac Toe board and
 * then, using the formula to calculate the row and column, places those
 * results into the row and column values of the struct respectively. The
 * formula of the row is rounddown(n / 3) and the formula for the column is
 * n MOD 3.
 *
 * @param[in] coordinates A pointer to a coordinates struct.
 * @param[in] user_selection An integer representing a Tic Tac Toe location to
 * be converted to coordinates.
 */
void convert_selection_to_coordinates(struct Coordinates* coordinates, int user_selection);

/**
 * @brief Checks if a given space already has an icon in the space.
 *
 * @details Uses the coordinates to check a space on the board input. If there
 * is an 'X' or an 'O', the function will return a 0 (false) value and 1 (true)
 * if not.
 *
 * @param[in] board A 2D list representing each space on a Tic Tac Toe board.
 * @param[in] coordinates A struct with a row and column integer value.
 *
 * @return An integer value representing true or false legality.
 */
int is_placement_legal(char board[3][3], struct Coordinates coordinates);

/**
 * @brief Puts the current player's icon at the designated coordinates.
 *
 * @details Uses the given coordinates to find the right space on the board and
 * then places the given player icon in that space.
 *
 * @param[in] board A 2D list representing each space on a Tic Tac Toe board.
 * @param[in] current_player_icon A char value of the current player's icon.
 * @param[in] coordinates A struct with a row and column integer value.
 */
void place_icon(char board[3][3], char current_player_icon, struct Coordinates coordinates);

/**
 * @brief Check all conditions of the board being in a winning state.
 *
 * @details Checks for three in a row horizontally in any row, vertically in
 * any column, or diagonally from any two opposite corners.
 *
 * @param[in] board A 2D list representing each space on a Tic Tac Toe board.
 * @param[in] current_player_icon A char value of the current player's icon.
 *
 * @return An integer 1 or 0. 1 for true, 0 for false.
 */
int is_game_won(char board[3][3], char current_player_icon);

/**
 * @brief Displays a message to the user(s) of the status of the completed game.
 *
 * @details Uses the status of the game being won or not to tell the user that
 * the current player has won or if the game was not won then to tell the user
 * that the game is a tie.
 *
 * @param[in] game_won A true or false integer value.
 * @param[in] current_player_icon A char value of the current player's icon.
 */
void display_completion_message(int game_won, char current_player_icon);

/**
 * @brief Changes the user setting to display numbers on spaces or not.
 *
 * @details Changes the boards empty values to contain their corresponding
 * integer values or not. It does not change spaces that have an 'X' or an 'O'
 * char value. It sets their current value to the opposite of what they
 * currently are.
 *
 * @param[in] board A 2D list representing each space on a Tic Tac Toe board.
 * @param[in] include_number_guides A true or false integer value showing the
 * status of the showing the number guides or not.
 */
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
            if (is_placement_legal(board, *coordinates)) {
                place_icon(board, current_player_icon, *coordinates);
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
            } else {
                printf("An %c cannot be placed there.\n", current_player_icon);
            }
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
    printf("Current board:\n");
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

int is_placement_legal(char board[3][3], struct Coordinates coordinates) {
    if (board[coordinates.row][coordinates.col] != 'X' && board[coordinates.row][coordinates.col] != 'O') {
        return 1;
    } else {
        return 0;
    }
}

void place_icon(char board[3][3], char current_player_icon, struct Coordinates coordinates) {
    board[coordinates.row][coordinates.col] = current_player_icon;
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


