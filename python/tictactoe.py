class TicTacToe:
    def __init(dim, userPlayer = 1):
        _initialize(dim, userPlayer)
    
    def _intialize(dim, userPlayer):
        self.board = {}
        self.dim = dim
        self.maxsize = self.dim * self.dim
        self.size = 0
        self.symbols = ['X', '0']
        self.players = [self.symbols[0], self.symbols[1]]
        self.userPlayer = userPlayer

    def resetGame(dim, userPlayer):
       _initialize(dim, userPlayer) 

    def move(index, ch):
        # check types of index and ch are int and char
        #if (type(index)
        if ch not in self.symbols:
            throw "Character " + ch + " not an accepted symbol"

        if index not a int:
            throw "Index not an integer"
        
        if index < 0 or index >= self.maxsize:
            throw "Index not within bounds"

        if !board.try_set(index, ch):
            throw ""

        # success
        self.size += 1

    def move(index, player):
        if player >= 1 and player <= self.players.size:
            move(index, self.players[player-1]
        else:
            throw ""

    def run():
        
        
