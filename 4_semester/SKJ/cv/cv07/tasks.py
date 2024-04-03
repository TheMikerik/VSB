def cached(func):
    """
    Create a decorator that caches up to 3 function results, based on the same parameter values.

    When `f` is called with the same parameter values that are already in the cache, return the
    stored result associated with these parameter values. You can assume that `f` receives only
    positional arguments (you can ignore keyword arguments).

    When `f` is called with new parameter values, forget the oldest accessed result in the cache
    if the cache is already full.

    Example:
        @cached
        def fn(a, b):
            return a + b # imagine an expensive computation

        fn(1, 2) == 3 # computed
        fn(1, 2) == 3 # returned from cache, `a + b` is not executed
        fn(3, 4) == 7 # computed
        fn(3, 5) == 8 # computed
        fn(3, 6) == 9 # computed, (1, 2) was now forgotten
        fn(1, 2) == 3 # computed again, (3, 4) was now forgotten
    """
    pass

class GameOfLife:
    """
    Implement "Game of life" (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

    The game board will be represented with nested tuples, where '.'
    marks a dead cell and 'x' marks a live cell. Cells that are out of bounds of the board are
    assumed to be dead.

    Try some patterns from wikipedia + the provided tests to test the functionality.

    The GameOfLife objects should be immutable, i.e. the move method will return a new instance
    of GameOfLife.

    Example:
        game = GameOfLife((
            ('.', '.', '.'),
            ('.', 'x', '.'),
            ('.', 'x', '.'),
            ('.', 'x', '.'),
            ('.', '.', '.')
        ))
        game.alive()    # 3
        game.dead()     # 12
        x = game.move() # 'game' doesn't change
        # x.board:
        (
            ('.', '.', '.'),
            ('.', '.', '.'),
            ('x', 'x', 'x'),
            ('.', '.', '.'),
            ('.', '.', '.')
        )

        str(x)
        ...\n
        ...\n
        xxx\n
        ...\n
        ...\n
    """

    def __init__(self, board):
        self.board = board
        pass

    def move(self):
        """
        Simulate one iteration of the game and return a new instance of GameOfLife containing
        the new board state.
        """
        pass

    def alive(self):
        count = 0
        for row in self.board:
            count += row.count('x')

        return count

    def dead(self):
        count = 0
        for row in self.board:
            count += row.count('.')

        return count

    def __repr__(self):
        repr_str = ""
        for row in self.board:
            repr_str += "".join(row) + "\n"
        return repr_str.rstrip("\n")


def play_game(game, n):
    """
    You can use this function to render the game for n iterations
    """
    for i in range(n):
        print(game)
        game = game.move()
        time.sleep(0.25)  # sleep to see the output


# this code will only be executed if you run `python tasks.py`
# it will not be executed when tasks.py is imported
if __name__ == "__main__":
    play_game(GameOfLife((
        ('.', '.', '.'),
        ('.', 'x', '.'),
        ('.', 'x', '.'),
        ('.', 'x', '.'),
        ('.', '.', '.'),
    )), 10)