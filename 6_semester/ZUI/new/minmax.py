import random
import copy

DEPTH = 3  # jak hluboko má Minimax přemýšlet

DIRECTIONS = ['up', 'down', 'left', 'right']

def get_move(board):
    best_move = None
    best_score = float('-inf')

    for move in DIRECTIONS:
        new_board, moved, _ = simulate_move(board, move)
        if not moved:
            continue
        score = minimax(new_board, depth=DEPTH - 1, is_max=False)
        if score > best_score:
            best_score = score
            best_move = move

    return best_move or random.choice(DIRECTIONS)


def minimax(board, depth, is_max):
    if depth == 0:
        return evaluate(board)

    if is_max:
        max_eval = float('-inf')
        for move in DIRECTIONS:
            new_board, moved, _ = simulate_move(board, move)
            if not moved:
                continue
            eval = minimax(new_board, depth - 1, False)
            max_eval = max(max_eval, eval)
        return max_eval
    else:
        # simulate random tile placement (2 or 4)
        empty = [(i, j) for i in range(4) for j in range(4) if board[i][j] == 0]
        if not empty:
            return evaluate(board)

        total = 0
        for (i, j) in empty:
            for value, prob in [(2, 0.9), (4, 0.1)]:
                temp = copy.deepcopy(board)
                temp[i][j] = value
                total += prob * minimax(temp, depth - 1, True)
        return total / len(empty)


def simulate_move(board, direction):
    """
    Simulates the move and returns (new_board, moved_flag, score_gain)
    """
    from copy import deepcopy
    new_board = deepcopy(board)
    moved = False
    score = 0

    def merge(row):
        nonlocal score
        new_row = [i for i in row if i != 0]
        merged = []
        skip = False
        for i in range(len(new_row)):
            if skip:
                skip = False
                continue
            if i + 1 < len(new_row) and new_row[i] == new_row[i + 1]:
                merged.append(new_row[i] * 2)
                score += new_row[i] * 2
                skip = True
            else:
                merged.append(new_row[i])
        while len(merged) < 4:
            merged.append(0)
        return merged

    def transpose(b): return [list(row) for row in zip(*b)]
    def reverse(b): return [list(reversed(row)) for row in b]

    if direction == 'left':
        for i in range(4):
            original = new_board[i]
            new_board[i] = merge(new_board[i])
            if new_board[i] != original:
                moved = True
    elif direction == 'right':
        for i in range(4):
            original = new_board[i]
            new_board[i] = list(reversed(merge(list(reversed(new_board[i])))))
            if new_board[i] != original:
                moved = True
    elif direction == 'up':
        new_board = transpose(new_board)
        for i in range(4):
            original = new_board[i]
            new_board[i] = merge(new_board[i])
            if new_board[i] != original:
                moved = True
        new_board = transpose(new_board)
    elif direction == 'down':
        new_board = transpose(new_board)
        for i in range(4):
            original = new_board[i]
            new_board[i] = list(reversed(merge(list(reversed(new_board[i])))))
            if new_board[i] != original:
                moved = True
        new_board = transpose(new_board)

    return new_board, moved, score


def evaluate(board):
    """
    Hodnotící funkce – čím více prázdných polí a vyšších čísel, tím lépe.
    Můžeš si to vylepšit podle libosti.
    """
    empty_tiles = sum(row.count(0) for row in board)
    max_tile = max(max(row) for row in board)
    return empty_tiles * 10 + max_tile
