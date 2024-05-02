#include "printing1.hpp"

#include "analysis1.hpp"
#include "common.hpp"

#include <cassert>
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

    assert(static_cast<std::size_t>(common::category::N) ==
           common::g_k_category_strs.size());
    for (std::size_t i_cat_str{0};
         i_cat_str < static_cast<std::size_t>(common::category::N);
         ++i_cat_str) {
      print_rank_prob_header(common::g_k_category_strs[i_cat_str],
                             common::g_k_rank_top);
      out << common::g_k_column_separator_char;
      print_rank_prob_header(common::g_k_category_strs[i_cat_str],
                             common::g_k_rank_top, common::g_k_rank_cutoff);
      out << common::g_k_column_separator_char;
    }
  }};

  print_header();
  out << common::g_k_row_separator_char;

  assert(common::g_k_pool_size == result.size());
  for (std::size_t i_player{0}; i_player < common::g_k_pool_size; ++i_player) {
    out << result[i_player].first->m_info.m_name
        << common::g_k_column_separator_char;

    assert(static_cast<std::size_t>(common::category::N) ==
           result[i_player].second.size());
    for (std::size_t i_cat{0};
         i_cat < static_cast<std::size_t>(common::category::N); ++i_cat) {
      out << result[i_player].second[i_cat].m_top
          << common::g_k_column_separator_char;
      out << result[i_player].second[i_cat].m_cutoff
          << common::g_k_column_separator_char;
    }

    out << common::g_k_row_separator_char;
  }
}
