#include "analysis1.hpp"
#include "analysis2.hpp"
#include "common.hpp"
#include "database.hpp"
#include "generation.hpp"
#include "printing1.hpp"
#include "printing2.hpp"
#include "scoring.hpp"

#include "bits-and-bytes/timer/timer.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>

int main(int argc, char *argv[]) {
  using namespace brown_basketball;
  if (argc != 2) {
    std::cerr << "program requires a single file path argument representing "
                 "the configuration file\n";
    std::exit(EXIT_FAILURE);
  }
  std::array<decltype(std::declval<bits_and_bytes::timer<
                          std::chrono::duration<double, std::milli>>>()
                          .elapsed()),
             3>
      timings{};
  bits_and_bytes::timer<std::chrono::duration<double, std::milli>> timer{};
  auto d{database::read_database(argv[1])};
  analysis1::accum_state a1{d};
  analysis2::accum_state a2{};
  timings[0] = timer.elapsed();
  timer.reset();
  for (std::size_t i_trial{0}; i_trial < common::k_trial_count; ++i_trial) {
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
    {
      double percent_completed{static_cast<double>(i_trial) /
                               common::k_trial_count};
      if ((i_trial % (common::k_trial_count / 100)) == 0) {
        std::cerr << "\33[2K\r"
                  << static_cast<int>(std::round(percent_completed * 100))
                  << "% completed, "
                  << std::chrono::hh_mm_ss{(
                         ((1 - percent_completed) / percent_completed) *
                         timer.elapsed())}
                  << " remaining" << std::flush;
      }
    }
  }
  timings[1] = timer.elapsed();
  timer.reset();
  printing1::print_result(std::cout, a1.read());
  std::cout << '\n';
  printing2::print_result(std::cout, a2.read());
  timings[2] = timer.elapsed();
  timer.reset();
  std::cerr << "\rcompleted in " << std::chrono::hh_mm_ss{([&timings]() {
    decltype(timings)::value_type sum{};
    for (const auto &i : timings) {
      sum += i;
    }
    return sum;
  }())} << '\n';
  return 0;
}
