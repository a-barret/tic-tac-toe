# Description

Alternating between player X and player O, allow the current player to select a square on a 3x3 board. If after a piece is placed, there are three Xs in a row or three Os in a row, either diagonally, horizontally or vertically, then the player whose icons form three in a row wins.

# Requirements

- Display the board to the current player before they select a square.
- End game after all squares are full or one player's icons form three in a row vertially, horizontally, or diagonally or if the current players chooses to end the game.
- Allow player to select a space that is empty to place their icon.

# Design
## Flowchart
<img src="images/TicTacToeFlowchart.png" alt="Tic Tac Toe Flowchart" width="800">

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
I made the decision in the end for no success reporting for "execute_turn" and "is_placement_legal" checks for if either an "X" or an "O" is there to return a false. Allowing for different "empty" placeholders within spaces besides " ". Additionally, I realized after running "is_placement_legal", "execute_turn" simply places the icon in the desired location. From a design perspective, checking legality isn't really part of performing your turn. So instead I renamed "execute_turn" to simply "place_icon". This was much easier to follow.
