import random
import copy
from functools import lru_cache

# Depth of the expectiminimax search
DEPTH = 3  # You can adjust this based on performance

DIRECTIONS = ['up', 'down', 'left', 'right']

# Snake pattern - encourages tiles to be arranged in a snake pattern
# with high values in specific positions
PERFECT_SNAKE = [
    [1,     2,     3,     4],
    [8,     7,     6,     5],
    [9,    10,    11,    12],
    [16,    15,    14,    13]
]

# Pre-computed weights for evaluation functions
EMPTY_WEIGHT = 10.0
SNAKE_WEIGHT = 1.0
MONO_WEIGHT = 20.0
SMOOTH_WEIGHT = 5.0
MERGE_WEIGHT = 15.0  # New weight for potential merges

# Cache for evaluation results
EVAL_CACHE = {}

def get_move(board):
    """Returns the best move using expectiminimax algorithm with alpha-beta pruning"""
    best_move = None
    best_score = float('-inf')
    
    # Clear the cache for a new board state
    EVAL_CACHE.clear()
    
    # For performance optimization, try most promising moves first
    # (This move ordering is based on empirical observation that 'up' and 'left' 
    # are often better in 2048)
    ordered_moves = ['up', 'left', 'right', 'down']
    
    for move in ordered_moves:
        new_board, moved, score_gained = simulate_move(board, move)
        if not moved:
            continue
        
        # For the initial move, we use expectiminimax with depth-0.5 to represent
        # it's the computer's turn next (adding a random tile)
        score = expectiminimax(tuple(map(tuple, new_board)), depth=DEPTH-0.5, is_max=False, alpha=float('-inf'), beta=float('inf'))
        
        # Bias slightly toward moves that merge tiles (gives immediate score)
        score += score_gained * 0.1
        
        if score > best_score:
            best_score = score
            best_move = move

    # If no good move was found, try any valid move
    if best_move is None:
        for move in DIRECTIONS:
            new_board, moved, _ = simulate_move(board, move)
            if moved:
                return move
    
    return best_move

def board_to_tuple(board):
    """Convert a board to an immutable tuple representation for caching"""
    return tuple(tuple(row) for row in board)

def expectiminimax(board_tuple, depth, is_max=True, alpha=float('-inf'), beta=float('inf')):
    """
    Optimized expectiminimax algorithm with alpha-beta pruning
    """
    # Early termination
    if depth <= 0:
        # Check if we've already evaluated this board
        if board_tuple in EVAL_CACHE:
            return EVAL_CACHE[board_tuple]
        
        # Otherwise evaluate and cache the result
        board = [list(row) for row in board_tuple]
        result = evaluate(board)
        EVAL_CACHE[board_tuple] = result
        return result

    # Convert back to list for processing
    board = [list(row) for row in board_tuple]
    
    if is_max:
        # Player's turn - choose the maximum score from possible moves
        max_eval = float('-inf')
        
        # Try most promising moves first for better pruning
        for move in ['up', 'left', 'right', 'down']:
            new_board, moved, _ = simulate_move(board, move)
            if not moved:
                continue
                
            new_board_tuple = board_to_tuple(new_board)
            eval_score = expectiminimax(new_board_tuple, depth - 0.5, False, alpha, beta)
            max_eval = max(max_eval, eval_score)
            
            # Alpha-beta pruning
            alpha = max(alpha, eval_score)
            if beta <= alpha:
                break
                
        return max_eval
    else:
        # Computer's turn - calculate expected score from random tile placements
        empty = [(i, j) for i in range(4) for j in range(4) if board[i][j] == 0]
        if not empty:
            # If board is full, evaluate directly
            result = evaluate(board)
            EVAL_CACHE[board_tuple] = result
            return result
        
        # Performance optimization: if many empty cells, sample a subset
        if len(empty) > 6 and depth > 1:
            # Sample a smaller number of empty cells for deeper searches
            empty = random.sample(empty, min(4, len(empty)))
        
        # Calculate expected value over sampled tile placements
        total = 0
        count = 0
        
        # Only consider adding a 2 (90% probability) for deeper searches to save time
        # Add both 2 and 4 for shallower searches for accuracy
        tile_options = [(2, 0.9), (4, 0.1)] if depth <= 1.5 else [(2, 1.0)]
        
        for (i, j) in empty:
            for value, prob in tile_options:
                temp = copy.deepcopy(board)
                temp[i][j] = value
                temp_tuple = board_to_tuple(temp)
                score = expectiminimax(temp_tuple, depth - 0.5, True, alpha, beta)
                total += prob * score
                count += prob
                
        return total / count if count > 0 else 0

