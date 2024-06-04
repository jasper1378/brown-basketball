#include "analysis1.hpp"
#include "analysis2.hpp"
#include "common.hpp"
#include "database.hpp"
#include "generation.hpp"
#include "printing1.hpp"
#include "printing2.hpp"
#include "scoring.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <utility>

int main(int argc, char *argv[]) {
  using namespace brown_basketball;
  if (argc != 2) {
    std::cerr << "program requires a single file path argument representing "
                 "the configuration file\n";
    std::exit(EXIT_FAILURE);
  }
  auto d{database::read_database(argv[1])};
  analysis1::accum_state a1{d};
  analysis2::accum_state a2{};
  for (std::size_t i_trial{0}; i_trial < common::g_k_trial_count; ++i_trial) {
    // auto g{generation::generate_league(d, (generation::flags::draft_aware |
    //                                        generation::flags::position_aware))};
    auto g{generation::generate_league(d, generation::flags::basic)};
    auto s_team_ranks{
        scoring::score_league(g, scoring::return_value_type::team_ranks)};
    a1.add(std::get<static_cast<std::size_t>(
               scoring::return_value_type::team_ranks)>(s_team_ranks));
    auto s_stats{std::get<static_cast<std::size_t>(
        scoring::return_value_type::team_stats)>(
        scoring::score_league(g, scoring::return_value_type::team_stats))};
    auto s_ranks{std::get<static_cast<std::size_t>(
        scoring::return_value_type::team_ranks)>(
        scoring::score_league(g, scoring::return_value_type::team_ranks))};
    a2.add(std::make_pair(s_stats, s_ranks));
    if ((i_trial % (common::g_k_trial_count / 100)) == 0) {
      std::cerr << '\r'
                << static_cast<int>(
                       std::round(i_trial * 100.0 / common::g_k_trial_count))
                << '%' << std::flush;
    }
  }
  std::cerr << '\r';
  printing1::print_result(std::cout, a1.read());
  std::cout << '\n';
  printing2::print_result(std::cout, a2.read());
  return 0;
}
