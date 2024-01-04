#include "generation.hpp"

#include "random.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream> // TODO XXX DEBUG
#include <random>

std::array<common::team, common::g_k_league_size> generation::generate_league(
    const std::array<common::player, common::g_k_pool_size> &database,
    const flags::type flags) {
  return impl::generate_league(database, flags);
}

std::array<common::team, common::g_k_league_size>
generation::impl::generate_league(
    const std::array<common::player, common::g_k_pool_size> &database,
    const flags::type flags) {
  step1_generation_func_t step1_generation_func{
      (flags & flags::DRAFT_AWARE) ? (draft_aware_step1_generation)
                                   : (basic_step1_generation)};
  step2_generation_func_t step2_generation_func{
      (flags & flags::POSITION_AWARE) ? (position_aware_step2_generation)
                                      : (basic_step2_generation)};

  std::array<index, common::g_k_pool_size> indices{};
  for (std::size_t i_index{0}; i_index < indices.size(); ++i_index) {
    indices[i_index] = {i_index, false};
  }

  my_rand::random rand{};

  std::array<std::array<index, common::g_k_team_size>, common::g_k_league_size>
      gen_ret_val{step2_generation_func(
          step1_generation_func(std::move(indices), database, rand), database,
          rand)};

  std::array<common::team, common::g_k_league_size> ret_val{};

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    for (std::size_t i_player{0}; i_player < common::g_k_team_size;
         ++i_player) {
      ret_val[i_team].m_players[i_player] =
          &(database[gen_ret_val[i_team][i_player].m_idx]);
    }
  }

  return ret_val;
}

std::array<generation::impl::index, common::g_k_pool_size>
generation::impl::basic_step1_generation(
    std::array<index, common::g_k_pool_size> &&indices,
    [[maybe_unused]] const std::array<common::player, common::g_k_pool_size>
        &database,
    my_rand::random &rand) {
  std::shuffle(indices.begin(), indices.end(), rand.get_generator());
  return indices;
}

std::array<generation::impl::index, common::g_k_pool_size>
generation::impl::draft_aware_step1_generation(
    std::array<index, common::g_k_pool_size> &&indices,
    const std::array<common::player, common::g_k_pool_size> &database,
    my_rand::random &rand) {
  // TODO
}

std::array<std::array<generation::impl::index, common::g_k_team_size>,
           common::g_k_league_size>
generation::impl::basic_step2_generation(
    std::array<index, common::g_k_pool_size> &&indices,
    [[maybe_unused]] const std::array<common::player, common::g_k_pool_size>
        &database,
    [[maybe_unused]] my_rand::random &rand) {
  std::array<std::array<index, common::g_k_team_size>, common::g_k_league_size>
      ret_val{};
  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    for (std::size_t i_player{0}; i_player < common::g_k_team_size;
         ++i_player) {
      ret_val[i_team][i_player] =
          indices[(i_team * common::g_k_team_size) + i_player];
    }
  }
  return ret_val;
}

std::array<std::array<generation::impl::index, common::g_k_team_size>,
           common::g_k_league_size>
