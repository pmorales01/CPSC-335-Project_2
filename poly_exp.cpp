///////////////////////////////////////////////////////////////////////////////
// poly_exp.cpp
//
// Definitions for two algorithms:
//
// soccer_exhaustive
// soccer_dyn_prog
//
///////////////////////////////////////////////////////////////////////////////

#include "poly_exp.hpp"
#include <cmath>
#include <iostream>

int algorithms::soccer_exhaustive(const std::vector<std::string> field) {

  // Check for invalid input
  if (field.size() == 0 || field[0].size() == 0) {
    throw std::invalid_argument("Field cannot have 0 rows or columns.");
  }

  for (int i = 0; i < field.size(); ++i) {
      if (field[i].size() != field[0].size()) {
        throw std::invalid_argument("Rows are of different lengths.");
      }
  }

  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[0].size(); ++j) {
      if (field[i][j] == '.' || field[i][j] == 'X') {
        continue;
      } else {
        throw std::invalid_argument("Field contains invalid characters.");
      }
    }
  }

  if ((field.size() + field[0].size() - 2) > 31) {
    throw std::invalid_argument("Field requires data type larger than 32 bits.");
  }

  int row = field.size();
  int col = field[0].size();
  int len = row + col - 2;
  int counter = 0;

  if (field[0][0] == 'X' || field[row-1][col-1] == 'X') {
    return 0;
  }

  for (int bits = 0; bits <= (pow(2, len) - 1); ++bits) {
    std::string candidate;
    for (int k = 0; k <= len - 1; ++k) {
      int bit = (bits >> k) & 1;

      if (bit == 1) {
        candidate.push_back('1'); // move down
      } else {
        candidate.push_back('0'); // move right
      }
    }

    // Checks if Candidate Stays in Grid
    int down = 0;
    int right = 0;
    for (int i = 0; i < candidate.size(); ++i) {
      if (candidate[i] == '1') {
        down++;
      } else {
        right++;
      }
    }

    bool in_grid = true;

    if ((down + right) != len) {
      in_grid = false;
      continue;
    }

    // Check if Candidate Crosses an X cell
    bool no_cross = true;

    int r = 0;
    int c = 0;
    for (int i = 0; i < candidate.size(); ++i) {
      if (r < row && c < col && field[r][c] == 'X') {
        no_cross = false;
        break;
      }

      if (candidate[i] == '1') {
        r++;
      } else {
        c++;
      }
    }

    if (down == row - 1 && right == col - 1 && in_grid && no_cross) {
      counter++;
    }
  }

  return counter;
}

int algorithms::soccer_dyn_prog(const std::vector<std::string> field) {
  // Check for invalid input
  if (field.size() == 0 || field[0].size() == 0) {
    throw std::invalid_argument("Field cannot have 0 rows or columns.");
  }

  for (int i = 0; i < field.size(); ++i) {
    if (field[i].size() != field[0].size()) {
      throw std::invalid_argument("Rows are of different lengths.");
    }
  }

  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[0].size(); ++j) {
      if (field[i][j] == '.' || field[i][j] == 'X') {
        continue;
      } else {
        throw std::invalid_argument("Field contains invalid characters.");
      }
    }
  }

  // corner case
  if (field[0][0] == 'X') {
      return 0;
  }

  int row = field.size();
  int col = field[0].size();
  std::vector<std::vector<int>> A(row, std::vector<int>(col));

  // base case
  A[0][0] = 1;

  // general case
  for (int i = 0; i <= row-1; ++i) {
    for (int j = 0; j <= col-1; ++j) {
      if (field[i][j] == 'X') {
        A[i][j] = 0;
        continue;
      }

      if (i == 0 && j == 0) {
        continue;
      }

      int above = 0;
      int left = 0;

      if (i > 0 && field[i-1][j] == '.') {
        above = A[i-1][j];
      }

      if (j > 0 && field[i][j-1] == '.') {
        left = A[i][j-1];
      }

      A[i][j] = above + left;
    }
  }

  return A[row-1][col-1];
}
