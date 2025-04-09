import random
import copy

DIRECTIONS = ['up', 'down', 'left', 'right']
ROLLOUTS_PER_MOVE = 10
MAX_MOVES_PER_GAME = 100

def get_move(board):
    best_move = None
    best_score = float('-inf')

    for move in DIRECTIONS:
        new_board, moved, _ = simulate_move(board, move)
        if not moved:
            continue

        total_score = 0
        for _ in range(ROLLOUTS_PER_MOVE):
            sim_board = copy.deepcopy(new_board)
            score = rollout(sim_board)
            total_score += score

        avg_score = total_score / ROLLOUTS_PER_MOVE

        if avg_score > best_score:
            best_score = avg_score
            best_move = move

    return best_move or random.choice(DIRECTIONS)


def rollout(board):
    total_score = 0
    for _ in range(MAX_MOVES_PER_GAME):
        valid_moves = []
        for move in DIRECTIONS:
            new_board, moved, score = simulate_move(board, move)
            if moved:
                valid_moves.append((new_board, score))

        if not valid_moves:
            break

        board, score = random.choice(valid_moves)
        total_score += score
        add_tile(board)

    return total_score


def simulate_move(board, direction):
    new_board = copy.deepcopy(board)
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


def add_tile(board):
    empty = [(i, j) for i in range(4) for j in range(4) if board[i][j] == 0]
    if empty:
        i, j = random.choice(empty)
        board[i][j] = 4 if random.random() < 0.1 else 2
