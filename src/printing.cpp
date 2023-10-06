#include "printing.hpp"

#include "analysis.hpp"
#include "common.hpp"

#include <array>
#include <iostream>
#include <string>

void printing::print_result(
    std::ostream &out,
    const std::array<std::pair<const common::player *, analysis::rank_probs>,
                     common::g_k_pool_size> &result) {
  return impl::print_result(out, result);
}

void printing::impl::print_result(
    std::ostream &out,
    const std::array<std::pair<const common::player *, analysis::rank_probs>,
                     common::g_k_pool_size> &result) {
  out << compose_header() << g_k_row_separator;

  for (auto p_player{result.begin()}; p_player != result.end(); ++p_player) {
    out << p_player->first->m_info.m_name << g_k_column_separator;

    out << p_player->second.m_points.m_top << g_k_column_separator;
    out << p_player->second.m_points.m_cutoff << g_k_column_separator;

    out << p_player->second.m_rebounds.m_top << g_k_column_separator;
    out << p_player->second.m_rebounds.m_cutoff << g_k_column_separator;

    out << p_player->second.m_assists.m_top << g_k_column_separator;
    out << p_player->second.m_assists.m_cutoff << g_k_column_separator;

    out << p_player->second.m_steals.m_top << g_k_column_separator;
    out << p_player->second.m_steals.m_cutoff << g_k_column_separator;

    out << p_player->second.m_blocks.m_top << g_k_column_separator;
    out << p_player->second.m_blocks.m_cutoff << g_k_column_separator;

    out << p_player->second.m_threes.m_top << g_k_column_separator;
    out << p_player->second.m_threes.m_cutoff << g_k_column_separator;

    out << p_player->second.m_field_goals.m_top << g_k_column_separator;
    out << p_player->second.m_field_goals.m_cutoff << g_k_column_separator;

    out << p_player->second.m_free_throws.m_top << g_k_column_separator;
    out << p_player->second.m_free_throws.m_cutoff << g_k_column_separator;

    out << g_k_row_separator;
  }
}

std::string printing::impl::compose_header() {
  static constexpr std::string player_header{"Player"};

  std::string ret_val{};

  ret_val.append(player_header).push_back(g_k_column_separator);

  for (auto p_cat_str{g_k_category_strs.begin()};
       p_cat_str != g_k_category_strs.end(); ++p_cat_str) {
    ret_val
        .append(compose_rank_prob_header(
            compose_rank_prob_header_category(*p_cat_str),
            compose_rank_prob_header_value(common::g_k_rank_top)))
        .push_back(g_k_column_separator);
    ret_val
        .append(compose_rank_prob_header(
            compose_rank_prob_header_category(*p_cat_str),
            compose_rank_prob_header_value(common::g_k_rank_top,
                                           common::g_k_rank_cutoff)))
        .push_back(g_k_column_separator);
  }

  return ret_val;
}

std::string
printing::impl::compose_rank_prob_header(const std::string &category,
                                         const std::string &value) {
  static constexpr std::string start{"P("};
  static constexpr std::string separator{"="};
  static constexpr std::string end{")"};
  return std::string{start + category + separator + value + end};
}

std::string
printing::impl::compose_rank_prob_header_category(const std::string &category) {
  static constexpr std::string start{"rank_"};
  return std::string{start + category};
}

std::string
printing::impl::compose_rank_prob_header_value(const int start,
                                               const int end /*= -1*/) {
  static constexpr std::string separator{"-"};
  return std::string{
      std::to_string(start) +
      ((end != -1) ? (separator + std::to_string(end)) : (std::string{}))};
}
