
///////////////////////////////////////////////////////////////////////////////
// poly_exp_test.cpp
//
// Unit tests for the functionality declared in poly_exp.hpp .
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "poly_exp.hpp"

std::vector<std::string> make_field(size_t r, size_t c, char cell = '.') {
  assert((cell == '.') || (cell == 'X'));
  return std::vector<std::string>(r, std::string(c, cell));
}

std::vector<std::string> make_field_n(size_t n) {
  // Create a 1xn field.
  // Solve for c:
  //   n = r + c - 2
  //   let r=1
  //   n = (1) + c - 2
  //   c = n + 1
  auto field =  make_field(1, n + 1);
  size_t r = field.size(),
         c = field[0].size(),
         actual_n = r + c - 2;
  assert(actual_n == n);
  return field;
}

TEST(soccer_exhaustive_invalid_argument, invalid_argument) {

  // valid field
  std::vector<std::string> valid{
    {"...X"},
    {".X.."},
    {"...."}
  };
  const int R = valid.size(),
            C = valid[0].size();

  // accepts valid field
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(valid));

  // zero rows
  EXPECT_THROW(algorithms::soccer_exhaustive( { } ),
               std::invalid_argument);

  // zero colums
  EXPECT_THROW(algorithms::soccer_exhaustive( { {}, {}, {} } ),
               std::invalid_argument);

  // one row is too short
  for (size_t i = 0; i < R; ++i) {
    auto misshapen = valid;
    misshapen[i].pop_back();
    EXPECT_THROW(algorithms::soccer_exhaustive(misshapen),
                 std::invalid_argument);
  }

  // one row is too long
  for (size_t i = 0; i < R; ++i) {
    auto misshapen = valid;
    misshapen[i].push_back('.');
    EXPECT_THROW(algorithms::soccer_exhaustive(misshapen),
                 std::invalid_argument);
  }

  // contains one invalid character
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      for (int ch = 1; ch < 128; ++ch) {
        if ((ch == '.') || (ch == 'X')) {
          continue;
        }
        auto invalid = valid;
        invalid[i][j] = ch;
        EXPECT_THROW(algorithms::soccer_exhaustive(invalid),
                     std::invalid_argument);

      }
    }
  }

  // contains all invalid characters
  for (int ch = 1; ch < 128; ++ch) {
    if ((ch == '.') || (ch == 'X')) {
      continue;
    }
    std::vector<std::string> invalid(10, std::string(12, ch));
    EXPECT_THROW(algorithms::soccer_exhaustive(invalid),
                  std::invalid_argument);

  }

  // accepts n <= 31
  // (stop testing at n=16 because otherewise the tests take too long)
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(0)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(1)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(2)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(3)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(4)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(5)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(6)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(7)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(8)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(9)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(10)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(11)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(12)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(13)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(14)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(15)));
  EXPECT_NO_THROW(algorithms::soccer_exhaustive(make_field_n(16)));

  // rejects > 31
  EXPECT_THROW(algorithms::soccer_exhaustive(make_field_n(32)), std::invalid_argument);
  EXPECT_THROW(algorithms::soccer_exhaustive(make_field_n(33)), std::invalid_argument);
  EXPECT_THROW(algorithms::soccer_exhaustive(make_field_n(34)), std::invalid_argument);
  EXPECT_THROW(algorithms::soccer_exhaustive(make_field_n(35)), std::invalid_argument);
  EXPECT_THROW(algorithms::soccer_exhaustive(make_field_n(1000)), std::invalid_argument);
  EXPECT_THROW(algorithms::soccer_exhaustive(make_field_n(1000000)), std::invalid_argument);
}

TEST(soccer_exhaustive_trivial_instances, trivial_instances) {

  // 1x1 grid, passable
  EXPECT_EQ(1, algorithms::soccer_exhaustive( {"."} ));

  // 2x2 grid, all passable
  EXPECT_EQ(2,
            algorithms::soccer_exhaustive( {"..",
                                            ".."} ));

  // 3x3 grid, all passable
  EXPECT_EQ(6,
            algorithms::soccer_exhaustive( {"...",
                                            "...",
                                            "..."} ));

  // 1x1 grid, impassable
  EXPECT_EQ(0, algorithms::soccer_exhaustive( {"X"} ));

  // 2x2 grid, all impassable
  EXPECT_EQ(0,
            algorithms::soccer_exhaustive( {"XX",
                                            "XX"} ));

  // 3x3 grid, all impassable
  EXPECT_EQ(0,
            algorithms::soccer_exhaustive( {"XXX",
                                            "XXX",
                                            "XXX"} ));

  // slender grid with only one path
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {"..." } ));
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {".",
                                            ".",
                                            "."} ));
}

