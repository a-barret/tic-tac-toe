# Description

Alternating between player X and player O, allow the current player to select a square on a 3x3 board. If after a piece is placed, there are three Xs in a row or three Os in a row, either diagonally, horizontally or vertically, then the player whose icons form three in a row wins.

# Requirements

- Display the board to the current player before they select a square.
- End game after all squares are full or one player's icons form three in a row vertially, horizontally, or diagonally or if the current players chooses to end the game.
- Allow player to select a space that is empty to place their icon.

# Design

One of the more confusing pieces to implement was the function to change the board at the location the player wanted to place their icon. I wrote the solution in pseudocode first to better understand the process.
```pseudocode
FUNCTION ExecuteTurn(board, currentPlayerIcon, coordinates)
    IF IsPlacementLegal(board, coordinates)
        SET board[coordinates[0]][coordinates[1]] = currentPlayerIcon
        RETURN TRUE
    ELSE
        PUT You cannot place your icon there.
        RETURN FALSE
    ENDIF
ENDFUNCTION

FUNCTION IsPlacementLegal(board, coordinates)
    IF board[coordinates[0]][coordinates[1]] = ' '
        RETURN TRUE
    ELSE
        RETURN FALSE
    ENDIF
ENDFUNCTION
```
