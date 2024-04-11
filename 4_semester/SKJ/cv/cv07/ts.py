import time


def cached(func):
    last_used = []
    cache = {}

    def wrapper(*args):
        if args not in cache:
            result = func(*args)
            if len(cache) == 3:
                oldest = last_used.pop(0)
                del cache[oldest]
            last_used.append(args)
            cache[args] = result
        else:
            last_used.remove(args)
            last_used.append(args)
            result = cache[args]
        return result

    return wrapper


class GameOfLife:
    def __init__(self, board):
        self.board = board

    def move(self):
        rows, cols = len(self.board), len(self.board[0])

        new_board = []
        for i in range(rows):
            new_row = []
            for j in range(cols):
                live_neighbors = self.count_live_neighbors(i, j, rows, cols)
                new_row.append(self.get_new_cell_state(i, j, live_neighbors))
            new_board.append(tuple(new_row))

        return GameOfLife(tuple(new_board))

    def count_live_neighbors(self, i, j, rows, cols):
        count = 0
        for x in range(max(0, i - 1), min(rows, i + 2)):
            for y in range(max(0, j - 1), min(cols, j + 2)):
                if (x, y) != (i, j) and self.board[x][y] == 'x':
                    count += 1
        return count

    def get_new_cell_state(self, i, j, live_neighbors):
        if live_neighbors == 3:
            return 'x'
        elif self.board[i][j] == 'x' and live_neighbors in [2, 3]:
            return 'x'
        else:
            return '.'

    def alive(self):
        return sum(row.count('x') for row in self.board)

    def dead(self):
        return sum(row.count('.') for row in self.board)

    def __repr__(self):
        return '\n'.join([' '.join(row) for row in self.board])


def play_game(game, n):
    for _ in range(n):
        print(game)
        game = game.move()
        time.sleep(0.25)


if __name__ == "__main__":
    play_game(GameOfLife((
        ('.', '.', '.'),
        ('.', 'x', '.'),
        ('.', 'x', '.'),
        ('.', 'x', '.'),
        ('.', '.', '.'),
    )), 10)
