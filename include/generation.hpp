#ifndef BROWN_BASKETBALL_GENERATION_HPP
#define BROWN_BASKETBALL_GENERATION_HPP

#include "common.hpp"

#include "my_random.hpp"

#include <array>
#include <cstddef>

namespace brown_basketball {

namespace generation {

enum class flags : unsigned int {
  basic = 0b00,
  draft_aware = 0b01,
  position_aware = 0b10,
};
BITS_AND_BYTES_DEFINE_ENUM_FLAG_OPERATORS_FOR_TYPE(flags);

std::array<common::team, common::k_league_size> generate_league(
    const std::array<common::player, common::k_pool_size> &database,
    const flags flags);

namespace impl {
struct index {
  std::size_t m_idx;
  bool m_used;
};

using step1_generation_func_t = std::array<index, common::k_pool_size> (*)(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand);

using step2_generation_func_t = std::array<
    std::array<index, common::k_team_size>, common::k_league_size> (*)(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand);

std::array<common::team, common::k_league_size> generate_league(
    const std::array<common::player, common::k_pool_size> &database,
    const flags flags);

std::array<index, common::k_pool_size> basic_step1_generation(
    std::array<index, common::k_pool_size> &&indices,
    [[maybe_unused]] const std::array<common::player, common::k_pool_size>
        &database,
    my_random::random &rand);

std::array<index, common::k_pool_size> draft_aware_step1_generation(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand);

// this method is superior in theory, but not feasible in practice :(
std::array<index, common::k_pool_size> draft_aware_step1_generation_alt(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand);

std::array<std::array<index, common::k_team_size>, common::k_league_size>
basic_step2_generation(
    std::array<index, common::k_pool_size> &&indices,
    [[maybe_unused]] const std::array<common::player, common::k_pool_size>
        &database,
    [[maybe_unused]] my_random::random &rand);

std::array<std::array<index, common::k_team_size>, common::k_league_size>
position_aware_step2_generation(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand);
} // namespace impl
} // namespace generation
} // namespace brown_basketball
#endif