TEST(soccer_exhaustive_general_instances, general_instances) {

  // 2x2 grid, only one path
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {".X",
                                            ".."} ));
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {"..",
                                            "X."} ));

  // 3x3 grid, only one path
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {"...",
                                            "XX.",
                                            "XX."} ));
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {".XX",
                                            ".XX",
                                            "..."} ));
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {"..X",
                                            "X.X",
                                            "X.."} ));

  // 3x3 grid, dead end
  EXPECT_EQ(0,
            algorithms::soccer_exhaustive( {"...",
                                            "XX.",
                                            "XXX"} ));
  EXPECT_EQ(0,
            algorithms::soccer_exhaustive( {"..X",
                                            "X..",
                                            "XXX"} ));
  EXPECT_EQ(0,
            algorithms::soccer_exhaustive( {"...",
                                            "X.X",
                                            "..X"} ));

  // 4x4 grid, only one path
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {"....",
                                            "XXX.",
                                            "XXX.",
                                            "XXX."} ));
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {"...X",
                                            "XX.X",
                                            "XX.X",
                                            "XX.."} ));
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {"...X",
                                            "X.XX",
                                            "X.XX",
                                            "X..."} ));

  // 4x4 grid, multiple paths
  EXPECT_EQ(2,
            algorithms::soccer_exhaustive( {"....",
                                            ".XX.",
                                            ".XX.",
                                            "...."} ));
  EXPECT_EQ(2,
            algorithms::soccer_exhaustive( {"...X",
                                            ".X.X",
                                            ".X.X",
                                            "...."} ));
  EXPECT_EQ(2,
            algorithms::soccer_exhaustive( {"...X",
                                            "XX.X",
                                            "XX..",
                                            "XX.."} ));
  EXPECT_EQ(2,
            algorithms::soccer_exhaustive( {"..XX",
                                            "X.XX",
                                            "X..X",
                                            "X..."} ));
  EXPECT_EQ(3,
            algorithms::soccer_exhaustive( {"..XX",
                                            "X..X",
                                            "X..X",
                                            "X..."} ));
  EXPECT_EQ(4,
            algorithms::soccer_exhaustive( {"...X",
                                            "X..X",
                                            "X..X",
                                            "X..."} ));

  // 9x8                                          
  EXPECT_EQ(0,
            algorithms::soccer_exhaustive( {"XXXXXXXXX",
                                            "XXXXXXXXX",
                                            "XXXXXXXXX",
                                            "XXXXXXXXX",
                                            "XXXXXXXXX",
                                            "XXXXXXXXX",
                                            "XXXXXXXXX",
                                            "XXXXXXXXX"} ));
  EXPECT_EQ(1,
            algorithms::soccer_exhaustive( {".XXXXXXXX",
                                            "..XXXXXXX",
                                            "X.XXXXXXX",
                                            "X.XXXXXXX",
                                            "X....XXXX",
                                            "XXXX.XXXX",
                                            "XXXX..XXX",
                                            "XXXXX...."} ));
  EXPECT_EQ(4,
            algorithms::soccer_exhaustive( {".........",
                                            "XX.X.X.X.",
                                            "XX.X.X.X.",
                                            "XX.X.X.X.",
                                            "XX.X.X.X.",
                                            "XX.X.X.X.",
                                            "XX.X.X.X.",
                                            "XX......."} ));
  EXPECT_EQ(6,
            algorithms::soccer_exhaustive( {".......XX",
                                            "XXXXXX.XX",
                                            "XXXXXX.XX",
                                            "XXXXXX.XX",
                                            "XXXXXX.XX",
                                            "XXXXXX...",
                                            "XXXXXX...",
                                            "XXXXXX..."} ));
  EXPECT_EQ(6,
            algorithms::soccer_exhaustive( {"...XXXXXX",
                                            "...XXXXXX",
                                            "...XXXXXX",
                                            "XX.XXXXXX",
                                            "XX.XXXXXX",
                                            "XX.XXXXXX",
                                            "XX.XXXXXX",
                                            "XX......."} ));
  EXPECT_EQ(36,
            algorithms::soccer_exhaustive( {"...XXXXXX",
                                            "...XXXXXX",
                                            "....XXXXX",
                                            "XXX.XXXXX",
                                            "XXX.XXXXX",
                                            "XXX......",
                                            "XXXXXX...",
                                            "XXXXXX..."} ));
  EXPECT_EQ(102,
            algorithms::soccer_exhaustive( {"......X.X",
                                            "X........",
                                            "...X...X.",
                                            "..X....X.",
                                            ".X....X..",
                                            "....X....",
                                            "..X.....X",
                                            "........."} ));
}

