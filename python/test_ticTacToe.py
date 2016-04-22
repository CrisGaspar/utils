from unittest import TestCase

from tictactoe import TicTacToe


class TestTicTacToe(TestCase):
    def test_set_char(self):
        t = TicTacToe(3)
        i = 2
        ch = 'O'
        t.set_char(i, ch)
        self.assertTrue(t.get_char(i) == ch)

    def test_set_invalid_char(self):
        t = TicTacToe(3)
        i = 2
        ch = '0'
        with self.assertRaises(Exception):
            t.set_char(i, ch)

    def test_set_char_not_a_char(self):
        t = TicTacToe(3)
        with self.assertRaises(Exception):
            t.set_char(2, 2)

    def test_set_char_not_an_index(self):
        t = TicTacToe(3)
        with self.assertRaises(Exception):
            t.set_char('x', 'X')

    def test_set_char_out_of_bounds(self):
        t = TicTacToe(3)
        with self.assertRaises(ValueError):
            t.set_char(9, 'X')

    def test_set_char_twice(self):
        t = TicTacToe(3)
        i = 2
        ch = 'O'
        t.set_char(i, ch)
        self.assertTrue(t.get_char(i) == ch)

        with self.assertRaises(ValueError):
            t.set_char(i, ch)

    def test_reset_game(self):
        t = TicTacToe(3)
        dim = 5
        user = 2
        t.reset_game(dim, user)
        self.assertTrue(t.board == {} and t.dim == dim
                        and t.size == 0 and t.max_size == dim * dim
                        and t.user_player == user)
    def test_run(self):
        t = TicTacToe(3)
        t.run

    def test_set(self):
        t = TicTacToe(3)
        t.set(5, 1)
        t.set(3, 2)
        self.assertTrue(t.get_char(5) == 'X' and t.get_char(3) == 'O')

    def test_set_invalid_player(self):
        t = TicTacToe(3)
        with self.assertRaises(ValueError):
            t.set(5, 3)
