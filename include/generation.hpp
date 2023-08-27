#ifndef GENERATION_HPP
#define GENERATION_HPP

#include "common.hpp"

#include "random.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

namespace generation {
enum class generation_type {
  BASIC,
};

std::array<common::team, common::g_k_league_size> generate_league(
    const std::array<common::player, common::g_k_player_count> &database,
    const generation_type gen_type);
namespace impl {
struct index {
  std::size_t m_idx;
  bool m_used;
};

std::array<common::team, common::g_k_league_size> generate_league(
    const std::array<common::player, common::g_k_player_count> &database,
    const generation_type gen_type);

void basic_generation(
    std::array<index, common::g_k_player_count> &indices,
    [[maybe_unused]] const std::array<common::player, common::g_k_player_count>
        &database,
    my_rand::random &rand);
} // namespace impl
} // namespace generation

#endif