TEST(soccer_dyn_prog_invalid_argument, invalid_argument) {

  // valid field
  std::vector<std::string> valid{
    {"...X"},
    {".X.."},
    {"...."}
  };
  const int R = valid.size(),
            C = valid[0].size();

  // accepts valid field
  EXPECT_NO_THROW(algorithms::soccer_dyn_prog(valid));

  // zero rows
  EXPECT_THROW(algorithms::soccer_dyn_prog( { } ),
               std::invalid_argument);

  // zero colums
  EXPECT_THROW(algorithms::soccer_dyn_prog( { {}, {}, {} } ),
               std::invalid_argument);

  // one row is too short
  for (size_t i = 0; i < R; ++i) {
    auto misshapen = valid;
    misshapen[i].pop_back();
    EXPECT_THROW(algorithms::soccer_dyn_prog(misshapen),
                 std::invalid_argument);
  }

  // one row is too long
  for (size_t i = 0; i < R; ++i) {
    auto misshapen = valid;
    misshapen[i].push_back('.');
    EXPECT_THROW(algorithms::soccer_dyn_prog(misshapen),
                 std::invalid_argument);
  }

  // contains one invalid character
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      for (int ch = 1; ch < 128; ++ch) {
        if ((ch == '.') || (ch == 'X')) {
          continue;
        }
        auto invalid = valid;
        invalid[i][j] = ch;
        EXPECT_THROW(algorithms::soccer_dyn_prog(invalid),
                     std::invalid_argument);

      }
    }
  }

  // contains all invalid characters
  for (int ch = 1; ch < 128; ++ch) {
    if ((ch == '.') || (ch == 'X')) {
      continue;
    }
    std::vector<std::string> invalid(10, std::string(12, ch));
    EXPECT_THROW(algorithms::soccer_dyn_prog(invalid),
                  std::invalid_argument);

  }
}

TEST(soccer_dyn_prog_trivial_instances, trivial_instances) {

  // 1x1 grid, passable
  EXPECT_EQ(1, algorithms::soccer_dyn_prog( {"."} ));

  // 2x2 grid, all passable
  EXPECT_EQ(2,
            algorithms::soccer_dyn_prog( {"..",
                                            ".."} ));

  // 3x3 grid, all passable
  EXPECT_EQ(6,
            algorithms::soccer_dyn_prog( {"...",
                                          "...",
                                          "..."} ));

  // 1x1 grid, impassable
  EXPECT_EQ(0, algorithms::soccer_dyn_prog( {"X"} ));

  // 2x2 grid, all impassable
  EXPECT_EQ(0,
            algorithms::soccer_dyn_prog( {"XX",
                                          "XX"} ));

  // 3x3 grid, all impassable
  EXPECT_EQ(0,
            algorithms::soccer_dyn_prog( {"XXX",
                                          "XXX",
                                          "XXX"} ));

  // slender grid with only one path
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {"..." } ));
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {".",
                                          ".",
                                          "."} ));
}

