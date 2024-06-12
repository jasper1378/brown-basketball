#include "printing2.hpp"

#include "analysis2.hpp"
#include "common.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

void brown_basketball::printing2::print_result(
    std::ostream &out, const analysis2::read_t &result) {
  const auto print_header{[&out]() {
    static constexpr std::array<std::string, 4> k_stat_strs{"mean", "min",
                                                            "max", "stdev"};

    out << "team" << common::k_column_separator_char;

    assert(static_cast<std::size_t>(common::category::N) ==
           common::k_category_strs.size());
    for (std::size_t i_cat_str{0};
         i_cat_str < static_cast<std::size_t>(common::category::N);
         ++i_cat_str) {
      for (std::size_t i_stat_str{0}; i_stat_str < k_stat_strs.size();
           ++i_stat_str) {
        out << common::k_category_strs[i_cat_str] << '_'
            << k_stat_strs[i_stat_str] << common::k_column_separator_char;
      }
    }
  }};

  print_header();
  out << common::k_row_separator_char;

  assert(static_cast<std::size_t>(common::category::N) == result.size());
  for (std::size_t i_cat_1{0};
       i_cat_1 < static_cast<std::size_t>(common::category::N); ++i_cat_1) {
    for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
      out << common::k_category_strs[i_cat_1] << "_team_" << (i_team + 1)
          << common::k_column_separator_char;
      assert(static_cast<std::size_t>(common::category::N) ==
             result[i_cat_1][i_team].size());
      for (std::size_t i_cat_2{0};
           i_cat_2 < static_cast<std::size_t>(common::category::N); ++i_cat_2) {
        out << result[i_cat_1][i_team][i_cat_2].m_mean
            << common::k_column_separator_char;
        out << result[i_cat_1][i_team][i_cat_2].m_min
            << common::k_column_separator_char;
        out << result[i_cat_1][i_team][i_cat_2].m_max
            << common::k_column_separator_char;
        out << result[i_cat_1][i_team][i_cat_2].m_stdev
            << common::k_column_separator_char;
      }
      out << common::k_row_separator_char;
    }
  }
};
