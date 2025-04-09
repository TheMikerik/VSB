import pygame, sys, random
import importlib

# Configuration constants
SIZE = 4                       # The grid is 4x4
TILE_SIZE = 100                # Pixel size of each tile
TILE_MARGIN = 10               # Margin between tiles
WIDTH = SIZE * TILE_SIZE + (SIZE + 1) * TILE_MARGIN
HEIGHT = WIDTH + 100           # Extra space at the bottom for the score display

BACKGROUND_COLOR = (187, 173, 160)
EMPTY_COLOR = (205, 193, 180)
# Mapping tile values to colors (if a value isn't in the map, it defaults to EMPTY_COLOR)
TILE_COLORS = {
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
TEXT_COLOR = (119, 110, 101)
SCORE_COLOR = (255, 255, 255)
FONT_NAME = 'freesansbold.ttf'

class Game2048:
    def __init__(self, solver=None):
        pygame.init()
        self.screen = pygame.display.set_mode((WIDTH, HEIGHT))
        pygame.display.set_caption("2048")
        self.clock = pygame.time.Clock()
        self.font = pygame.font.Font(FONT_NAME, 40)
        self.score_font = pygame.font.Font(FONT_NAME, 30)
        self.solver = solver
        self.auto_play = solver is not None
        self.reset()

    def reset(self):
        """Initialize a new game board and score."""
        self.board = [[0] * SIZE for _ in range(SIZE)]
        self.score = 0
        self.add_tile()
        self.add_tile()

    def add_tile(self):
        """Add a new tile with value 2 (90% chance) or 4 (10% chance) on a random empty cell."""
        empty_tiles = [(i, j) for i in range(SIZE) for j in range(SIZE) if self.board[i][j] == 0]
        if empty_tiles:
            i, j = random.choice(empty_tiles)
            self.board[i][j] = 4 if random.random() < 0.1 else 2

    def move_left(self):
        """Slide and merge the board to the left."""
        moved = False
        new_board = []
        for row in self.board:
            original = list(row)
            merged = self.merge(row)
            new_board.append(merged)
            if merged != original:
                moved = True
        self.board = new_board
        return moved

    def move_right(self):
        """Slide and merge the board to the right."""
        moved = False
        new_board = []
        for row in self.board:
            original = list(row)
            # Reverse row, merge as if moving left, then reverse back
            reversed_row = list(reversed(row))
            merged = self.merge(reversed_row)
            merged = list(reversed(merged))
            new_board.append(merged)
            if merged != original:
                moved = True
        self.board = new_board
        return moved

    def move_up(self):
        """Slide and merge the board upward."""
        # Transpose the board so columns become rows, then move left
        self.board = self.transpose(self.board)
        moved = self.move_left()
        self.board = self.transpose(self.board)
        return moved

    def move_down(self):
        """Slide and merge the board downward."""
        # Transpose the board so columns become rows, then move right
        self.board = self.transpose(self.board)
        moved = self.move_right()
        self.board = self.transpose(self.board)
        return moved

    def merge(self, row):
        """
        Merge a single row by sliding non-zero numbers to the left and combining
        adjacent equal numbers.
        """
        # Remove zeros
        new_row = [num for num in row if num != 0]
        merged_row = []
        skip = False
        for i in range(len(new_row)):
            if skip:
                skip = False
                continue
            # Merge if the next number is identical
            if i + 1 < len(new_row) and new_row[i] == new_row[i + 1]:
                merged_value = new_row[i] * 2
                self.score += merged_value
                merged_row.append(merged_value)
                skip = True
            else:
                merged_row.append(new_row[i])
        # Fill the rest of the row with zeros
        merged_row += [0] * (SIZE - len(merged_row))
        return merged_row

    def transpose(self, board):
        """Transpose the board (swap rows and columns)."""
        return [list(row) for row in zip(*board)]

    def game_over(self):
        """Check whether there are no possible moves left."""
        for i in range(SIZE):
            for j in range(SIZE):
                if self.board[i][j] == 0:
                    return False
                if j < SIZE - 1 and self.board[i][j] == self.board[i][j + 1]:
                    return False
                if i < SIZE - 1 and self.board[i][j] == self.board[i + 1][j]:
                    return False
        return True

    def draw(self):
        """Draw the game board, tiles, and score."""
        self.screen.fill(BACKGROUND_COLOR)
        # Draw score background
        pygame.draw.rect(self.screen, (143, 122, 102), (0, WIDTH, WIDTH, HEIGHT - WIDTH))
        score_surface = self.score_font.render(f"Score: {self.score}", True, SCORE_COLOR)
        self.screen.blit(score_surface, (TILE_MARGIN, WIDTH + 10))

        for i in range(SIZE):
            for j in range(SIZE):
                value = self.board[i][j]
                rect_x = TILE_MARGIN + j * (TILE_SIZE + TILE_MARGIN)
                rect_y = TILE_MARGIN + i * (TILE_SIZE + TILE_MARGIN)
                tile_rect = pygame.Rect(rect_x, rect_y, TILE_SIZE, TILE_SIZE)
                color = TILE_COLORS.get(value, EMPTY_COLOR) if value != 0 else EMPTY_COLOR
                pygame.draw.rect(self.screen, color, tile_rect, border_radius=8)
                if value != 0:
                    text_surface = self.font.render(str(value), True, TEXT_COLOR)
                    text_rect = text_surface.get_rect(center=tile_rect.center)
                    self.screen.blit(text_surface, text_rect)

        pygame.display.update()

    def run(self):
        running = True
        while running:
            pygame.event.pump()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    pygame.quit()
                    sys.exit()

            moved = False

            if self.auto_play:
                move = self.solver.get_move(self.board)
                if move == 'left':
                    moved = self.move_left()
                elif move == 'right':
                    moved = self.move_right()
                elif move == 'up':
                    moved = self.move_up()
                elif move == 'down':
                    moved = self.move_down()

                if moved:
                    self.add_tile()
                    self.draw()
                    pygame.display.update()

                if self.game_over():
                    print(f"FINAL_SCORE: {self.score}")
                    running = False
            else:
                # ruční ovládání přes šipky
                for event in pygame.event.get():
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_LEFT:
                            moved = self.move_left()
                        elif event.key == pygame.K_RIGHT:
                            moved = self.move_right()
                        elif event.key == pygame.K_UP:
                            moved = self.move_up()
                        elif event.key == pygame.K_DOWN:
                            moved = self.move_down()
                        if moved:
                            self.add_tile()
                            self.draw()

            self.draw()

if __name__ == "__main__":
    solver = None
    if len(sys.argv) > 1:
        solver_module_name = sys.argv[1].replace('.py', '').replace('/', '.')
        solver = importlib.import_module(solver_module_name)
    game = Game2048(solver=solver)
    game.run()

