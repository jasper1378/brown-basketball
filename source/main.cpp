#include "analysis.hpp"
#include "common.hpp"
#include "database.hpp"
#include "generation.hpp"
#include "misc.hpp"
#include "printing.hpp"
#include "scoring.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

// flow:
// database d
// d -> analysis a
// d -> generation g
// g -> scoring s
// s -> a
// a -> printing

int main_main(int argc, char *argv[]) {
  using namespace brown_basketball;
  if (argc != 2) {
    std::cerr << "program requires a single file path argument representing "
                 "the configuration file\n";
    std::exit(EXIT_FAILURE);
  }
  auto d{database::read_database(argv[1])};
  analysis::accum_state a{d};
  for (std::size_t i_trial{0}; i_trial < common::g_k_trial_count; ++i_trial) {
    auto g{generation::generate_league(d, (generation::flags::DRAFT_AWARE |
                                           generation::flags::POSITION_AWARE))};
    auto s{scoring::score_league(g, scoring::return_value_type::TEAM_RANKS)};
    a.add(std::get<static_cast<std::size_t>(
              scoring::return_value_type::TEAM_RANKS)>(s));
  }
  printing::print_result(std::cout, a.read());
  return 0;
}

// ALT

#define MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(_cat)                              \
  do {                                                                         \
    auto begin{team._cat.begin()};                                             \
    auto end{team._cat.end()};                                                 \
    double mean{misc::mean<double>(begin, end)};                               \
                                                                               \
    std::cout << mean << separator;                                            \
    std::cout << *std::min_element(begin, end) << separator;                   \
    std::cout << *std::max_element(begin, end) << separator;                   \
    std::cout << misc::standard_deviation(begin, end, mean) << separator;      \
  } while (0);

#define MACRO_PRINT_TEAM(_cat)                                                 \
  do {                                                                         \
    for (std::size_t i_team{0}; i_team < data._cat.size(); ++i_team) {         \
      std::cout << #_cat << "_team_" << (i_team + 1) << separator;             \
      print_team_stats(data._cat[i_team]);                                     \
      std::cout << '\n';                                                       \
    }                                                                          \
  } while (0);

template <typename T> struct categories {
  T points;
  T rebounds;
  T assists;
  T steals;
  T blocks;
  T threes;
  T field_goals;
  T free_throws;
};
struct stats {
  std::vector<double> points;
  std::vector<double> rebounds;
  std::vector<double> assists;
  std::vector<double> steals;
  std::vector<double> blocks;
  std::vector<double> threes;
  std::vector<double> field_goals;
  std::vector<double> free_throws;
};
using data_t =
    categories<std::array<stats, brown_basketball::common::g_k_league_size>>;

