#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class ChessBoard {
  friend ostream &operator<<(ostream &out, const ChessBoard &cb) {
    out << endl;
    for (int i = 1; i <= cb.size; i++) {
      for (int j = 1; j <= cb.size; j++) {
        out << (cb.board[i][j] == cb.QUEEN ? "Q" : ".");
      }
      out << endl;
    }

    return out;
  }

public:
  const static int MAX_SIZE = 100;
  const static int QUEEN = -1;
  const static int EMPTY = 0;
  int size;
  int board[MAX_SIZE][MAX_SIZE];
  ChessBoard(int size) : size{size} {
    assert(size < 100);
    reset();
  }
  void reset() {
    for (int i = 1; i <= size; i++) {
      for (int j = 1; j <= size; j++) {
        board[i][j] = EMPTY;
      }
    }
  }
  bool solve() { return placeQueen(1); }
  bool placeQueen(int col) {
    if (col > size) {
      return true;
    }
    for (int row = 1; row <= size; row++) {
      if (isSafe(row, col)) {
        addQueenToBoard(row, col);
        if (placeQueen(col + 1)) {
          return true;
        } else {
          removeQueenFromBoard(row, col);
        }
      }
    }
    return false;
  }
  bool isSafe(int row, int col) const {
    int change[8][2] = {{1, 0}, {-1, 0},  {0, 1},  {0, -1},
                        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    for (int c = 0; c < 8; c++) {
      int i = row + change[c][0];
      int j = col + change[c][1];
      while (i <= size && i >= 1 && j <= size && j >= 1) {
        if (board[i][j] == QUEEN) {
          return false;
        }
        i += change[c][0];
        j += change[c][1];
      }
    }
    return true;
  }

  void addQueenToBoard(int row, int col) {
    assert(board[row][col] == EMPTY);
    board[row][col] = QUEEN;
  }
  void removeQueenFromBoard(int row, int col) {
    assert(board[row][col] == QUEEN);
    board[row][col] = EMPTY;
  }
};

int main() {
  ChessBoard cb(8);
  cb.solve();
  cout << cb << endl;
}