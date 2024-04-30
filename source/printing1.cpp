#include "printing1.hpp"

#include "analysis1.hpp"
#include "common.hpp"

#include <cstddef>
#include <iostream>
#include <string>

void brown_basketball::printing1::print_result(
    std::ostream &out, const analysis1::read_t &result) {
  const auto print_header{[&out]() {
    const auto print_rank_prob_header{[&out](const std::string &category,
                                             const int value_start,
                                             const int value_end = -1) {
      out << "P("
          << "rank_" << category << '=' << value_start;
      if (value_end != -1) {
        out << '-' << value_end;
      }
      out << ')';
    }};

    out << "player" << common::g_k_column_separator_char;

    for (std::size_t i_cat_str{0}; i_cat_str < common::g_k_category_strs.size();
         ++i_cat_str) {
      print_rank_prob_header(common::g_k_category_strs[i_cat_str],
                             common::g_k_rank_top);
      out << common::g_k_column_separator_char;
      print_rank_prob_header(common::g_k_category_strs[i_cat_str],
                             common::g_k_rank_cutoff);
      out << common::g_k_column_separator_char;
    }
  }};

  print_header();
  out << common::g_k_row_separator_char;

  for (std::size_t i_player{0}; i_player < result.size(); ++i_player) {
    out << result[i_player].first->m_info.m_name
        << common::g_k_column_separator_char;

    out << result[i_player].second.m_points.m_top
        << common::g_k_column_separator_char;
    out << result[i_player].second.m_points.m_cutoff
        << common::g_k_column_separator_char;

    out << result[i_player].second.m_rebounds.m_top
        << common::g_k_column_separator_char;
    out << result[i_player].second.m_rebounds.m_cutoff
        << common::g_k_column_separator_char;

    out << result[i_player].second.m_assists.m_top
        << common::g_k_column_separator_char;
    out << result[i_player].second.m_assists.m_cutoff
        << common::g_k_column_separator_char;

    out << result[i_player].second.m_steals.m_top
        << common::g_k_column_separator_char;
    out << result[i_player].second.m_steals.m_cutoff
        << common::g_k_column_separator_char;

    out << result[i_player].second.m_blocks.m_top
        << common::g_k_column_separator_char;
    out << result[i_player].second.m_blocks.m_cutoff
        << common::g_k_column_separator_char;

    out << result[i_player].second.m_threes.m_top
        << common::g_k_column_separator_char;
    out << result[i_player].second.m_threes.m_cutoff
        << common::g_k_column_separator_char;

    out << result[i_player].second.m_field_goals.m_top
        << common::g_k_column_separator_char;
    out << result[i_player].second.m_field_goals.m_cutoff
        << common::g_k_column_separator_char;

    out << result[i_player].second.m_free_throws.m_top
        << common::g_k_column_separator_char;
    out << result[i_player].second.m_free_throws.m_cutoff
        << common::g_k_column_separator_char;

    out << common::g_k_row_separator_char;
  }
}
