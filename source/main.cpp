#include "analysis.hpp"
#include "common.hpp"
#include "database.hpp"
#include "generation.hpp"
#include "printing.hpp"
#include "scoring.hpp"

#include <cstdlib>
#include <iostream>

// flow:
// database d
// d -> analysis a
// d -> generation g
// g -> scoring s
// s -> a
// a -> printing

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "program requires a single file path argument representing "
                 "the configuration file\n";
    std::exit(EXIT_FAILURE);
  }
  auto d{brown_basketball::database::read_database(argv[1])};
  brown_basketball::analysis::accum_state a{d};
  for (std::size_t i_trial{0};
       i_trial < brown_basketball::common::g_k_trial_count; ++i_trial) {
    auto g{brown_basketball::generation::generate_league(
        d, (brown_basketball::generation::flags::BASIC))};
    auto s{brown_basketball::scoring::score_league(
        g, brown_basketball::scoring::return_value_type::TEAM_RANKS)};
    a.add(std::get<static_cast<std::size_t>(
              brown_basketball::scoring::return_value_type::TEAM_RANKS)>(s));
  }
  brown_basketball::printing::print_result(std::cout, a.read());
}
