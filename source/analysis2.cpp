#include "analysis2.hpp"

#include "bits-and-bytes/stats/stats.hpp"
#include "common.hpp"
#include "scoring.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>

brown_basketball::analysis2::accum_state::accum_state()
    : m_accum_state{impl::accum_state_init_accum_state()},
      m_trial_count{impl::accum_state_init_total_trial_count()} {}

void brown_basketball::analysis2::accum_state::add(const add_t &league) {
  impl::accum_state_add(m_accum_state, m_trial_count, league);
}

brown_basketball::analysis2::read_t
brown_basketball::analysis2::accum_state::read() const {
  return impl::accum_state_read(m_accum_state, m_trial_count);
}

brown_basketball::analysis2::accum_state_t
brown_basketball::analysis2::impl::accum_state_init_accum_state() {
  accum_state_t ret_val{};

  assert(static_cast<std::size_t>(common::category::N) == ret_val.size());
  for (std::size_t i_cat_1{0};
       i_cat_1 < static_cast<std::size_t>(common::category::N); ++i_cat_1) {
    assert(common::g_k_league_size == ret_val[i_cat_1].size());
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      assert(static_cast<std::size_t>(common::category::N) ==
             ret_val[i_cat_1][i_team].size());
      for (std::size_t i_cat_2{0}; i_cat_2 < ret_val[i_cat_1][i_team].size();
           ++i_cat_2) {
        ret_val[i_cat_1][i_team][i_cat_2].resize(
            brown_basketball::common::g_k_trial_count);
      }
    }
  }

  return ret_val;
}

unsigned long
brown_basketball::analysis2::impl::accum_state_init_total_trial_count() {
  return 0;
}

void brown_basketball::analysis2::impl::accum_state_add(
    accum_state_t &accum_state, unsigned long &trial_count,
    const add_t &league) {
  assert(common::g_k_league_size == league.second.size());
  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    assert(
        (static_cast<std::size_t>(common::category::N) == accum_state.size()) &&
        ((static_cast<std::size_t>(common::category::N) ==
          league.second[i_team].m_ranks.size())));
    for (std::size_t i_cat_1{0};
         i_cat_1 < static_cast<std::size_t>(common::category::N); ++i_cat_1) {
      assert((static_cast<std::size_t>(common::category::N) ==
              accum_state[i_cat_1][league.second[i_team].m_ranks[i_cat_1] - 1]
                  .size()) &&
             (static_cast<std::size_t>(common::category::N) ==
              league.first[i_team].m_stats.size()));
      for (std::size_t i_cat_2{0};
           i_cat_2 < static_cast<std::size_t>(common::category::N); ++i_cat_2) {
        accum_state[i_cat_1][league.second[i_team].m_ranks[i_cat_1] - 1]
                   [i_cat_2][trial_count] =
                       league.first[i_team].m_stats[i_cat_2];
      }
    }
  }
  ++trial_count;
}

brown_basketball::analysis2::read_t
brown_basketball::analysis2::impl::accum_state_read(
    const accum_state_t &accum_state,
    [[maybe_unused]] const unsigned long trial_count) {
  read_t ret_val{};

  assert((static_cast<std::size_t>(common::category::N) == ret_val.size()) &&
         (static_cast<std::size_t>(common::category::N) == accum_state.size()));
  for (std::size_t i_cat_1{0};
       i_cat_1 < static_cast<std::size_t>(common::category::N); ++i_cat_1) {
    assert((common::g_k_league_size == ret_val[i_cat_1].size()) &&
           (common::g_k_league_size == accum_state[i_cat_1].size()));
    for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
      assert((static_cast<std::size_t>(common::category::N) ==
              ret_val[i_cat_1][i_team].size()) &&
             (static_cast<std::size_t>(common::category::N) ==
              accum_state[i_cat_1][i_team].size()));
      for (std::size_t i_cat_2{0};
           i_cat_2 < static_cast<std::size_t>(common::category::N); ++i_cat_2) {
        ret_val[i_cat_1][i_team][i_cat_2].m_mean =
            bits_and_bytes::stats::mean<double>(
                accum_state[i_cat_1][i_team][i_cat_2].begin(),
                accum_state[i_cat_1][i_team][i_cat_2].end());
        ret_val[i_cat_1][i_team][i_cat_2].m_min =
            bits_and_bytes::stats::min<double>(
                accum_state[i_cat_1][i_team][i_cat_2].begin(),
                accum_state[i_cat_1][i_team][i_cat_2].end());
        ret_val[i_cat_1][i_team][i_cat_2].m_max =
            bits_and_bytes::stats::max<double>(
                accum_state[i_cat_1][i_team][i_cat_2].begin(),
                accum_state[i_cat_1][i_team][i_cat_2].end());
        ret_val[i_cat_1][i_team][i_cat_2].m_stdev =
            bits_and_bytes::stats::stdev<double>(
                accum_state[i_cat_1][i_team][i_cat_2].begin(),
                accum_state[i_cat_1][i_team][i_cat_2].end(),
                ret_val[i_cat_1][i_team][i_cat_2].m_mean);
      }
    }
  }

  return ret_val;
}
