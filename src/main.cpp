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
  auto d{database::read_database(argv[1])};
  analysis::accum_state a{d};
  for (std::size_t i_trial{0}; i_trial < common::g_k_trial_count; ++i_trial) {
    auto g{generation::generate_league(d, generation::generation_type::BASIC)};
    // XXX DEBUG BEGIN
    std::cerr << "g:\n\n";
    for (std::size_t i{0}; i < g.size(); ++i) {
      for (std::size_t j{0}; j < g[i].m_players.size(); ++j) {
        std::cerr << g[i].m_players[j]->m_info.m_name << "; ";
      }
      std::cerr << "\n\n";
    }
    std::cerr << '\n';

    auto s1{std::get<static_cast<std::size_t>(
        scoring::return_value_type::TEAM_STATS)>(
        scoring::score_league(g, scoring::return_value_type::TEAM_STATS))};
    std::cerr << "s1:\n\n";
    for (std::size_t i{0}; i < s1.size(); ++i) {
      for (std::size_t j{0}; j < s1[i].m_team->m_players.size(); ++j) {
        std::cerr << s1[i].m_team->m_players[j]->m_info.m_name << "; ";
      }
      std::cerr << '\n';
      std::cerr << "points:" << s1[i].m_stats.m_points << "; ";
      std::cerr << "rebounds:" << s1[i].m_stats.m_rebounds << "; ";
      std::cerr << "assists:" << s1[i].m_stats.m_assists << "; ";
      std::cerr << "steals:" << s1[i].m_stats.m_steals << "; ";
      std::cerr << "blocks:" << s1[i].m_stats.m_blocks << "; ";
      std::cerr << "threes:" << s1[i].m_stats.m_threes << "; ";
      std::cerr << "field_goals:" << s1[i].m_stats.m_field_goals << "; ";
      std::cerr << "free_throws:" << s1[i].m_stats.m_free_throws << "; ";
      std::cerr << "\n\n";
    }
    std::cerr << '\n';

    auto s2{std::get<static_cast<std::size_t>(
        scoring::return_value_type::TEAM_RANKS)>(
        scoring::score_league(g, scoring::return_value_type::TEAM_RANKS))};
    std::cerr << "s2:\n\n";
    for (std::size_t i{0}; i < s2.size(); ++i) {
      for (std::size_t j{0}; j < s2[i].m_team->m_players.size(); ++j) {
        std::cerr << s2[i].m_team->m_players[j]->m_info.m_name << "; ";
      }
      std::cerr << '\n';
      std::cerr << "points:" << s2[i].m_ranks.m_points << "; ";
      std::cerr << "rebounds:" << s2[i].m_ranks.m_rebounds << "; ";
      std::cerr << "assists:" << s2[i].m_ranks.m_assists << "; ";
      std::cerr << "steals:" << s2[i].m_ranks.m_steals << "; ";
      std::cerr << "blocks:" << s2[i].m_ranks.m_blocks << "; ";
      std::cerr << "threes:" << s2[i].m_ranks.m_threes << "; ";
      std::cerr << "field_goals:" << s2[i].m_ranks.m_field_goals << "; ";
      std::cerr << "free_throws:" << s2[i].m_ranks.m_free_throws << "; ";
      std::cerr << "\n\n";
    }
    std::cerr << '\n';

    auto s3{std::get<static_cast<std::size_t>(
        scoring::return_value_type::TEAM_SCORES)>(
        scoring::score_league(g, scoring::return_value_type::TEAM_SCORES))};
    std::cerr << "s3:\n\n";
    for (std::size_t i{0}; i < s3.size(); ++i) {
      for (std::size_t j{0}; j < s3[i].m_team->m_players.size(); ++j) {
        std::cerr << s3[i].m_team->m_players[j]->m_info.m_name << "; ";
      }
      std::cerr << '\n';
      std::cerr << "points:" << s3[i].m_scores.m_points << "; ";
      std::cerr << "rebounds:" << s3[i].m_scores.m_rebounds << "; ";
      std::cerr << "assists:" << s3[i].m_scores.m_assists << "; ";
      std::cerr << "steals:" << s3[i].m_scores.m_steals << "; ";
      std::cerr << "blocks:" << s3[i].m_scores.m_blocks << "; ";
      std::cerr << "threes:" << s3[i].m_scores.m_threes << "; ";
      std::cerr << "field_goals:" << s3[i].m_scores.m_field_goals << "; ";
      std::cerr << "free_throws:" << s3[i].m_scores.m_free_throws << "; ";
      std::cerr << "\n\n";
    }
    std::cerr << '\n';

    auto s4{std::get<static_cast<std::size_t>(
        scoring::return_value_type::TEAM_TOTAL_SCORE)>(
        scoring::score_league(g,
                              scoring::return_value_type::TEAM_TOTAL_SCORE))};
    std::cerr << "s4:\n\n";
    for (std::size_t i{0}; i < s4.size(); ++i) {
      for (std::size_t j{0}; j < s4[i].m_team->m_players.size(); ++j) {
        std::cerr << s4[i].m_team->m_players[j]->m_info.m_name << "; ";
      }
      std::cerr << '\n';
      std::cerr << s4[i].m_total_score;
      std::cerr << "\n\n";
    }
    std::cerr << '\n';

    auto s5{std::get<static_cast<std::size_t>(
        scoring::return_value_type::TEAM_TOTAL_RANK)>(
        scoring::score_league(g, scoring::return_value_type::TEAM_TOTAL_RANK))};
    std::cerr << "s5:\n\n";
    for (std::size_t i{0}; i < s5.size(); ++i) {
      for (std::size_t j{0}; j < s5[i].m_team->m_players.size(); ++j) {
        std::cerr << s5[i].m_team->m_players[j]->m_info.m_name << "; ";
      }
      std::cerr << '\n';
      std::cerr << s5[i].m_total_rank;
      std::cerr << "\n\n";
    }
    std::cerr << '\n';

    std::exit(0);
    // XXX DEBUG END
    auto s{scoring::score_league(g, scoring::return_value_type::TEAM_RANKS)};
    a.add(std::get<static_cast<std::size_t>(
              scoring::return_value_type::TEAM_RANKS)>(s));
  }
  printing::print_result(std::cout, a.read());
}
