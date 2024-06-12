#include "analysis1.hpp"

#include "common.hpp"
#include "scoring.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

brown_basketball::analysis1::accum_state::accum_state(
    const std::array<common::player, common::k_pool_size> &database)
    : m_accum_state{impl::accum_state_init_accum_state(database)},
      m_trial_count{impl::accum_state_init_trial_count()} {}

void brown_basketball::analysis1::accum_state::add(const add_t &league) {
  impl::accum_state_add(m_accum_state, m_trial_count, league);
}

brown_basketball::analysis1::read_t
brown_basketball::analysis1::accum_state::read() const {
  return impl::accum_state_read(m_accum_state, m_trial_count);
}

brown_basketball::analysis1::accum_state_t
brown_basketball::analysis1::impl::accum_state_init_accum_state(
    const std::array<common::player, common::k_pool_size> &database) {
  accum_state_t ret_val{};

  assert(common::k_pool_size == database.size());
  for (std::size_t i_player{0}; i_player < common::k_pool_size; ++i_player) {
    ret_val[i_player].first = &(database[i_player]);
  }

  return ret_val;
}

unsigned long
brown_basketball::analysis1::impl::accum_state_init_trial_count() {
  return 0;
}

void brown_basketball::analysis1::impl::accum_state_add(
    accum_state_t &accum_state, unsigned long &trial_count,
    const std::array<scoring::team_ranks, common::k_league_size> &league) {
  assert(common::k_league_size == league.size());
  for (std::size_t i_team{0}; i_team < common::k_league_size; ++i_team) {
    for (auto p_player{league[i_team].m_team->m_players.begin()};
         p_player != league[i_team].m_team->m_players.end(); ++p_player) {
      ++(accum_state[(*p_player)->m_idx].second.m_trial_count);
      assert(static_cast<std::size_t>(common::category::N) ==
             league[i_team].m_ranks.size());
      for (std::size_t i_cat{0};
           i_cat < static_cast<std::size_t>(common::category::N); ++i_cat) {
        if (league[i_team].m_ranks[i_cat] == common::k_rank_top) {
          ++(accum_state[(*p_player)->m_idx].second.m_rank_counts[i_cat].m_top);
        }
        if (league[i_team].m_ranks[i_cat] <= common::k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts[i_cat]
                 .m_cutoff);
        }
      }
    }
  }

  ++trial_count;
}

brown_basketball::analysis1::read_t
brown_basketball::analysis1::impl::accum_state_read(
    const accum_state_t &accum_state,
    [[maybe_unused]] const unsigned long trial_count) {
  read_t ret_val{};

  assert(common::k_pool_size == accum_state.size());
  for (std::size_t i_player{0}; i_player < common::k_pool_size; ++i_player) {
    ret_val[i_player].first = accum_state[i_player].first;
  }

  assert(common::k_pool_size == accum_state.size());
  for (std::size_t i_player{0}; i_player < common::k_pool_size; ++i_player) {
    assert((static_cast<std::size_t>(common::category::N) ==
            ret_val[i_player].second.size()) &&
           (static_cast<std::size_t>(common::category::N) ==
            accum_state[i_player].second.m_rank_counts.size()));
    for (std::size_t i_cat{0};
         i_cat < static_cast<std::size_t>(common::category::N); ++i_cat) {
      ret_val[i_player].second[i_cat].m_top =
          (accum_state[i_player].second.m_rank_counts[i_cat].m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second[i_cat].m_cutoff =
          (accum_state[i_player].second.m_rank_counts[i_cat].m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
    }
  }

  return ret_val;
}
