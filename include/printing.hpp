#ifndef BROWN_BASKETBALL_PRINTING_HPP
#define BROWN_BASKETBALL_PRINTING_HPP

#include "analysis.hpp"
#include "common.hpp"

#include <array>
#include <iostream>
#include <string>

namespace printing {
void print_result(
    std::ostream &out,
    const std::array<std::pair<const common::player *, analysis::rank_probs>,
                     common::g_k_pool_size> &result);
namespace impl {
static constexpr char g_k_column_separator{','};
static constexpr char g_k_row_separator{'\n'};

static constexpr std::array<std::string, 8> g_k_category_strs{
    "points", "rebounds", "assists",      "steals",
    "blocks", "threes",   "fields_goals", "free_throws"};
void print_result(
    std::ostream &out,
    const std::array<std::pair<const common::player *, analysis::rank_probs>,
                     common::g_k_pool_size> &result);

std::string compose_header();
std::string compose_rank_prob_header(const std::string &category,
                                     const std::string &value);
std::string compose_rank_prob_header_category(const std::string &category);
std::string compose_rank_prob_header_value(const int start, const int end = -1);
}; // namespace impl
}; // namespace printing

#endif
