class TicTacToe:
    board = {}
    dim = 0
    size = 0
    max_size = 0
    symbols = ['X', 'O']
    players = [symbols[0], symbols[1]]
    user_player = 1

    def __init__(self, dim, user_player=1):
        self._initialize(dim, user_player)

    def _initialize(self, dim, user_player):
        self.board = {}
        self.dim = dim
        self.size = 0
        self.max_size = self.dim * self.dim
        self.user_player = user_player

    def reset_game(self, dim, user_player):
        self._initialize(dim, user_player)

    def get_char(self, index):
        return self.board[index]

    def set_char(self, index, ch):
        if ch not in self.symbols:
            raise ValueError("Character {} not an accepted symbol".format(ch))

        if index < 0 or index >= self.max_size:
            raise ValueError("Index not within bounds")

        if index not in self.board:
            self.board[index] = ch
        else:
            raise ValueError("Already have a move at this location")

        # success
        self.size += 1

    def set(self, index, player):
        if 1 <= player <= len(self.players):
            self.set_char(index, self.players[player-1])
        else:
            raise ValueError('Invalid player: number of players is {}'.format(len(self.players)))

    def run():
        print "Running..."

if __name__ == "__main__":
    game = TicTacToe(3)
    game.run