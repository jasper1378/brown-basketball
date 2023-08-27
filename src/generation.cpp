#include "generation.hpp"

#include "random.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

std::array<common::team, common::g_k_league_size> generation::generate_league(
    const std::array<common::player, common::g_k_player_count> &database,
    const generation_type gen_type) {
  return impl::generate_league(database, gen_type);
}

std::array<common::team, common::g_k_league_size>
generation::impl::generate_league(
    const std::array<common::player, common::g_k_player_count> &database,
    const generation_type gen_type) {
  std::array<index, common::g_k_player_count> indices{};
  for (std::size_t i_index{0}; i_index < indices.size(); ++i_index) {
    indices[i_index] = {i_index, false};
  }

  my_rand::random rand{};

  switch (gen_type) {
  case generation_type::BASIC: {
    basic_generation(indices, database, rand);
  } break;
  }

  std::array<common::team, common::g_k_league_size> ret_val{};

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    common::team cur_team{};
    for (std::size_t i_player{0}; i_player < common::g_k_team_size;
         ++i_player) {
      cur_team.m_players[i_player] =
          database[indices[(i_team * common::g_k_team_size) + i_player].m_idx];
    }
  }

  return ret_val;
}

void generation::impl::basic_generation(
    std::array<index, common::g_k_player_count> &indices,
    [[maybe_unused]] const std::array<common::player, common::g_k_player_count>
        &database,
    my_rand::random &rand) {
  std::shuffle(indices.begin(), indices.end(), rand.get_generator());
}
