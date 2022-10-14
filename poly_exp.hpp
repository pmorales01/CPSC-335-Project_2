///////////////////////////////////////////////////////////////////////////////
// poly_exp.hpp
//
// Declarations for two algorithms:
//
// soccer_exhaustive
// soccer_dyn_prog
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>

namespace algorithms {

  // Each of these functions solves the *soccer opponent avoidance problem*.
  //
  // soccer_exhaustive uses exhaustive search and takes exponential time.
  // soccer_dyn_prog uses dynamic programming and takes quadratic time.
  //
  // field is a vector of strings that defines a play field.
  //   So field[i] is row i, and field[i][j] is the cell at row i, column j.
  //   Each character must be '.' (passable) or 'X' (impassable).
  //   The number of rows and columns must both be positive.
  //   All rows must have the same number of columns.
  //
  // Returns the number of valid paths that start at the top-left corner at
  // (0, 0) and end at the bottom-right corner.
  //
  // Throws std::invalid_argument if field is invalid (empty, misshapen, or
  // contains invalid characters).
  //
  // In addition, soccer_exhaustive throws std::invalid_argument if n > 31,
  // where n = r + c - 2.

  int soccer_exhaustive(const std::vector<std::string> field);

  int soccer_dyn_prog(const std::vector<std::string> field);

}
