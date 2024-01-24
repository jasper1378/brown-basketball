#ifndef BROWN_BASKETBALL_GENERATION_HPP
#define BROWN_BASKETBALL_GENERATION_HPP

#include "common.hpp"

#include "my_random.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

namespace brown_basketball {

namespace generation {
namespace flags {
using type = unsigned int;
enum : type {
  BASIC = 0b00,
  DRAFT_AWARE = 0b01,
  POSITION_AWARE = 0b10,
};
} // namespace flags

std::array<common::team, common::g_k_league_size> generate_league(
    const std::array<common::player, common::g_k_pool_size> &database,
    const flags::type flags);

namespace impl {
struct index {
  std::size_t m_idx;
  bool m_used;
};

using step1_generation_func_t = std::array<index, common::g_k_pool_size> (*)(
    std::array<index, common::g_k_pool_size> &&indices,
    const std::array<common::player, common::g_k_pool_size> &database,
    my_random::random &rand);

using step2_generation_func_t = std::array<
    std::array<index, common::g_k_team_size>, common::g_k_league_size> (*)(
    std::array<index, common::g_k_pool_size> &&indices,
    const std::array<common::player, common::g_k_pool_size> &database,
    my_random::random &rand);

std::array<common::team, common::g_k_league_size> generate_league(
    const std::array<common::player, common::g_k_pool_size> &database,
    const flags::type flags);

std::array<index, common::g_k_pool_size> basic_step1_generation(
    std::array<index, common::g_k_pool_size> &&indices,
    [[maybe_unused]] const std::array<common::player, common::g_k_pool_size>
        &database,
    my_random::random &rand);

std::array<index, common::g_k_pool_size> draft_aware_step1_generation(
    std::array<index, common::g_k_pool_size> &&indices,
    const std::array<common::player, common::g_k_pool_size> &database,
    my_random::random &rand);

// superior in theory, non-functional in practice
std::array<index, common::g_k_pool_size> draft_aware_step1_generation_alt(
    std::array<index, common::g_k_pool_size> &&indices,
    const std::array<common::player, common::g_k_pool_size> &database,
    my_random::random &rand);

std::array<std::array<index, common::g_k_team_size>, common::g_k_league_size>
basic_step2_generation(
    std::array<index, common::g_k_pool_size> &&indices,
    [[maybe_unused]] const std::array<common::player, common::g_k_pool_size>
        &database,
    [[maybe_unused]] my_random::random &rand);

std::array<std::array<index, common::g_k_team_size>, common::g_k_league_size>
position_aware_step2_generation(
    std::array<index, common::g_k_pool_size> &&indices,
    const std::array<common::player, common::g_k_pool_size> &database,
    my_random::random &rand);
} // namespace impl
} // namespace generation
} // namespace brown_basketball
#endif
