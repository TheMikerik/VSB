import pygame
import random
import sys
import numpy as np
from ai_solver_2048 import AI2048Solver, Direction
from ai_integration import AI2048Controller
import time

# Initialize pygame
pygame.init()

# Constants
GRID_SIZE = 4
CELL_SIZE = 100
GRID_PADDING = 10
WINDOW_WIDTH = GRID_SIZE * CELL_SIZE + (GRID_SIZE + 1) * GRID_PADDING
WINDOW_HEIGHT = GRID_SIZE * CELL_SIZE + (GRID_SIZE + 1) * GRID_PADDING + 100
BUTTON_WIDTH = 120
BUTTON_HEIGHT = 40
BUTTON_PADDING = 20

# Colors
BACKGROUND_COLOR = (250, 248, 239)
GRID_COLOR = (187, 173, 160)
EMPTY_CELL_COLOR = (205, 193, 180)
BUTTON_COLOR = (142, 122, 101)
BUTTON_HOVER_COLOR = (156, 135, 113)
TEXT_COLOR = (249, 246, 242)
TILE_COLORS = {
    0: (205, 193, 180),
    2: (238, 228, 218),
    4: (237, 224, 200),
    8: (242, 177, 121),
    16: (245, 149, 99),
    32: (246, 124, 95),
    64: (246, 94, 59),
    128: (237, 207, 114),
    256: (237, 204, 97),
    512: (237, 200, 80),
    1024: (237, 197, 63),
    2048: (237, 194, 46)
}
TILE_TEXT_COLORS = {
    2: (119, 110, 101),
    4: (119, 110, 101),
    8: (249, 246, 242),
    16: (249, 246, 242),
    32: (249, 246, 242),
    64: (249, 246, 242),
    128: (249, 246, 242),
    256: (249, 246, 242),
    512: (249, 246, 242),
    1024: (249, 246, 242),
    2048: (249, 246, 242)
}

# Create the window
window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("2048 Game")

# Fonts
font = pygame.font.SysFont("Arial", 36, bold=True)
small_font = pygame.font.SysFont("Arial", 24, bold=True)


class Game2048:
    def __init__(self):
        self.grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
        self.score = 0
        self.game_over = False
        self.add_new_tile()
        self.add_new_tile()

    def add_new_tile(self):
        # Find empty cells
        empty_cells = [(i, j) for i in range(GRID_SIZE) for j in range(GRID_SIZE) if self.grid[i, j] == 0]
        if empty_cells:
            # Choose a random empty cell
            i, j = random.choice(empty_cells)
            # Place a 2 or 4 with 90% and 10% probability respectively
            self.grid[i, j] = 2 if random.random() < 0.9 else 4

    def move(self, direction):
        # 0: up, 1: right, 2: down, 3: left
        moved = False
        
        # Make a copy of the grid to check if it changes
        old_grid = self.grid.copy()
        
        if direction == 0:  # Up
            for j in range(GRID_SIZE):
                # Extract column
                column = self.grid[:, j]
                # Remove zeros
                column = column[column != 0]
                # Merge same numbers
                i = 0
                while i < len(column) - 1:
                    if column[i] == column[i + 1]:
                        column[i] *= 2
                        self.score += column[i]
                        column = np.delete(column, i + 1)
                    i += 1
                # Pad with zeros
                column = np.pad(column, (0, GRID_SIZE - len(column)), 'constant')
                # Update grid
                self.grid[:, j] = column
                
        elif direction == 1:  # Right
            for i in range(GRID_SIZE):
                # Extract row
                row = self.grid[i, :]
                # Remove zeros
                row = row[row != 0]
                # Merge same numbers
                j = len(row) - 1
                while j > 0:
                    if row[j] == row[j - 1]:
                        row[j] *= 2
                        self.score += row[j]
                        row = np.delete(row, j - 1)
                        j -= 1
                    j -= 1
                # Pad with zeros
                row = np.pad(row, (GRID_SIZE - len(row), 0), 'constant')
                # Update grid
                self.grid[i, :] = row
                
        elif direction == 2:  # Down
            for j in range(GRID_SIZE):
                # Extract column
                column = self.grid[:, j]
                # Remove zeros
                column = column[column != 0]
                # Merge same numbers
                i = len(column) - 1
                while i > 0:
                    if column[i] == column[i - 1]:
                        column[i] *= 2
                        self.score += column[i]
                        column = np.delete(column, i - 1)
                        i -= 1
                    i -= 1
                # Pad with zeros
                column = np.pad(column, (GRID_SIZE - len(column), 0), 'constant')
                # Update grid
                self.grid[:, j] = column
                
        elif direction == 3:  # Left
            for i in range(GRID_SIZE):
                # Extract row
                row = self.grid[i, :]
                # Remove zeros
                row = row[row != 0]
                # Merge same numbers
                j = 0
                while j < len(row) - 1:
                    if row[j] == row[j + 1]:
                        row[j] *= 2
                        self.score += row[j]
                        row = np.delete(row, j + 1)
                    j += 1
                # Pad with zeros
                row = np.pad(row, (0, GRID_SIZE - len(row)), 'constant')
                # Update grid
                self.grid[i, :] = row
                
        # Check if the grid changed
        if not np.array_equal(old_grid, self.grid):
            moved = True
            self.add_new_tile()
            
        # Check for game over
        if not moved and not self.can_move():
            self.game_over = True
            
        return moved
    
    def can_move(self):
        # Check if there are any empty cells
        if 0 in self.grid:
            return True
        
        # Check if there are any adjacent cells with the same value
        for i in range(GRID_SIZE):
            for j in range(GRID_SIZE):
                current = self.grid[i, j]
                # Check right
                if j < GRID_SIZE - 1 and current == self.grid[i, j + 1]:
                    return True
                # Check down
                if i < GRID_SIZE - 1 and current == self.grid[i + 1, j]:
                    return True
        
        return False
    
    def restart(self):
        self.grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
        self.score = 0
        self.game_over = False
        self.add_new_tile()
        self.add_new_tile()


