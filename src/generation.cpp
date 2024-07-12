#include "generation.hpp"

#include "common.hpp"
#include "my_random.hpp"

#include "bits-and-bytes/move_elem_to.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <vector>

std::array<brown_basketball::common::team,
           brown_basketball::common::k_league_size>
brown_basketball::generation::generate_league(
    const std::array<common::player, common::k_pool_size> &database,
    const flags flags) {
  return impl::generate_league(database, flags);
}

std::array<brown_basketball::common::team,
           brown_basketball::common::k_league_size>
brown_basketball::generation::impl::generate_league(
    const std::array<common::player, common::k_pool_size> &database,
    const flags flags) {

  step1_generation_func_t step1_generation_func{[flags]()
                                                    -> step1_generation_func_t {
    if (static_cast<bool>(flags & flags::draft_aware) &&
        static_cast<bool>(flags & flags::random_epiphany_thingy)) {
      throw std::runtime_error{
          "generation::flags::draft_aware and "
          "generation::flags::random_epiphany_thingy are mutually exclusive"};
    } else if (static_cast<bool>(flags & flags::draft_aware)) {
      return step1_generation_draft_aware;
    } else if (static_cast<bool>(flags & flags::random_epiphany_thingy)) {
      return step1_generation_random_epiphany_thingy;
    } else {
      return step1_generation_basic;
    }
  }()};

  step2_generation_func_t step2_generation_func{[flags]()
                                                    -> step2_generation_func_t {
    if (static_cast<bool>(flags & flags::position_aware) &&
        static_cast<bool>(flags & flags::random_epiphany_thingy)) {
      throw std::runtime_error{
          "generation::flags::position_aware and "
          "generation::flags::random_epiphany_thingy are mutually exclusive"};
    } else if (static_cast<bool>(flags & flags::position_aware)) {
      return step2_generation_position_aware;
    } else if (static_cast<bool>(flags & flags::random_epiphany_thingy)) {
      return step2_generation_random_epiphany_thingy;
    } else {
      return step2_generation_basic;
    }
  }()};

  std::array<index, common::k_pool_size> indices{};
  for (std::size_t i_index{0}; i_index < indices.size(); ++i_index) {
    indices[i_index] = {i_index, false};
  }

  my_random::random rand{};

  std::array<std::array<index, common::k_team_size>, common::k_league_size>
      gen_ret_val{step2_generation_func(
          step1_generation_func(std::move(indices), database, rand), database,
          rand)};

  std::array<common::team, common::k_league_size> ret_val{};

  assert(common::k_league_size == ret_val.size());
  for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
    assert(common::k_team_size == ret_val[i_team].m_players.size());
    for (std::size_t i_player{0}; i_player < common::k_team_size; ++i_player) {
      ret_val[i_team].m_players[i_player] =
          &(database[gen_ret_val[i_team][i_player].m_idx]);
    }
  }

  return ret_val;
}

std::array<brown_basketball::generation::impl::index,
           brown_basketball::common::k_pool_size>
brown_basketball::generation::impl::step1_generation_basic(
    std::array<index, common::k_pool_size> &&indices,
    [[maybe_unused]] const std::array<common::player, common::k_pool_size>
        &database,
    my_random::random &rand) {
  std::shuffle(indices.begin(), indices.end(), rand.get_generator());
  return indices;
}

std::array<brown_basketball::generation::impl::index,
           brown_basketball::common::k_pool_size>
brown_basketball::generation::impl::step1_generation_draft_aware(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand) {
  const auto draft_range_midpoint{
      [](const common::player &player)
          -> decltype(common::info::m_draft_range_begin) {
        return ((player.m_info.m_draft_range_begin +
                 player.m_info.m_draft_range_end) /
                2);
      }};
  std::sort(indices.begin(), indices.end(),
            [&database, &draft_range_midpoint](const index &i1,
                                               const index &i2) -> bool {
              return ((draft_range_midpoint(database[i1.m_idx])) <
                      (draft_range_midpoint(database[i2.m_idx])));
            });

  static constexpr std::size_t k_bin_size{
      10}; // TODO what is a good bin_size? smaller means that players are more
           // likely to be drafted in their range, larger means more randomness

  assert(common::k_pool_size == indices.size());
  for (std::size_t i_player{0}; i_player < common::k_pool_size;
       i_player += k_bin_size) {
    std::shuffle((indices.begin() + i_player),
                 (((i_player + k_bin_size) < indices.size())
                      ? (indices.begin() + i_player + k_bin_size)
                      : (indices.end())),
                 rand.get_generator());
  }

  return indices;
}

