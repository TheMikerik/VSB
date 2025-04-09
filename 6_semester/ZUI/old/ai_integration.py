import time
from ai_solver_2048 import AI2048Solver, Direction

class AI2048Controller:
    def __init__(self, game):
        """
        Initialize the AI controller
        
        Parameters:
        game (Game2048): The game instance to control
        """
        self.game = game
        self.solver = AI2048Solver(depth=3)
        self.is_active = False
        self.move_delay = 0.2  # Delay between AI moves in seconds
        self.last_move_time = 0
        
    def toggle(self):
        """Toggle AI on/off"""
        self.is_active = not self.is_active
        return self.is_active
    
    def make_move(self):
        """Make a move if AI is active and enough time has passed"""
        if not self.is_active or self.game.game_over:
            return
        
        current_time = time.time()
        if current_time - self.last_move_time < self.move_delay:
            return
        
        # Get the best move from the solver
        direction = self.solver.get_next_move(self.game.grid)
        
        # Convert Direction enum to game direction integer
        game_direction = direction.value
        
        # Make the move
        self.game.move(game_direction)
        self.last_move_time = current_time