TEST(soccer_dyn_prog_general_instances, general_instances) {

  // 2x2 grid, only one path
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {".X",
                                          ".."} ));
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {"..",
                                          "X."} ));

  // 3x3 grid, only one path
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {"...",
                                          "XX.",
                                          "XX."} ));
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {".XX",
                                          ".XX",
                                          "..."} ));
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {"..X",
                                          "X.X",
                                          "X.."} ));

  // 3x3 grid, dead end
  EXPECT_EQ(0,
            algorithms::soccer_dyn_prog( {"...",
                                          "XX.",
                                          "XXX"} ));
  EXPECT_EQ(0,
            algorithms::soccer_dyn_prog( {"..X",
                                          "X..",
                                          "XXX"} ));
  EXPECT_EQ(0,
            algorithms::soccer_dyn_prog( {"...",
                                          "X.X",
                                          "..X"} ));

  // 4x4 grid, only one path
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {"....",
                                          "XXX.",
                                          "XXX.",
                                          "XXX."} ));
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {"...X",
                                          "XX.X",
                                          "XX.X",
                                          "XX.."} ));
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {"...X",
                                            "X.XX",
                                            "X.XX",
                                            "X..."} ));

  // 4x4 grid, multiple paths
  EXPECT_EQ(2,
            algorithms::soccer_dyn_prog( {"....",
                                          ".XX.",
                                          ".XX.",
                                          "...."} ));
  EXPECT_EQ(2,
            algorithms::soccer_dyn_prog( {"...X",
                                          ".X.X",
                                          ".X.X",
                                          "...."} ));
  EXPECT_EQ(2,
            algorithms::soccer_dyn_prog( {"...X",
                                            "XX.X",
                                            "XX..",
                                            "XX.."} ));
  EXPECT_EQ(2,
            algorithms::soccer_dyn_prog( {"..XX",
                                          "X.XX",
                                          "X..X",
                                          "X..."} ));
  EXPECT_EQ(3,
            algorithms::soccer_dyn_prog( {"..XX",
                                          "X..X",
                                          "X..X",
                                          "X..."} ));
  EXPECT_EQ(4,
            algorithms::soccer_dyn_prog( {"...X",
                                          "X..X",
                                          "X..X",
                                          "X..."} ));

  // 9x8                                          
  EXPECT_EQ(0,
            algorithms::soccer_dyn_prog( {"XXXXXXXXX",
                                          "XXXXXXXXX",
                                          "XXXXXXXXX",
                                          "XXXXXXXXX",
                                          "XXXXXXXXX",
                                          "XXXXXXXXX",
                                          "XXXXXXXXX",
                                          "XXXXXXXXX"} ));
  EXPECT_EQ(1,
            algorithms::soccer_dyn_prog( {".XXXXXXXX",
                                          "..XXXXXXX",
                                          "X.XXXXXXX",
                                          "X.XXXXXXX",
                                          "X....XXXX",
                                          "XXXX.XXXX",
                                          "XXXX..XXX",
                                          "XXXXX...."} ));
  EXPECT_EQ(4,
            algorithms::soccer_dyn_prog( {".........",
                                          "XX.X.X.X.",
                                          "XX.X.X.X.",
                                          "XX.X.X.X.",
                                          "XX.X.X.X.",
                                          "XX.X.X.X.",
                                          "XX.X.X.X.",
                                          "XX......."} ));
  EXPECT_EQ(6,
            algorithms::soccer_dyn_prog( {".......XX",
                                          "XXXXXX.XX",
                                          "XXXXXX.XX",
                                          "XXXXXX.XX",
                                          "XXXXXX.XX",
                                          "XXXXXX...",
                                          "XXXXXX...",
                                          "XXXXXX..."} ));
  EXPECT_EQ(6,
            algorithms::soccer_dyn_prog( {"...XXXXXX",
                                          "...XXXXXX",
                                          "...XXXXXX",
                                          "XX.XXXXXX",
                                          "XX.XXXXXX",
                                          "XX.XXXXXX",
                                          "XX.XXXXXX",
                                          "XX......."} ));
  EXPECT_EQ(36,
            algorithms::soccer_dyn_prog( {"...XXXXXX",
                                          "...XXXXXX",
                                          "....XXXXX",
                                          "XXX.XXXXX",
                                          "XXX.XXXXX",
                                          "XXX......",
                                          "XXXXXX...",
                                          "XXXXXX..."} ));
  EXPECT_EQ(102,
            algorithms::soccer_dyn_prog( {"......X.X",
                                          "X........",
                                          "...X...X.",
                                          "..X....X.",
                                          ".X....X..",
                                          "....X....",
                                          "..X.....X",
                                          "........."} ));
}

TEST(soccer_dyn_prog_large_instances, large_instances) {

  // Confirm that soccer_dyn_prog takes polynomial time.
  // If it takes exponential time, these will time out.

  // 100x100, impassible
  {
    std::vector<std::string> field(100, std::string(100, 'X'));
    field[0][0] = field[99][99] = '.';
    EXPECT_EQ(0, algorithms::soccer_dyn_prog(field));
  }

  // 100x100, passable
  {
    std::vector<std::string> field(100, std::string(100, '.'));
    // do not test the return value because it may overflow
    EXPECT_NO_THROW(algorithms::soccer_dyn_prog(field));
  }

  // 1000x1000, impassible
  {
    std::vector<std::string> field(1000, std::string(1000, 'X'));
    field[0][0] = field[999][999] = '.';
    EXPECT_EQ(0, algorithms::soccer_dyn_prog(field));
  }

  // 1000x1000, passable
  {
    std::vector<std::string> field(1000, std::string(1000, '.'));
    // do not test the return value because it may overflow
    EXPECT_NO_THROW(algorithms::soccer_dyn_prog(field));
  }
}