std::array<brown_basketball::generation::impl::index,
           brown_basketball::common::k_pool_size>
brown_basketball::generation::impl::step1_generation_draft_aware_alt(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand) {
  std::shuffle(indices.begin(), indices.end(), rand.get_generator());

  std::array<index, common::k_pool_size> indices_res;

  const auto find_spot_for_player{[&indices_res, &database,
                                   &rand](const index &player) -> void {
    decltype(index::m_idx) cur_index{player.m_idx};

    while (true) {
      std::vector<std::size_t> valid_pos(
          (database[cur_index].m_info.m_draft_range_end -
           database[cur_index].m_info.m_draft_range_begin) +
          1);
      std::iota(valid_pos.begin(), valid_pos.end(),
                database[cur_index].m_info.m_draft_range_begin);
      std::shuffle(valid_pos.begin(), valid_pos.end(), rand.get_generator());

      for (std::size_t i_valid_pos{0}; i_valid_pos < valid_pos.size();
           ++i_valid_pos) {
        if (indices_res[valid_pos[i_valid_pos]].m_used == false) {
          indices_res[valid_pos[i_valid_pos]].m_used = true;
          indices_res[valid_pos[i_valid_pos]].m_idx = cur_index;
          return;
        }
      }

      decltype(index::m_idx) temp = indices_res[valid_pos[0]].m_idx;
      indices_res[valid_pos[0]].m_idx = cur_index;
      cur_index = temp;
    }
  }};

  assert(common::k_pool_size == indices.size());
  for (std::size_t i_player{0}; i_player < common::k_pool_size; ++i_player) {
    find_spot_for_player(indices[i_player]);
  }

  return indices_res;
}

std::array<brown_basketball::generation::impl::index,
           brown_basketball::common::k_pool_size>
brown_basketball::generation::impl::step1_generation_random_epiphany_thingy(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand) {
  assert(common::k_pool_size == 144);

  std::sort(indices.begin(), indices.end(),
            [&database](const index &i1, const index &i2) -> bool {
              return ((database[i1.m_idx].m_info.m_rank) <
                      (database[i2.m_idx].m_info.m_rank));
            });

  std::shuffle(indices.begin(), (indices.begin() + 6), rand.get_generator());
  bits_and_bytes::move_elem_to::move_elem_to((indices.data() + 11),
                                             (indices.data() + 6));
  bits_and_bytes::move_elem_to::move_elem_to((indices.data() + 13),
                                             (indices.data() + 7));
  bits_and_bytes::move_elem_to::move_elem_to((indices.data() + 23),
                                             (indices.data() + 8));
  std::shuffle((indices.begin() + 6), (indices.begin() + 9),
               rand.get_generator());
  std::shuffle((indices.begin() + 9), (indices.begin() + 36),
               rand.get_generator());
  std::shuffle((indices.begin() + 6), (indices.begin() + 12),
               rand.get_generator());

  // OLD vvv
  // std::shuffle((indices.begin() + 23), (indices.begin() + 120),
  //              rand.get_generator());
  // OLD ^^^
  // NEW vvv
  std::shuffle((indices.begin() + 23), (indices.begin() + 75),
               rand.get_generator());
  std::shuffle((indices.begin() + 60), (indices.begin() + 120),
               rand.get_generator());
  std::shuffle((indices.begin() + 96), (indices.begin() + 120),
               rand.get_generator());
  // NEW ^^^

  std::shuffle((indices.begin() + 120), (indices.begin() + 144),
               rand.get_generator());

  return indices;
}

std::array<std::array<brown_basketball::generation::impl::index,
                      brown_basketball::common::k_team_size>,
           brown_basketball::common::k_league_size>
