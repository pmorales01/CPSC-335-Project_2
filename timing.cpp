///////////////////////////////////////////////////////////////////////////////
// timing.cpp
//
// Example code showing how to run each algorithm while measuring
// elapsed times precisely. You should modify this program to gather
// all of your experimental data.
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "poly_exp.hpp"
#include "timer.hpp"

enum class algo_choice { dyn, exh };

const size_t MIN_N{2},
  MAX_PREVIEW_ROWS{20};

// probability of an X cell is 1 / X_PROBABILITY
const int X_PROBABILITY{5};

void print_bar() {
  std::cout << std::string(79, '-') << std::endl;
}

void print_usage() {
  std::cout << "usage:" << std::endl << std::endl
	    << "    timing <ALGO> <N>" << std::endl << std::endl
	    << "where" << std::endl << std::endl
	    << "    <ALGO> is one of: dyn exh" << std::endl
	    << "    <N> is an integer string length (at least " << MIN_N << ")" << std::endl
	    << std::endl
	    << "Example:" << std::endl
	    << "    $ ./timing dyn 5000" << std::endl
	    << std::endl;
}

int main(int argc, char* argv[]) {

  // Exit codes
  const int SUCCESS = 0, USAGE_ERROR = 1;

  // First, try to parse commandline arguments for algo choice and n.
  algo_choice algo;
  size_t n;
  
  if (argc != 3) {
    print_usage();
    return USAGE_ERROR;
  }

  std::string algo_str{argv[1]},
    n_str{argv[2]};

  if (algo_str == "dyn") {
    algo = algo_choice::dyn;
  } else if (algo_str == "exh") {
    algo = algo_choice::exh;
  } else {
    std::cout << "error: unknown <ALGO> \"" << algo_str << "\""
      	      << std::endl << std::endl;
    print_usage();
    return USAGE_ERROR;
  }

  long n_signed;
  try {
    n_signed = std::stol(n_str);
  } catch (std::exception e) {
    std::cout << "error: <N> must be an integer"
	            << std::endl << std::endl;
    print_usage();
    return USAGE_ERROR;
  }
  if (n_signed < 0) {
    std::cout << "error: <N> must be non-negative"
	            << std::endl << std::endl;
    print_usage();
    return USAGE_ERROR;
  }
  n = n_signed;
  if (n < MIN_N) {
    std::cout << "error: <N> must be at least " << MIN_N
	            << std::endl << std::endl;
    print_usage();
    return USAGE_ERROR;
  }

  // n should be initialized
  assert(n >= MIN_N);

  // check maximimum exhaustive search size
  if ((algo == algo_choice::exh) && (n >= 32)) {
    std::cout << "error: exhaustive search is limited to n < 32" << std::endl;
    return USAGE_ERROR;
  }

  // build a grid
  
  // first calculate r and c according to n = r + c - 2
  assert(n >= 2);
  size_t r = (n - 2) / 2,
         c = n - r + 2;
  assert(n == (r + c - 2));
  
  // allocate grid of blanks
  std::vector<std::string> field(r, std::string(c, '.'));

  // add random Xs
  srand(time(0));
  for (size_t i = 0; i < r; ++i) {
    for (size_t j = 0; j < c; ++j) {
      if ((rand() % X_PROBABILITY) == 0) {
        field[i][j] = 'X';
      }
    }
  }
  // ensure that top-left and bottom-right corners are '.', otherwise the
  // input is trivial
  field[0][0] = field[r-1][c-1] = '.';
  
  // prepare to run algorithm with timer
  Timer timer;    // see timer.hpp
  double elapsed; // elapsed time in seconds

  print_bar();
  std::cout << "algo = ";
  switch (algo) {
  case algo_choice::dyn:
    std::cout << "dyn";
    break;
  case algo_choice::exh:
    std::cout << "exh";
    break;
  }
  
  std::cout << std::endl
      	    << "n = " << n << std::endl;

  if (r > MAX_PREVIEW_ROWS) {
    std::cout << "(field too large to print)" << std::endl;
  } else {
    for (auto& row : field) {
      std::cout << row << std::endl;
    }
  }

  // run the algorithm
  // note that there is no input/output while the timer is running
  
  timer.reset();
  
  int solution;
  switch (algo) {
  case algo_choice::dyn:
    solution = algorithms::soccer_dyn_prog(field);
    break;
  case algo_choice::exh:
    solution = algorithms::soccer_exhaustive(field);
    break;
  }

  elapsed = timer.elapsed();

  // end of timing

  std::cout << "solution = " << solution << std::endl;

  std::cout << "elapsed time=" << elapsed << " seconds" << std::endl;

  print_bar();

  return SUCCESS;
}
