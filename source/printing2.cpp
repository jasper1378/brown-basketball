#include "printing2.hpp"

#include "analysis2.hpp"
#include "common.hpp"

#include <cstddef>
#include <iostream>
#include <string>

void brown_basketball::printing2::print_result(
    std::ostream &out, const analysis2::read_t &result) {
  const auto print_header{[&out]() {
    static constexpr std::array<std::string, 4> stat_strs{"mean", "min", "max",
                                                          "stdev"};

    out << "team" << common::g_k_column_separator_char;

    for (auto p_cat_str{common::g_k_category_strs.begin()};
         p_cat_str != common::g_k_category_strs.end(); ++p_cat_str) {
      for (auto p_stat_str{stat_strs.begin()}; p_stat_str != stat_strs.end();
           ++p_stat_str) {
        out << *p_cat_str << '_' << *p_stat_str
            << common::g_k_column_separator_char;
      }
    }
  }};

  print_header();
  out << common::g_k_row_separator_char;

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    out << common::g_k_category_strs[static_cast<std::size_t>(
               common::category::points)]
        << "_team_" << (i_team + 1) << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_points.m_mean
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_points.m_min
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_points.m_max
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_points.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_rebounds.m_mean
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_rebounds.m_min
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_rebounds.m_max
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_rebounds.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_assists.m_mean
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_assists.m_min
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_assists.m_max
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_assists.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_steals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_steals.m_min
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_steals.m_max
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_steals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_blocks.m_mean
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_blocks.m_min
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_blocks.m_max
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_blocks.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_threes.m_mean
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_threes.m_min
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_threes.m_max
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_threes.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_field_goals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_field_goals.m_min
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_field_goals.m_max
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_field_goals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_free_throws.m_mean
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_free_throws.m_min
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_free_throws.m_max
        << common::g_k_column_separator_char;
    out << result.m_points[i_team].m_free_throws.m_stdev
        << common::g_k_column_separator_char;
    out << common::g_k_row_separator_char;
  }

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    out << common::g_k_category_strs[static_cast<std::size_t>(
               common::category::rebounds)]
        << "_team_" << (i_team + 1) << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_points.m_mean
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_points.m_min
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_points.m_max
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_points.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_rebounds.m_mean
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_rebounds.m_min
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_rebounds.m_max
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_rebounds.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_assists.m_mean
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_assists.m_min
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_assists.m_max
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_assists.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_steals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_steals.m_min
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_steals.m_max
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_steals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_blocks.m_mean
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_blocks.m_min
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_blocks.m_max
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_blocks.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_threes.m_mean
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_threes.m_min
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_threes.m_max
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_threes.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_field_goals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_field_goals.m_min
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_field_goals.m_max
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_field_goals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_free_throws.m_mean
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_free_throws.m_min
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_free_throws.m_max
        << common::g_k_column_separator_char;
    out << result.m_rebounds[i_team].m_free_throws.m_stdev
        << common::g_k_column_separator_char;
    out << common::g_k_row_separator_char;
  }

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    out << common::g_k_category_strs[static_cast<std::size_t>(
               common::category::assists)]
        << "_team_" << (i_team + 1) << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_points.m_mean
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_points.m_min
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_points.m_max
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_points.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_rebounds.m_mean
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_rebounds.m_min
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_rebounds.m_max
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_rebounds.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_assists.m_mean
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_assists.m_min
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_assists.m_max
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_assists.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_steals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_steals.m_min
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_steals.m_max
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_steals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_blocks.m_mean
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_blocks.m_min
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_blocks.m_max
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_blocks.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_threes.m_mean
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_threes.m_min
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_threes.m_max
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_threes.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_field_goals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_field_goals.m_min
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_field_goals.m_max
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_field_goals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_free_throws.m_mean
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_free_throws.m_min
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_free_throws.m_max
        << common::g_k_column_separator_char;
    out << result.m_assists[i_team].m_free_throws.m_stdev
        << common::g_k_column_separator_char;
    out << common::g_k_row_separator_char;
  }

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    out << common::g_k_category_strs[static_cast<std::size_t>(
               common::category::steals)]
        << "_team_" << (i_team + 1) << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_points.m_mean
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_points.m_min
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_points.m_max
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_points.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_rebounds.m_mean
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_rebounds.m_min
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_rebounds.m_max
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_rebounds.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_assists.m_mean
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_assists.m_min
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_assists.m_max
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_assists.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_steals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_steals.m_min
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_steals.m_max
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_steals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_blocks.m_mean
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_blocks.m_min
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_blocks.m_max
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_blocks.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_threes.m_mean
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_threes.m_min
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_threes.m_max
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_threes.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_field_goals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_field_goals.m_min
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_field_goals.m_max
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_field_goals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_free_throws.m_mean
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_free_throws.m_min
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_free_throws.m_max
        << common::g_k_column_separator_char;
    out << result.m_steals[i_team].m_free_throws.m_stdev
        << common::g_k_column_separator_char;
    out << common::g_k_row_separator_char;
  }

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    out << common::g_k_category_strs[static_cast<std::size_t>(
               common::category::blocks)]
        << "_team_" << (i_team + 1) << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_points.m_mean
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_points.m_min
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_points.m_max
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_points.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_rebounds.m_mean
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_rebounds.m_min
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_rebounds.m_max
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_rebounds.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_assists.m_mean
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_assists.m_min
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_assists.m_max
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_assists.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_steals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_steals.m_min
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_steals.m_max
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_steals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_blocks.m_mean
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_blocks.m_min
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_blocks.m_max
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_blocks.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_threes.m_mean
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_threes.m_min
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_threes.m_max
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_threes.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_field_goals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_field_goals.m_min
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_field_goals.m_max
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_field_goals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_free_throws.m_mean
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_free_throws.m_min
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_free_throws.m_max
        << common::g_k_column_separator_char;
    out << result.m_blocks[i_team].m_free_throws.m_stdev
        << common::g_k_column_separator_char;
    out << common::g_k_row_separator_char;
  }

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    out << common::g_k_category_strs[static_cast<std::size_t>(
               common::category::threes)]
        << "_team_" << (i_team + 1) << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_points.m_mean
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_points.m_min
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_points.m_max
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_points.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_rebounds.m_mean
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_rebounds.m_min
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_rebounds.m_max
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_rebounds.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_assists.m_mean
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_assists.m_min
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_assists.m_max
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_assists.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_steals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_steals.m_min
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_steals.m_max
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_steals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_blocks.m_mean
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_blocks.m_min
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_blocks.m_max
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_blocks.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_threes.m_mean
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_threes.m_min
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_threes.m_max
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_threes.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_field_goals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_field_goals.m_min
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_field_goals.m_max
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_field_goals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_free_throws.m_mean
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_free_throws.m_min
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_free_throws.m_max
        << common::g_k_column_separator_char;
    out << result.m_threes[i_team].m_free_throws.m_stdev
        << common::g_k_column_separator_char;
    out << common::g_k_row_separator_char;
  }

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    out << common::g_k_category_strs[static_cast<std::size_t>(
               common::category::field_goals)]
        << "_team_" << (i_team + 1) << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_points.m_mean
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_points.m_min
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_points.m_max
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_points.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_rebounds.m_mean
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_rebounds.m_min
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_rebounds.m_max
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_rebounds.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_assists.m_mean
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_assists.m_min
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_assists.m_max
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_assists.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_steals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_steals.m_min
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_steals.m_max
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_steals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_blocks.m_mean
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_blocks.m_min
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_blocks.m_max
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_blocks.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_threes.m_mean
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_threes.m_min
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_threes.m_max
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_threes.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_field_goals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_field_goals.m_min
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_field_goals.m_max
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_field_goals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_free_throws.m_mean
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_free_throws.m_min
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_free_throws.m_max
        << common::g_k_column_separator_char;
    out << result.m_field_goals[i_team].m_free_throws.m_stdev
        << common::g_k_column_separator_char;
    out << common::g_k_row_separator_char;
  }

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    out << common::g_k_category_strs[static_cast<std::size_t>(
               common::category::free_throws)]
        << "_team_" << (i_team + 1) << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_points.m_mean
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_points.m_min
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_points.m_max
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_points.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_rebounds.m_mean
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_rebounds.m_min
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_rebounds.m_max
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_rebounds.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_assists.m_mean
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_assists.m_min
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_assists.m_max
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_assists.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_steals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_steals.m_min
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_steals.m_max
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_steals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_blocks.m_mean
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_blocks.m_min
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_blocks.m_max
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_blocks.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_threes.m_mean
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_threes.m_min
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_threes.m_max
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_threes.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_field_goals.m_mean
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_field_goals.m_min
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_field_goals.m_max
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_field_goals.m_stdev
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_free_throws.m_mean
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_free_throws.m_min
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_free_throws.m_max
        << common::g_k_column_separator_char;
    out << result.m_free_throws[i_team].m_free_throws.m_stdev
        << common::g_k_column_separator_char;
    out << common::g_k_row_separator_char;
  }
};
