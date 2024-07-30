"""
Tic Tac Toe Player
"""

import math
import copy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    x_count = sum(board[i][j] == X for i in range(len(board)) for j in range(len(board[i])))
    o_count = sum(board[i][j] == O for i in range(len(board)) for j in range(len(board[i])))
    return X if x_count <= o_count else O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    return set([(i, j) for i in range(len(board)) for j in range(len(board[i])) if board[i][j] == EMPTY])


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    i, j = action
    if 0 <= i <= 2 and 0 <= j <= 2 and board[i][j] == EMPTY:
        b = copy.deepcopy(board)
        b[i][j] = player(board)
        return b
    else:
        raise IndexError("Invalid action")


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    n = len(board)
    for i in range(n):
        if board[i][0] == board[i][1] == board[i][2]:
            if board[i][0] != EMPTY:
                return board[i][0]
        
        if board[0][i] == board[1][i] == board[2][i]:
            if board[0][i] != EMPTY:
                return board[1][i]
            
    if board[0][0] == board[1][1] == board[2][2] or board[0][2] == board[1][1] == board[2][0]:
        if board[1][1] != EMPTY:
            return board[1][1]
        
    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) is not None:
        return True

    return not any(board[i][j] == EMPTY for i in range(len(board)) for j in range(len(board[i])))


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    win = winner(board)
    if win is not None:
        return 1 if win == X else -1
    else:
        return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None

    optimal = None
    value = None
    is_x = player(board) == X

    for action in actions(board):
        if is_x:
            tmp = min_value(result(board, action))
            if value is None or tmp > value:
                value = tmp
                optimal = action
        else:
            tmp = max_value(result(board, action))
            if value is None or tmp < value:
                value = tmp
                optimal = action

    return optimal


def min_value(board):
    if terminal(board):
        return utility(board)
    
    value = float('inf')
    for action in actions(board):
        value = min(value, max_value(result(board, action)))
    
    return value


def max_value(board):
    if terminal(board):
        return utility(board)
    
    value = float('-inf')
    for action in actions(board):
        value = max(value, min_value(result(board, action)))
    
    return value
    
