import numpy as np
import random
from enum import Enum
import time

class Direction(Enum):
    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3

class AI2048Solver:
    def __init__(self, depth=3):
        """
        Initialize the AI solver with a specified search depth
        
        Parameters:
        depth (int): The depth of the search tree. Higher values give better results but take longer.
        """
        self.depth = depth
        self.move_weights = {
            # Weights for different evaluation factors
            'empty_cells': 10.0,       # Prefer more empty cells
            'monotonicity': 2.0,       # Prefer monotonic arrangements (increasing/decreasing)
            'smoothness': 2.0,         # Prefer similar values next to each other
            'max_tile': 1.0,           # Prefer higher max tile
            'corner_max': 2.0,         # Prefer max tile in corner
            'edge_values': 1.5         # Prefer high values on edges
        }
        
    def get_next_move(self, grid):
        """
        Determine the best move for the given grid state
        
        Parameters:
        grid (numpy.ndarray): The current game grid
        
        Returns:
        Direction: The best move direction
        """
        best_score = float('-inf')
        best_move = None
        
        # Try all possible moves
        for direction in Direction:
            # Create a copy of the grid
            grid_copy = grid.copy()
            
            # Simulate the move
            moved, new_grid, score = self._simulate_move(grid_copy, direction)
            
            # If the move is valid, evaluate it
            if moved:
                # Use expectimax search to evaluate the move
                move_score = self._expectimax(new_grid, self.depth, False)
                
                # Update best move if this one is better
                if move_score > best_score:
                    best_score = move_score
                    best_move = direction
        
        # If no valid move is found, return a random move
        if best_move is None:
            return random.choice(list(Direction))
            
        return best_move
    
    def _simulate_move(self, grid, direction):
        """
        Simulate a move and return the resulting grid and score gain
        
        Parameters:
        grid (numpy.ndarray): The current game grid
        direction (Direction): The direction to move
        
        Returns:
        tuple: (moved, new_grid, score_gain)
        """
        # Make a copy of the grid
        new_grid = grid.copy()
        score_gain = 0
        moved = False
        
        if direction == Direction.UP:  # Up
            for j in range(4):
                # Extract column
                column = new_grid[:, j]
                # Remove zeros
                column = column[column != 0]
                # Merge same numbers
                i = 0
                while i < len(column) - 1:
                    if column[i] == column[i + 1]:
                        column[i] *= 2
                        score_gain += column[i]
                        column = np.delete(column, i + 1)
                        moved = True
                    i += 1
                # Pad with zeros
                column = np.pad(column, (0, 4 - len(column)), 'constant')
                # Update grid
                new_grid[:, j] = column
                
        elif direction == Direction.RIGHT:  # Right
            for i in range(4):
                # Extract row
                row = new_grid[i, :]
                # Remove zeros
                row = row[row != 0]
                # Merge same numbers
                j = len(row) - 1
                while j > 0:
                    if row[j] == row[j - 1]:
                        row[j] *= 2
                        score_gain += row[j]
                        row = np.delete(row, j - 1)
                        j -= 1
                        moved = True
                    j -= 1
                # Pad with zeros
                row = np.pad(row, (4 - len(row), 0), 'constant')
                # Update grid
                new_grid[i, :] = row
                
        elif direction == Direction.DOWN:  # Down
            for j in range(4):
                # Extract column
                column = new_grid[:, j]
                # Remove zeros
                column = column[column != 0]
                # Merge same numbers
                i = len(column) - 1
                while i > 0:
                    if column[i] == column[i - 1]:
                        column[i] *= 2
                        score_gain += column[i]
                        column = np.delete(column, i - 1)
                        i -= 1
                        moved = True
                    i -= 1
                # Pad with zeros
                column = np.pad(column, (4 - len(column), 0), 'constant')
                # Update grid
                new_grid[:, j] = column
                
        elif direction == Direction.LEFT:  # Left
            for i in range(4):
                # Extract row
                row = new_grid[i, :]
                # Remove zeros
                row = row[row != 0]
                # Merge same numbers
                j = 0
                while j < len(row) - 1:
                    if row[j] == row[j + 1]:
                        row[j] *= 2
                        score_gain += row[j]
                        row = np.delete(row, j + 1)
                        moved = True
                    j += 1
                # Pad with zeros
                row = np.pad(row, (0, 4 - len(row)), 'constant')
                # Update grid
                new_grid[i, :] = row
        
        # Check if any cell moved
        if not moved:
            moved = not np.array_equal(grid, new_grid)
            
        return moved, new_grid, score_gain
    
    def _expectimax(self, grid, depth, is_max_node):
        """
        Perform expectimax search to evaluate moves
        
        Parameters:
        grid (numpy.ndarray): The current game grid
        depth (int): The remaining depth to search
        is_max_node (bool): Whether this is a maximizing node
        
        Returns:
        float: The evaluated score for the state
        """
        # Base case: reached depth limit
        if depth == 0:
            return self._evaluate_grid(grid)
        
        # Check for game over
        if not self._can_move(grid) and np.count_nonzero(grid == 0) == 0:
            return float('-inf')
        
        if is_max_node:
            # Maximizing player (the AI)
            max_value = float('-inf')
            
            # Try all possible moves
            for direction in Direction:
                # Simulate the move
                moved, new_grid, _ = self._simulate_move(grid, direction)
                
                # If the move is valid, evaluate it
                if moved:
                    value = self._expectimax(new_grid, depth - 1, False)
                    max_value = max(max_value, value)
            
            return max_value
        else:
            # Chance node (random tile spawn)
            expected_value = 0
            empty_cells = [(i, j) for i in range(4) for j in range(4) if grid[i, j] == 0]
            
            # If no empty cells, return the evaluation
            if not empty_cells:
                return self._evaluate_grid(grid)
            
            # For each empty cell
            for i, j in empty_cells:
                # Try placing a 2 (90% probability)
                grid_copy = grid.copy()
                grid_copy[i, j] = 2
                value_with_2 = self._expectimax(grid_copy, depth - 1, True)
                
                # Try placing a 4 (10% probability)
                grid_copy = grid.copy()
                grid_copy[i, j] = 4
                value_with_4 = self._expectimax(grid_copy, depth - 1, True)
                
                # Calculate expected value based on probabilities
                cell_expected_value = 0.9 * value_with_2 + 0.1 * value_with_4
                expected_value += cell_expected_value / len(empty_cells)
            
            return expected_value
    
    def _evaluate_grid(self, grid):
        """
        Evaluate the given grid state
        
        Parameters:
        grid (numpy.ndarray): The current game grid
        
        Returns:
        float: The evaluated score for the state
        """
        # Number of empty cells
        empty_cells = np.count_nonzero(grid == 0)
        
        # Max tile value
        max_tile = np.max(grid)
        
        # Monotonicity: prefer grids where values are monotonically increasing or decreasing
        monotonicity_score = self._calculate_monotonicity(grid)
        
        # Smoothness: prefer grids where adjacent tiles have similar values
        smoothness_score = self._calculate_smoothness(grid)
        
        # Corner preference: higher values in corners are good
        corner_max_score = self._calculate_corner_max(grid)
        
        # Edge values: higher values on edges are good
        edge_values_score = self._calculate_edge_values(grid)
        
        # Combine all factors with their weights
        total_score = (
            self.move_weights['empty_cells'] * empty_cells +
            self.move_weights['monotonicity'] * monotonicity_score +
            self.move_weights['smoothness'] * smoothness_score +
            self.move_weights['max_tile'] * np.log2(max_tile) +
            self.move_weights['corner_max'] * corner_max_score +
            self.move_weights['edge_values'] * edge_values_score
        )
        
        return total_score
    
    def _calculate_monotonicity(self, grid):
        """Calculate monotonicity score: higher when values increase/decrease consistently"""
        mono_score = 0
        
        # Check rows
        for i in range(4):
            # Left to right
            left_right = 0
            for j in range(1, 4):
                if grid[i, j-1] != 0 and grid[i, j] != 0:
                    if grid[i, j-1] <= grid[i, j]:
                        left_right += 1
            
            # Right to left
            right_left = 0
            for j in range(2, -1, -1):
                if grid[i, j+1] != 0 and grid[i, j] != 0:
                    if grid[i, j+1] <= grid[i, j]:
                        right_left += 1
            
            mono_score += max(left_right, right_left)
        
        # Check columns
        for j in range(4):
            # Top to bottom
            top_bottom = 0
            for i in range(1, 4):
                if grid[i-1, j] != 0 and grid[i, j] != 0:
                    if grid[i-1, j] <= grid[i, j]:
                        top_bottom += 1
            
            # Bottom to top
            bottom_top = 0
            for i in range(2, -1, -1):
                if grid[i+1, j] != 0 and grid[i, j] != 0:
                    if grid[i+1, j] <= grid[i, j]:
                        bottom_top += 1
            
            mono_score += max(top_bottom, bottom_top)
        
        return mono_score
    
    def _calculate_smoothness(self, grid):
        """Calculate smoothness score: higher when adjacent tiles have similar values"""
        smoothness = 0
        
        # For each non-empty cell
        for i in range(4):
            for j in range(4):
                if grid[i, j] != 0:
                    # Check right
                    if j < 3 and grid[i, j+1] != 0:
                        smoothness -= abs(np.log2(grid[i, j]) - np.log2(grid[i, j+1]))
                    
                    # Check down
                    if i < 3 and grid[i+1, j] != 0:
                        smoothness -= abs(np.log2(grid[i, j]) - np.log2(grid[i+1, j]))
        
        return smoothness
    
    def _calculate_corner_max(self, grid):
        """Calculate corner max score: higher when max value is in a corner"""
        max_value = np.max(grid)
        corners = [grid[0, 0], grid[0, 3], grid[3, 0], grid[3, 3]]
        
        if max_value in corners:
            return max_value
        return 0
    
    def _calculate_edge_values(self, grid):
        """Calculate edge values score: higher when large values are on edges"""
        edge_sum = (
            sum(grid[0, :]) +  # Top row
            sum(grid[3, :]) +  # Bottom row
            sum(grid[1:3, 0]) +  # Left column (excluding corners)
            sum(grid[1:3, 3])    # Right column (excluding corners)
        )
        
        return np.log2(edge_sum + 1)
    
    def _can_move(self, grid):
        """Check if any moves are possible"""
        # Check if there are any empty cells
        if 0 in grid:
            return True
        
        # Check if there are any adjacent cells with the same value
        for i in range(4):
            for j in range(4):
                current = grid[i, j]
                # Check right
                if j < 3 and current == grid[i, j + 1]:
                    return True
                # Check down
                if i < 3 and current == grid[i + 1, j]:
                    return True
        
        return False