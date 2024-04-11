import time


def cached(func):
    last_one = []
    cache = {}
    def my_wrapper(*args):
        if args not in cache:
            res = func(*args)
            if len(cache) == 3:
                old_one = last_one.pop(0)
                cache.pop(old_one)
            last_one.append(args)
            cache[args] = res
        else:
            last_one.remove(args)
            last_one.append(args)
            res = cache[args]
        return res
    return my_wrapper


class GameOfLife:
    def __init__(self, board):
        self.board = board

    def move(self):
        rows = len(self.board)
        cols = len(self.board[0])

        new_board = []
        for i in range(rows):
            new_row = []
            for j in range(cols):
                live_neighbors = 0
                neighbors = [(i - 1, j - 1), (i - 1, j), (i - 1, j + 1), (i, j - 1), (i, j + 1), (i + 1, j - 1),
                            (i + 1, j), (i + 1, j + 1)]
                for x, y in neighbors:
                    if 0 <= x < rows and 0 <= y < cols and self.board[x][y] == 'x':
                        live_neighbors += 1
                if live_neighbors == 3:
                    new_row.append('x')
                elif self.board[i][j] == 'x' and (live_neighbors == 2 or live_neighbors == 3):
                    new_row.append('x')
                else:
                    new_row.append('.')
            new_board.append(tuple(new_row))

        return GameOfLife(tuple(new_board))

    def alive(self):
        return sum(row.count('x') for row in self.board)

    def dead(self):
        return sum(row.count('.') for row in self.board)

    def __repr__(self):
        rows = []
        for row in self.board:
            rows.append(' '.join(row))
        return '\n'.join(rows)


def play_game(game, n):
    for i in range(n):
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