def draw_grid(game, ai_controller):
    # Draw background
    window.fill(BACKGROUND_COLOR)
    
    # Draw grid background
    pygame.draw.rect(window, GRID_COLOR, (0, 100, WINDOW_WIDTH, WINDOW_HEIGHT - 100))
    
    # Draw cells
    for i in range(GRID_SIZE):
        for j in range(GRID_SIZE):
            # Calculate cell position
            x = j * CELL_SIZE + (j + 1) * GRID_PADDING
            y = i * CELL_SIZE + (i + 1) * GRID_PADDING + 100
            
            # Draw cell
            cell_value = game.grid[i, j]
            color = TILE_COLORS.get(cell_value, TILE_COLORS[2048])
            pygame.draw.rect(window, color, (x, y, CELL_SIZE, CELL_SIZE))
            
            # Draw number
            if cell_value != 0:
                text_color = TILE_TEXT_COLORS.get(cell_value, TEXT_COLOR)
                text = font.render(str(cell_value), True, text_color)
                text_rect = text.get_rect(center=(x + CELL_SIZE // 2, y + CELL_SIZE // 2))
                window.blit(text, text_rect)
    
    # Draw score
    score_text = small_font.render(f"Score: {game.score}", True, (119, 110, 101))
    window.blit(score_text, (20, 20))
    
    # Draw buttons
    restart_button = pygame.Rect(WINDOW_WIDTH - 2 * BUTTON_WIDTH - BUTTON_PADDING, 30, BUTTON_WIDTH, BUTTON_HEIGHT)
    ai_button = pygame.Rect(WINDOW_WIDTH - BUTTON_WIDTH, 30, BUTTON_WIDTH, BUTTON_HEIGHT)
    
    pygame.draw.rect(window, BUTTON_COLOR, restart_button)
    pygame.draw.rect(window, BUTTON_COLOR, ai_button)
    
    # Draw button text
    restart_text = small_font.render("Restart", True, TEXT_COLOR)
    ai_text = small_font.render("AI: ON" if ai_controller.is_active else "AI: OFF", True, TEXT_COLOR)
    
    
    restart_text_rect = restart_text.get_rect(center=restart_button.center)
    ai_text_rect = ai_text.get_rect(center=ai_button.center)
    
    window.blit(restart_text, restart_text_rect)
    window.blit(ai_text, ai_text_rect)
    
    # Draw game over message
    if game.game_over:
        overlay = pygame.Surface((WINDOW_WIDTH, WINDOW_HEIGHT))
        overlay.set_alpha(150)
        overlay.fill((255, 255, 255))
        window.blit(overlay, (0, 0))
        
        game_over_text = font.render("Game Over!", True, (119, 110, 101))
        game_over_rect = game_over_text.get_rect(center=(WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2))
        window.blit(game_over_text, game_over_rect)
    
    pygame.display.update()


def main():
    game = Game2048()
    ai_controller = AI2048Controller(game)
    clock = pygame.time.Clock()

    game = Game2048()
    clock = pygame.time.Clock()
    
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            
            if event.type == pygame.KEYDOWN and not game.game_over:
                if event.key == pygame.K_UP:
                    game.move(0)
                elif event.key == pygame.K_RIGHT:
                    game.move(1)
                elif event.key == pygame.K_DOWN:
                    game.move(2)
                elif event.key == pygame.K_LEFT:
                    game.move(3)
            
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                # Check if restart button was clicked
                restart_button = pygame.Rect(WINDOW_WIDTH - 2 * BUTTON_WIDTH - BUTTON_PADDING, 30, BUTTON_WIDTH, BUTTON_HEIGHT)
                if restart_button.collidepoint(mouse_pos):
                    game.restart()
                
                # Check if AI button was clicked
                ai_button = pygame.Rect(WINDOW_WIDTH - BUTTON_WIDTH, 30, BUTTON_WIDTH, BUTTON_HEIGHT)
                if ai_button.collidepoint(mouse_pos):
                  ai_controller.toggle()
        
        if ai_controller.is_active:
          ai_controller.make_move()

        draw_grid(game, ai_controller)
        clock.tick(60)


if __name__ == "__main__":
    main()