def simulate_move(board, direction):
    """
    Simulates the move and returns (new_board, moved_flag, score_gain)
    Optimized version that avoids unnecessary operations
    """
    # Create a copy of the board
    new_board = [row[:] for row in board]  # Faster than deepcopy for small lists
    moved = False
    score = 0

    def merge(row):
        nonlocal score
        # Faster implementation that avoids creating multiple lists
        # Filter zeros in-place
        new_row = [i for i in row if i != 0]
        result = [0, 0, 0, 0]  # Pre-allocate result
        idx = 0
        i = 0
        
        while i < len(new_row):
            if i + 1 < len(new_row) and new_row[i] == new_row[i + 1]:
                merged_value = new_row[i] * 2
                result[idx] = merged_value
                score += merged_value
                i += 2
            else:
                result[idx] = new_row[i]
                i += 1
            idx += 1
            
        return result

    def transpose(b):
        return [[b[j][i] for j in range(4)] for i in range(4)]

    if direction == 'left':
        for i in range(4):
            original = new_board[i][:]  # Fast copy
            new_board[i] = merge(new_board[i])
            if new_board[i] != original:
                moved = True
    elif direction == 'right':
        for i in range(4):
            # Reverse, merge, then reverse back
            row = new_board[i][::-1]  # Faster than list(reversed())
            original = row[:]
            merged = merge(row)
            if merged != original:
                moved = True
            new_board[i] = merged[::-1]  # Reverse back
    elif direction == 'up':
        transposed = transpose(new_board)
        original_transposed = [row[:] for row in transposed]
        for i in range(4):
            transposed[i] = merge(transposed[i])
        if transposed != original_transposed:
            moved = True
        new_board = transpose(transposed)
    elif direction == 'down':
        transposed = transpose(new_board)
        original_transposed = [row[:] for row in transposed]
        for i in range(4):
            row = transposed[i][::-1]
            merged = merge(row)
            transposed[i] = merged[::-1]
        if transposed != original_transposed:
            moved = True
        new_board = transpose(transposed)

    return new_board, moved, score

# Create a pattern-based lookup table for faster evaluation
PATTERN_TABLE = {}
def initialize_pattern_table():
    """Pre-compute evaluation scores for common patterns"""
    # This would be an advanced optimization - we'll just use a placeholder here
    pass

initialize_pattern_table()

