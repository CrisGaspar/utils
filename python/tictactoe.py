class TicTacToe:
    board = {}
    dim = 0
    size = 0
    maxsize = 0
    symbols = ['X', '0']
    players = [symbols[0], symbols[1]]
    user_player = 1

    def __init__(self, dim, user_player=1):
        self._initialize(dim, user_player)

    def _initialize(self, dim, user_player):
        self.board = {}
        self.dim = dim
        self.size = 0
        self.maxsize = self.dim * self.dim
        self.user_player = user_player

    def reset_game(self, dim, user_player):
        self._initialize(dim, user_player)

    def move(self, index, ch):
        """

        :type index: int
        """
        if ch not in self.symbols:
            raise ValueError("Character " + ch + " not an accepted symbol")

        if isinstance(index, int):
            raise TypeError("Index not an integer")

        if index < 0 or index >= self.maxsize:
            raise ValueError("Index not within bounds")

        if index not in self.board:
            self.board[index] = ch
            raise ValueError("Already have a move at this location")

        # success
        self.size += 1

    def move(self, index, player):
        if player >= 1 and player <= self.players.size:
            self.move(index, self.players[player-1])
        else:
            raise ValueError("Index out of bounds. Move aborted")

    def run():
        print("Running...")



if __name__ == "__main__":
    game = TicTacToe(3)
    game.run