int main_alt(int argc, char *argv[]) {
  using namespace brown_basketball;
  if (argc != 2) {
    std::cerr << "program requires a single file path argument representing "
                 "the configuration file\n";
    std::exit(EXIT_FAILURE);
  }
  data_t data;
  for (std::size_t i{0}; i < data.points.size(); ++i) {
    data.points[i].points.resize(brown_basketball::common::g_k_trial_count);
    data.points[i].rebounds.resize(brown_basketball::common::g_k_trial_count);
    data.points[i].assists.resize(brown_basketball::common::g_k_trial_count);
    data.points[i].steals.resize(brown_basketball::common::g_k_trial_count);
    data.points[i].blocks.resize(brown_basketball::common::g_k_trial_count);
    data.points[i].threes.resize(brown_basketball::common::g_k_trial_count);
    data.points[i].field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    data.points[i].free_throws.resize(
        brown_basketball::common::g_k_trial_count);
  }
  for (std::size_t i{0}; i < data.rebounds.size(); ++i) {
    data.rebounds[i].points.resize(brown_basketball::common::g_k_trial_count);
    data.rebounds[i].rebounds.resize(brown_basketball::common::g_k_trial_count);
    data.rebounds[i].assists.resize(brown_basketball::common::g_k_trial_count);
    data.rebounds[i].steals.resize(brown_basketball::common::g_k_trial_count);
    data.rebounds[i].blocks.resize(brown_basketball::common::g_k_trial_count);
    data.rebounds[i].threes.resize(brown_basketball::common::g_k_trial_count);
    data.rebounds[i].field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    data.rebounds[i].free_throws.resize(
        brown_basketball::common::g_k_trial_count);
  }
  for (std::size_t i{0}; i < data.assists.size(); ++i) {
    data.assists[i].points.resize(brown_basketball::common::g_k_trial_count);
    data.assists[i].rebounds.resize(brown_basketball::common::g_k_trial_count);
    data.assists[i].assists.resize(brown_basketball::common::g_k_trial_count);
    data.assists[i].steals.resize(brown_basketball::common::g_k_trial_count);
    data.assists[i].blocks.resize(brown_basketball::common::g_k_trial_count);
    data.assists[i].threes.resize(brown_basketball::common::g_k_trial_count);
    data.assists[i].field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    data.assists[i].free_throws.resize(
        brown_basketball::common::g_k_trial_count);
  }
  for (std::size_t i{0}; i < data.steals.size(); ++i) {
    data.steals[i].points.resize(brown_basketball::common::g_k_trial_count);
    data.steals[i].rebounds.resize(brown_basketball::common::g_k_trial_count);
    data.steals[i].assists.resize(brown_basketball::common::g_k_trial_count);
    data.steals[i].steals.resize(brown_basketball::common::g_k_trial_count);
    data.steals[i].blocks.resize(brown_basketball::common::g_k_trial_count);
    data.steals[i].threes.resize(brown_basketball::common::g_k_trial_count);
    data.steals[i].field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    data.steals[i].free_throws.resize(
        brown_basketball::common::g_k_trial_count);
  }
  for (std::size_t i{0}; i < data.blocks.size(); ++i) {
    data.blocks[i].points.resize(brown_basketball::common::g_k_trial_count);
    data.blocks[i].rebounds.resize(brown_basketball::common::g_k_trial_count);
    data.blocks[i].assists.resize(brown_basketball::common::g_k_trial_count);
    data.blocks[i].steals.resize(brown_basketball::common::g_k_trial_count);
    data.blocks[i].blocks.resize(brown_basketball::common::g_k_trial_count);
    data.blocks[i].threes.resize(brown_basketball::common::g_k_trial_count);
    data.blocks[i].field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    data.blocks[i].free_throws.resize(
        brown_basketball::common::g_k_trial_count);
  }
  for (std::size_t i{0}; i < data.threes.size(); ++i) {
    data.threes[i].points.resize(brown_basketball::common::g_k_trial_count);
    data.threes[i].rebounds.resize(brown_basketball::common::g_k_trial_count);
    data.threes[i].assists.resize(brown_basketball::common::g_k_trial_count);
    data.threes[i].steals.resize(brown_basketball::common::g_k_trial_count);
    data.threes[i].blocks.resize(brown_basketball::common::g_k_trial_count);
    data.threes[i].threes.resize(brown_basketball::common::g_k_trial_count);
    data.threes[i].field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    data.threes[i].free_throws.resize(
        brown_basketball::common::g_k_trial_count);
  }
  for (std::size_t i{0}; i < data.field_goals.size(); ++i) {
    data.field_goals[i].points.resize(
        brown_basketball::common::g_k_trial_count);
    data.field_goals[i].rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    data.field_goals[i].assists.resize(
        brown_basketball::common::g_k_trial_count);
    data.field_goals[i].steals.resize(
        brown_basketball::common::g_k_trial_count);
    data.field_goals[i].blocks.resize(
        brown_basketball::common::g_k_trial_count);
    data.field_goals[i].threes.resize(
        brown_basketball::common::g_k_trial_count);
    data.field_goals[i].field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    data.field_goals[i].free_throws.resize(
        brown_basketball::common::g_k_trial_count);
  }
  for (std::size_t i{0}; i < data.free_throws.size(); ++i) {
    data.free_throws[i].points.resize(
        brown_basketball::common::g_k_trial_count);
    data.free_throws[i].rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    data.free_throws[i].assists.resize(
        brown_basketball::common::g_k_trial_count);
    data.free_throws[i].steals.resize(
        brown_basketball::common::g_k_trial_count);
    data.free_throws[i].blocks.resize(
        brown_basketball::common::g_k_trial_count);
    data.free_throws[i].threes.resize(
        brown_basketball::common::g_k_trial_count);
    data.free_throws[i].field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    data.free_throws[i].free_throws.resize(
        brown_basketball::common::g_k_trial_count);
  }

  auto d{database::read_database(argv[1])};
  analysis::accum_state a{d};
  for (std::size_t i_trial{0}; i_trial < common::g_k_trial_count; ++i_trial) {
    auto g{generation::generate_league(d, (generation::flags::BASIC))};
    auto s_stats{std::get<static_cast<std::size_t>(
        scoring::return_value_type::TEAM_STATS)>(
        scoring::score_league(g, scoring::return_value_type::TEAM_STATS))};
    auto s_ranks{std::get<static_cast<std::size_t>(
        scoring::return_value_type::TEAM_RANKS)>(
        scoring::score_league(g, scoring::return_value_type::TEAM_RANKS))};

    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      data.points[s_ranks[i_team].m_ranks.m_points - 1].points[i_trial] =
          s_stats[i_team].m_stats.m_points;
      data.points[s_ranks[i_team].m_ranks.m_points - 1].rebounds[i_trial] =
          s_stats[i_team].m_stats.m_rebounds;
      data.points[s_ranks[i_team].m_ranks.m_points - 1].assists[i_trial] =
          s_stats[i_team].m_stats.m_assists;
      data.points[s_ranks[i_team].m_ranks.m_points - 1].steals[i_trial] =
          s_stats[i_team].m_stats.m_steals;
      data.points[s_ranks[i_team].m_ranks.m_points - 1].blocks[i_trial] =
          s_stats[i_team].m_stats.m_blocks;
      data.points[s_ranks[i_team].m_ranks.m_points - 1].threes[i_trial] =
          s_stats[i_team].m_stats.m_threes;
      data.points[s_ranks[i_team].m_ranks.m_points - 1].field_goals[i_trial] =
          s_stats[i_team].m_stats.m_field_goals;
      data.points[s_ranks[i_team].m_ranks.m_points - 1].free_throws[i_trial] =
          s_stats[i_team].m_stats.m_free_throws;
    }
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      data.rebounds[s_ranks[i_team].m_ranks.m_rebounds - 1].points[i_trial] =
          s_stats[i_team].m_stats.m_points;
      data.rebounds[s_ranks[i_team].m_ranks.m_rebounds - 1].rebounds[i_trial] =
          s_stats[i_team].m_stats.m_rebounds;
      data.rebounds[s_ranks[i_team].m_ranks.m_rebounds - 1].assists[i_trial] =
          s_stats[i_team].m_stats.m_assists;
      data.rebounds[s_ranks[i_team].m_ranks.m_rebounds - 1].steals[i_trial] =
          s_stats[i_team].m_stats.m_steals;
      data.rebounds[s_ranks[i_team].m_ranks.m_rebounds - 1].blocks[i_trial] =
          s_stats[i_team].m_stats.m_blocks;
      data.rebounds[s_ranks[i_team].m_ranks.m_rebounds - 1].threes[i_trial] =
          s_stats[i_team].m_stats.m_threes;
      data.rebounds[s_ranks[i_team].m_ranks.m_rebounds - 1]
          .field_goals[i_trial] = s_stats[i_team].m_stats.m_field_goals;
      data.rebounds[s_ranks[i_team].m_ranks.m_rebounds - 1]
          .free_throws[i_trial] = s_stats[i_team].m_stats.m_free_throws;
    }
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      data.assists[s_ranks[i_team].m_ranks.m_assists - 1].points[i_trial] =
          s_stats[i_team].m_stats.m_points;
      data.assists[s_ranks[i_team].m_ranks.m_assists - 1].rebounds[i_trial] =
          s_stats[i_team].m_stats.m_rebounds;
      data.assists[s_ranks[i_team].m_ranks.m_assists - 1].assists[i_trial] =
          s_stats[i_team].m_stats.m_assists;
      data.assists[s_ranks[i_team].m_ranks.m_assists - 1].steals[i_trial] =
          s_stats[i_team].m_stats.m_steals;
      data.assists[s_ranks[i_team].m_ranks.m_assists - 1].blocks[i_trial] =
          s_stats[i_team].m_stats.m_blocks;
      data.assists[s_ranks[i_team].m_ranks.m_assists - 1].threes[i_trial] =
          s_stats[i_team].m_stats.m_threes;
      data.assists[s_ranks[i_team].m_ranks.m_assists - 1].field_goals[i_trial] =
          s_stats[i_team].m_stats.m_field_goals;
      data.assists[s_ranks[i_team].m_ranks.m_assists - 1].free_throws[i_trial] =
          s_stats[i_team].m_stats.m_free_throws;
    }
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      data.steals[s_ranks[i_team].m_ranks.m_steals - 1].points[i_trial] =
          s_stats[i_team].m_stats.m_points;
      data.steals[s_ranks[i_team].m_ranks.m_steals - 1].rebounds[i_trial] =
          s_stats[i_team].m_stats.m_rebounds;
      data.steals[s_ranks[i_team].m_ranks.m_steals - 1].assists[i_trial] =
          s_stats[i_team].m_stats.m_assists;
      data.steals[s_ranks[i_team].m_ranks.m_steals - 1].steals[i_trial] =
          s_stats[i_team].m_stats.m_steals;
      data.steals[s_ranks[i_team].m_ranks.m_steals - 1].blocks[i_trial] =
          s_stats[i_team].m_stats.m_blocks;
      data.steals[s_ranks[i_team].m_ranks.m_steals - 1].threes[i_trial] =
          s_stats[i_team].m_stats.m_threes;
      data.steals[s_ranks[i_team].m_ranks.m_steals - 1].field_goals[i_trial] =
          s_stats[i_team].m_stats.m_field_goals;
      data.steals[s_ranks[i_team].m_ranks.m_steals - 1].free_throws[i_trial] =
          s_stats[i_team].m_stats.m_free_throws;
    }
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      data.blocks[s_ranks[i_team].m_ranks.m_blocks - 1].points[i_trial] =
          s_stats[i_team].m_stats.m_points;
      data.blocks[s_ranks[i_team].m_ranks.m_blocks - 1].rebounds[i_trial] =
          s_stats[i_team].m_stats.m_rebounds;
      data.blocks[s_ranks[i_team].m_ranks.m_blocks - 1].assists[i_trial] =
          s_stats[i_team].m_stats.m_assists;
      data.blocks[s_ranks[i_team].m_ranks.m_blocks - 1].steals[i_trial] =
          s_stats[i_team].m_stats.m_steals;
      data.blocks[s_ranks[i_team].m_ranks.m_blocks - 1].blocks[i_trial] =
          s_stats[i_team].m_stats.m_blocks;
      data.blocks[s_ranks[i_team].m_ranks.m_blocks - 1].threes[i_trial] =
          s_stats[i_team].m_stats.m_threes;
      data.blocks[s_ranks[i_team].m_ranks.m_blocks - 1].field_goals[i_trial] =
          s_stats[i_team].m_stats.m_field_goals;
      data.blocks[s_ranks[i_team].m_ranks.m_blocks - 1].free_throws[i_trial] =
          s_stats[i_team].m_stats.m_free_throws;
    }
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      data.threes[s_ranks[i_team].m_ranks.m_threes - 1].points[i_trial] =
          s_stats[i_team].m_stats.m_points;
      data.threes[s_ranks[i_team].m_ranks.m_threes - 1].rebounds[i_trial] =
          s_stats[i_team].m_stats.m_rebounds;
      data.threes[s_ranks[i_team].m_ranks.m_threes - 1].assists[i_trial] =
          s_stats[i_team].m_stats.m_assists;
      data.threes[s_ranks[i_team].m_ranks.m_threes - 1].steals[i_trial] =
          s_stats[i_team].m_stats.m_steals;
      data.threes[s_ranks[i_team].m_ranks.m_threes - 1].blocks[i_trial] =
          s_stats[i_team].m_stats.m_blocks;
      data.threes[s_ranks[i_team].m_ranks.m_threes - 1].threes[i_trial] =
          s_stats[i_team].m_stats.m_threes;
      data.threes[s_ranks[i_team].m_ranks.m_threes - 1].field_goals[i_trial] =
          s_stats[i_team].m_stats.m_field_goals;
      data.threes[s_ranks[i_team].m_ranks.m_threes - 1].free_throws[i_trial] =
          s_stats[i_team].m_stats.m_free_throws;
    }
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      data.field_goals[s_ranks[i_team].m_ranks.m_field_goals - 1]
          .points[i_trial] = s_stats[i_team].m_stats.m_points;
      data.field_goals[s_ranks[i_team].m_ranks.m_field_goals - 1]
          .rebounds[i_trial] = s_stats[i_team].m_stats.m_rebounds;
      data.field_goals[s_ranks[i_team].m_ranks.m_field_goals - 1]
          .assists[i_trial] = s_stats[i_team].m_stats.m_assists;
      data.field_goals[s_ranks[i_team].m_ranks.m_field_goals - 1]
          .steals[i_trial] = s_stats[i_team].m_stats.m_steals;
      data.field_goals[s_ranks[i_team].m_ranks.m_field_goals - 1]
          .blocks[i_trial] = s_stats[i_team].m_stats.m_blocks;
      data.field_goals[s_ranks[i_team].m_ranks.m_field_goals - 1]
          .threes[i_trial] = s_stats[i_team].m_stats.m_threes;
      data.field_goals[s_ranks[i_team].m_ranks.m_field_goals - 1]
          .field_goals[i_trial] = s_stats[i_team].m_stats.m_field_goals;
      data.field_goals[s_ranks[i_team].m_ranks.m_field_goals - 1]
          .free_throws[i_trial] = s_stats[i_team].m_stats.m_free_throws;
    }
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      data.free_throws[s_ranks[i_team].m_ranks.m_free_throws - 1]
          .points[i_trial] = s_stats[i_team].m_stats.m_points;
      data.free_throws[s_ranks[i_team].m_ranks.m_free_throws - 1]
          .rebounds[i_trial] = s_stats[i_team].m_stats.m_rebounds;
      data.free_throws[s_ranks[i_team].m_ranks.m_free_throws - 1]
          .assists[i_trial] = s_stats[i_team].m_stats.m_assists;
      data.free_throws[s_ranks[i_team].m_ranks.m_free_throws - 1]
          .steals[i_trial] = s_stats[i_team].m_stats.m_steals;
      data.free_throws[s_ranks[i_team].m_ranks.m_free_throws - 1]
          .blocks[i_trial] = s_stats[i_team].m_stats.m_blocks;
      data.free_throws[s_ranks[i_team].m_ranks.m_free_throws - 1]
          .threes[i_trial] = s_stats[i_team].m_stats.m_threes;
      data.free_throws[s_ranks[i_team].m_ranks.m_free_throws - 1]
          .field_goals[i_trial] = s_stats[i_team].m_stats.m_field_goals;
      data.free_throws[s_ranks[i_team].m_ranks.m_free_throws - 1]
          .free_throws[i_trial] = s_stats[i_team].m_stats.m_free_throws;
    }
  }

  //

  static constexpr char separator{';'};

  auto print_team_stats{[](const stats &team) -> void {
    MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(points);
    MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(rebounds);
    MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(assists);
    MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(steals);
    MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(blocks);
    MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(threes);
    MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(field_goals);
    MACRO_PRINT_TEAM_STATS_FOR_CATEGORY(free_throws);
  }};

  std::cout << "team" << separator << "points_mean" << separator << "points_min"
            << separator << "points_max" << separator << "points_stdev"
            << separator << "rebounds_mean" << separator << "rebounds_min"
            << separator << "rebounds_max" << separator << "rebounds_stdev"
            << separator << "assists_mean" << separator << "assists_min"
            << separator << "assists_max" << separator << "assists_stdev"
            << separator << "steals_mean" << separator << "steals_min"
            << separator << "steals_max" << separator << "steals_stdev"
            << separator << "blocks_mean" << separator << "blocks_min"
            << separator << "blocks_max" << separator << "blocks_stdev"
            << separator << "threes_mean" << separator << "threes_min"
            << separator << "threes_max" << separator << "threes_stdev"
            << separator << "field_goals_mean" << separator << "field_goals_min"
            << separator << "field_goals_max" << separator
            << "field_goals_stdev" << separator << "free_throws_mean"
            << separator << "free_throws_min" << separator << "free_throws_max"
            << separator << "free_throws_stdev" << '\n';

  MACRO_PRINT_TEAM(points);
  MACRO_PRINT_TEAM(rebounds);
  MACRO_PRINT_TEAM(assists);
  MACRO_PRINT_TEAM(steals);
  MACRO_PRINT_TEAM(blocks);
  MACRO_PRINT_TEAM(threes);
  MACRO_PRINT_TEAM(field_goals);
  MACRO_PRINT_TEAM(free_throws);
  return 0;
}

int main(int argc, char *argv[]) { main_main(argc, argv); }