generation::impl::position_aware_step2_generation(
    std::array<index, common::g_k_pool_size> &&indices,
    const std::array<common::player, common::g_k_pool_size> &database,
    my_rand::random &rand) {
  enum class team_positions_specificity_1 : unsigned int {
    POINT_GUARD_1 = 0,
    SHOOTING_GUARD_1,
    SMALL_FORWARD_1,
    POWER_FORWARD_1,
    CENTER_1,
    CENTER_2,
    N,
  };

  enum class team_positions_specificity_2 : unsigned int {
    ANY_GUARD_1 = static_cast<unsigned int>(team_positions_specificity_1::N),
    ANY_FORWARD_1,
    N
  };

  enum class team_positions_specificity_3 : unsigned int {
    UTILITY_1 = static_cast<unsigned int>(team_positions_specificity_2::N),
    UTILITY_2,
    N
  };

  enum class team_positions : unsigned int {
    POINT_GUARD_1 =
        static_cast<unsigned int>(team_positions_specificity_1::POINT_GUARD_1),
    SHOOTING_GUARD_1 = static_cast<unsigned int>(
        team_positions_specificity_1::SHOOTING_GUARD_1),
    SMALL_FORWARD_1 = static_cast<unsigned int>(
        team_positions_specificity_1::SMALL_FORWARD_1),
    POWER_FORWARD_1 = static_cast<unsigned int>(
        team_positions_specificity_1::POWER_FORWARD_1),
    CENTER_1 =
        static_cast<unsigned int>(team_positions_specificity_1::CENTER_1),
    CENTER_2 =
        static_cast<unsigned int>(team_positions_specificity_1::CENTER_2),
    ANY_GUARD_1 =
        static_cast<unsigned int>(team_positions_specificity_2::ANY_GUARD_1),
    ANY_FORWARD_1 =
        static_cast<unsigned int>(team_positions_specificity_2::ANY_FORWARD_1),
    UTILITY_1 =
        static_cast<unsigned int>(team_positions_specificity_3::UTILITY_1),
    UTILITY_2 =
        static_cast<unsigned int>(team_positions_specificity_3::UTILITY_2),
    N
  };

  static_assert(static_cast<unsigned int>(team_positions::N) ==
                common::g_k_team_size);

  const auto compatible_player_postion{
      [](const team_positions pos,
         const common::position::type player) -> bool {
        switch (pos) {
        case team_positions::POINT_GUARD_1: {
          return (player & common::position::POINT_GUARD);
        } break;
        case team_positions::SHOOTING_GUARD_1: {
          return (player & common::position::SHOOTING_GUARD);
        } break;
        case team_positions::ANY_GUARD_1: {
          return ((player & common::position::POINT_GUARD) ||
                  (player & common::position::SHOOTING_GUARD));
        } break;
        case team_positions::SMALL_FORWARD_1: {
          return (player & common::position::SMALL_FORWARD);
        } break;
        case team_positions::POWER_FORWARD_1: {
          return (player & common::position::POWER_FORWARD);
        } break;
        case team_positions::ANY_FORWARD_1: {
          return ((player & common::position::SMALL_FORWARD) ||
                  (player & common::position::POWER_FORWARD));
        } break;
        case team_positions::CENTER_1:
        case team_positions::CENTER_2: {
          return (player & common::position::CENTER);
        } break;
        case team_positions::UTILITY_1:
        case team_positions::UTILITY_2: {
          return true;
        } break;
        default: {
          return false;
        } break;
        }
      }};

  std::array<std::array<team_positions, common::g_k_team_size>,
             common::g_k_league_size>
      team_pos_slots{};
  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    team_pos_slots[i_team] = {
        team_positions::POINT_GUARD_1,   team_positions::SHOOTING_GUARD_1,
        team_positions::SMALL_FORWARD_1, team_positions::POWER_FORWARD_1,
        team_positions::CENTER_1,        team_positions::CENTER_2,
        team_positions::ANY_GUARD_1,     team_positions::ANY_FORWARD_1,
        team_positions::UTILITY_1,       team_positions::UTILITY_2};

    const auto iter_team_position_specificity_1_begin{
        team_pos_slots[i_team].begin()};
    const auto iter_team_position_specificity_1_end{
        team_pos_slots[i_team].begin() +
        static_cast<unsigned int>(team_positions_specificity_1::N)};

    const auto iter_team_position_specificity_2_begin{
        iter_team_position_specificity_1_end};
    const auto iter_team_position_specificity_2_end{
        team_pos_slots[i_team].begin() +
        static_cast<unsigned int>(team_positions_specificity_2::N)};

    const auto iter_team_position_specificity_3_begin{
        iter_team_position_specificity_2_end};
    const auto iter_team_position_specificity_3_end{
        team_pos_slots[i_team].begin() +
        static_cast<unsigned int>(team_positions_specificity_3::N)};

    std::shuffle(iter_team_position_specificity_1_begin,
                 iter_team_position_specificity_1_end, rand.get_generator());
    std::shuffle(iter_team_position_specificity_2_begin,
                 iter_team_position_specificity_2_end, rand.get_generator());
    std::shuffle(iter_team_position_specificity_3_begin,
                 iter_team_position_specificity_3_end, rand.get_generator());
  }

  std::array<std::array<index, common::g_k_team_size>, common::g_k_league_size>
      ret_val{};

  for (std::size_t i_pos{0}; i_pos < common::g_k_team_size; ++i_pos) {
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      for (std::size_t i_player{0}; i_player < common::g_k_pool_size;
           ++i_player) {
        // TODO XXX DEBUG vvv
        if (indices[i_player].m_used == true) {
          std::cerr << "NO SUITABLE PLAYERS\n";
          std::exit(1);
        }
        // TODO XXX DEBUG ^^^
        if (compatible_player_postion(
                team_pos_slots[i_team][i_pos],
                database[indices[i_player].m_idx].m_info.m_positions)) {
          indices[i_player].m_used = true;
          ret_val[i_team][i_pos] = indices[i_player];
          std::rotate((indices.begin() + i_player),
                      (indices.begin() + i_player + 1), (indices.end()));
          break;
        }
      }
    }
  }

  return ret_val;
}
