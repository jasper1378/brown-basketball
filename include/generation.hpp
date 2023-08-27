#ifndef GENERATION_HPP
#define GENERATION_HPP

#include "common.hpp"

#include "random.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

namespace generation {
std::array<common::team, common::g_k_league_size> generate_league(
    const std::array<common::player, common::g_k_player_count> &database);
namespace impl {
struct index {
  std::size_t m_idx;
  bool m_used;
};

std::array<common::team, common::g_k_league_size> generate_league(
    const std::array<common::player, common::g_k_player_count> &database);

void basic_generation(
    std::array<index, common::g_k_player_count> &indices,
    [[maybe_unused]] const std::array<common::player, common::g_k_player_count>
        &database,
    class random &rand);
} // namespace impl
} // namespace generation

#endif