brown_basketball::generation::impl::step2_generation_basic(
    std::array<index, common::k_pool_size> &&indices,
    [[maybe_unused]] const std::array<common::player, common::k_pool_size>
        &database,
    [[maybe_unused]] my_random::random &rand) {
  std::array<std::array<index, common::k_team_size>, common::k_league_size>
      ret_val{};
  assert(common::k_team_size == ret_val.front().size());
  for (std::size_t i_player{0}; i_player < common::k_team_size; ++i_player) {
    assert(common::k_league_size == ret_val.size());
    for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
      ret_val[i_team][i_player] =
          indices[(i_player * common::k_league_size) + i_team];
    }
  }
  return ret_val;
}

std::array<std::array<brown_basketball::generation::impl::index,
                      brown_basketball::common::k_team_size>,
           brown_basketball::common::k_league_size>
brown_basketball::generation::impl::step2_generation_position_aware(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    my_random::random &rand) {
  enum class team_positions_specificity_1 : unsigned int {
    point_guard_1 = 0,
    shooting_guard_1,
    small_forward_1,
    power_forward_1,
    center_1,
    center_2,
    N,
  };

  enum class team_positions_specificity_2 : unsigned int {
    any_guard_1 = static_cast<unsigned int>(team_positions_specificity_1::N),
    any_forward_1,
    N
  };

  enum class team_positions_specificity_3 : unsigned int {
    utility_1 = static_cast<unsigned int>(team_positions_specificity_2::N),
    utility_2,
    N
  };

  enum class team_positions : unsigned int {
    point_guard_1 =
        static_cast<unsigned int>(team_positions_specificity_1::point_guard_1),
    shooting_guard_1 = static_cast<unsigned int>(
        team_positions_specificity_1::shooting_guard_1),
    small_forward_1 = static_cast<unsigned int>(
        team_positions_specificity_1::small_forward_1),
    power_forward_1 = static_cast<unsigned int>(
        team_positions_specificity_1::power_forward_1),
    center_1 =
        static_cast<unsigned int>(team_positions_specificity_1::center_1),
    center_2 =
        static_cast<unsigned int>(team_positions_specificity_1::center_2),
    any_guard_1 =
        static_cast<unsigned int>(team_positions_specificity_2::any_guard_1),
    any_forward_1 =
        static_cast<unsigned int>(team_positions_specificity_2::any_forward_1),
    utility_1 =
        static_cast<unsigned int>(team_positions_specificity_3::utility_1),
    utility_2 =
        static_cast<unsigned int>(team_positions_specificity_3::utility_2),
    N
  };

  const auto compatible_player_postion{
      [](const team_positions pos, const common::position player) -> bool {
        switch (pos) {
        case team_positions::point_guard_1: {
          return static_cast<bool>(player & common::position::point_guard);
        } break;
        case team_positions::shooting_guard_1: {
          return static_cast<bool>(player & common::position::shooting_guard);
        } break;
        case team_positions::any_guard_1: {
          return static_cast<bool>(
              static_cast<bool>(player & common::position::point_guard) ||
              static_cast<bool>(player & common::position::shooting_guard));
        } break;
        case team_positions::small_forward_1: {
          return static_cast<bool>(player & common::position::small_forward);
        } break;
        case team_positions::power_forward_1: {
          return static_cast<bool>(player & common::position::power_forward);
        } break;
        case team_positions::any_forward_1: {
          return static_cast<bool>(
              static_cast<bool>(player & common::position::small_forward) ||
              static_cast<bool>(player & common::position::power_forward));
        } break;
        case team_positions::center_1:
        case team_positions::center_2: {
          return static_cast<bool>(player & common::position::center);
        } break;
        case team_positions::utility_1:
        case team_positions::utility_2: {
          return true;
        } break;
        default: {
          return false;
        } break;
        }
      }};

  if constexpr (static_cast<unsigned int>(team_positions::N) !=
                common::k_team_size) {
    throw std::runtime_error{"position-aware league generation unvailable if "
                             "team size does not equal position count"};
  }

  std::array<std::array<team_positions, common::k_team_size>,
             common::k_league_size>
      team_pos_slots{};
  for (std::size_t i_team{0}; i_team < team_pos_slots.size(); ++i_team) {
    team_pos_slots[i_team] = {
        team_positions::point_guard_1,   team_positions::shooting_guard_1,
        team_positions::small_forward_1, team_positions::power_forward_1,
        team_positions::center_1,        team_positions::center_2,
        team_positions::any_guard_1,     team_positions::any_forward_1,
        team_positions::utility_1,       team_positions::utility_2};

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

  std::array<std::array<index, common::k_team_size>, common::k_league_size>
      ret_val{};

  assert((common::k_team_size == team_pos_slots.front().size()) &&
         (common::k_team_size == ret_val.front().size()));
  for (std::size_t i_pos{0}; i_pos < common::k_team_size; ++i_pos) {
    assert((common::k_league_size == ret_val.size()) &&
           (common::k_league_size == team_pos_slots.size()));
    for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
      assert(common::k_pool_size == indices.size());
      for (std::size_t i_player{0}; i_player < common::k_pool_size;
           ++i_player) {
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

std::array<std::array<brown_basketball::generation::impl::index,
                      brown_basketball::common::k_team_size>,
           brown_basketball::common::k_league_size>
brown_basketball::generation::impl::step2_generation_random_epiphany_thingy(
    std::array<index, common::k_pool_size> &&indices,
    const std::array<common::player, common::k_pool_size> &database,
    [[maybe_unused]] my_random::random &rand) {
  // OLD vvv
  // std::size_t center_pos_count_total{[&database]() -> std::size_t {
  //   std::size_t sum{0};
  //   assert(common::k_pool_size == database.size());
  //   for (std::size_t i{0}; i < common::k_pool_size; ++i) {
  //     if (static_cast<bool>(database[i].m_info.m_positions &
  //                           common::position::center)) {
  //       ++sum;
  //     }
  //   }
  //   return sum;
  // }()};
  // static constexpr std::size_t center_pos_count_min{3};
  // static constexpr std::size_t center_pos_count_max{5};
  // std::size_t center_pos_count_required{common::k_league_size *
  //                                       center_pos_count_min};
  //
  // std::array<std::size_t, common::k_team_size> center_pos_count_teams{};
  //
  // std::array<std::array<index, common::k_team_size>, common::k_league_size>
  //     ret_val{};
  //
  // std::size_t first_unused_index{0};
  //
  // assert(common::k_team_size == ret_val.front().size());
  // for (std::size_t i_player{0}; i_player < common::k_team_size; ++i_player) {
  //   assert((common::k_league_size == ret_val.size()) &&
  //          (common::k_league_size == center_pos_count_teams.size()));
  //   for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
  //     bool skipped_indices{false};
  //     assert(common::k_pool_size == indices.size());
  //     for (std::size_t i_index{first_unused_index};
  //          i_index < common::k_pool_size; ++i_index) {
  //       if (bool is_center_pos{static_cast<bool>(
  //               database[indices[i_index].m_idx].m_info.m_positions &
  //               common::position::center)};
  //           (indices[i_index].m_used == false) &&
  //           (
  //
  //               ((is_center_pos) &&
  //                (center_pos_count_teams[i_team] < center_pos_count_min))
  //
  //               ||
  //
  //               ((!is_center_pos) &&
  //                (center_pos_count_teams[i_team] >= center_pos_count_min))
  //
  //               ||
  //
  //               ((is_center_pos) &&
  //                (center_pos_count_teams[i_team] < center_pos_count_max) &&
  //                ((center_pos_count_total - 1) >=
  //                (center_pos_count_required)))
  //
  //                   )) {
  //         indices[i_index].m_used = true;
  //         ret_val[i_team][i_player] = indices[i_index];
  //         if (static_cast<bool>(
  //                 database[ret_val[i_team][i_player].m_idx].m_info.m_positions
  //                 & common::position::center)) {
  //           ++center_pos_count_teams[i_team];
  //           --center_pos_count_total;
  //           if (center_pos_count_teams[i_team] <= center_pos_count_min) {
  //             --center_pos_count_required;
  //           }
  //         }
  //         if (!skipped_indices) {
  //           first_unused_index = i_index + 1;
  //         }
  //         break;
  //       } else {
  //         skipped_indices = true;
  //         continue;
  //       }
  //     }
  //   }
  // }
  //
  // return ret_val;
  // OLD ^^^
  // NEW vvv
  return step2_generation_basic(std::move(indices), database, rand);
  // NEW ^^^
}