def evaluate(board):
    """
    Optimized evaluation function using multiple heuristics
    """
    # Quick lookup for common patterns (would need to be implemented for full optimization)
    board_hash = hash(board_to_tuple(board))
    if board_hash in PATTERN_TABLE:
        return PATTERN_TABLE[board_hash]
    
    # Fast path: if more than half the board is empty, just count empty tiles
    empty_tiles = sum(row.count(0) for row in board)
    if empty_tiles > 8:
        return empty_tiles * EMPTY_WEIGHT
    
    # Snake pattern score - optimized calculation
    snake_score = 0
    max_tile = 0
    
    for i in range(4):
        for j in range(4):
            value = board[i][j]
            if value > max_tile:
                max_tile = value
            if value != 0:
                snake_score += value * PERFECT_SNAKE[i][j]
    
    # Calculate potential merges (fewer calculations than full smoothness)
    merge_potential = calculate_merge_potential(board)
    
    # Only calculate more expensive metrics for boards with fewer empty spaces
    if empty_tiles <= 6:
        mono_score = calculate_monotonicity(board)
        smooth_score = calculate_smoothness(board)
    else:
        # For boards with many empty spaces, use simplified metrics
        mono_score = simplified_monotonicity(board)
        smooth_score = 0  # Skip smoothness calculation for speed
    
    # Combine all heuristics with their weights
    final_score = (
        SNAKE_WEIGHT * snake_score + 
        EMPTY_WEIGHT * empty_tiles +
        MONO_WEIGHT * mono_score +
        SMOOTH_WEIGHT * smooth_score +
        MERGE_WEIGHT * merge_potential
    )
    
    # Corner bonus: having max tile in corner is good
    if max_tile == board[0][0] or max_tile == board[0][3] or max_tile == board[3][0] or max_tile == board[3][3]:
        final_score *= 1.2
    
    return final_score

def simplified_monotonicity(board):
    """A faster, simpler version of monotonicity calculation"""
    mono_score = 0
    
    # Just check if the maximum value is in the correct position
    max_val = 0
    max_i, max_j = 0, 0
    
    for i in range(4):
        for j in range(4):
            if board[i][j] > max_val:
                max_val = board[i][j]
                max_i, max_j = i, j
    
    # Prefer max value in top-left corner (position [0][0])
    if max_i == 0 and max_j == 0:
        mono_score += 2
    
    # Simplified row check (prefer decreasing from left to right in top row)
    for j in range(3):
        if board[0][j] >= board[0][j+1] and board[0][j] > 0 and board[0][j+1] > 0:
            mono_score += 1
    
    return mono_score

def calculate_monotonicity(board):
    """Calculate how monotonic (ordered) the tiles are in each direction"""
    # This is the same as the original, kept for boards with few empty spaces
    total_mono = 0
    
    # Check rows
    for i in range(4):
        mono_left = 0
        mono_right = 0
        for j in range(3):
            if board[i][j] != 0 and board[i][j+1] != 0:
                if board[i][j] >= board[i][j+1]:
                    mono_left += 1
                if board[i][j] <= board[i][j+1]:
                    mono_right += 1
        total_mono += max(mono_left, mono_right)
    
    # Check columns
    for j in range(4):
        mono_up = 0
        mono_down = 0
        for i in range(3):
            if board[i][j] != 0 and board[i+1][j] != 0:
                if board[i][j] >= board[i+1][j]:
                    mono_up += 1
                if board[i][j] <= board[i+1][j]:
                    mono_down += 1
        total_mono += max(mono_up, mono_down)
    
    return total_mono

def calculate_merge_potential(board):
    """Calculate potential for merges in the near future"""
    merge_potential = 0
    
    # Check for adjacent equal tiles horizontally
    for i in range(4):
        for j in range(3):
            if board[i][j] != 0 and board[i][j] == board[i][j+1]:
                merge_potential += 1
    
    # Check for adjacent equal tiles vertically
    for i in range(3):
        for j in range(4):
            if board[i][j] != 0 and board[i][j] == board[i+1][j]:
                merge_potential += 1
                
    return merge_potential

def calculate_smoothness(board):
    """Calculate how smooth the board is (adjacent tiles have similar values)"""
    smoothness = 0
    
    # Check horizontal smoothness
    for i in range(4):
        for j in range(3):
            if board[i][j] != 0 and board[i][j+1] != 0:
                # Use log base 2 difference for better scaling
                diff = abs(board[i][j] - board[i][j+1])
                smoothness -= diff
    
    # Check vertical smoothness
    for i in range(3):
        for j in range(4):
            if board[i][j] != 0 and board[i+1][j] != 0:
                diff = abs(board[i][j] - board[i+1][j])
                smoothness -= diff
                
    return smoothness