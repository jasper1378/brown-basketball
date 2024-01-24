#include "analysis.hpp"

#include "common.hpp"
#include "scoring.hpp"

#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

brown_basketball::analysis::accum_state::accum_state(
    const std::array<brown_basketball::common::player,
                     brown_basketball::common::g_k_pool_size> &database)
    : m_accum_state{impl::accum_state_init_accum_state(database)},
      m_total_trial_count(impl::accum_state_init_total_trial_count()) {}

void brown_basketball::analysis::accum_state::add(
    const std::array<brown_basketball::scoring::team_ranks,
                     brown_basketball::common::g_k_league_size> &league) {
  impl::accum_state_add(m_accum_state, m_total_trial_count, league);
}

const std::array<std::pair<const brown_basketball::common::player *,
                           brown_basketball::analysis::rank_probs>,
                 brown_basketball::common::g_k_pool_size> &
brown_basketball::analysis::accum_state::read() const {
  return impl::accum_state_read(m_accum_state, m_total_trial_count);
}

std::array<std::pair<const brown_basketball::common::player *,
                     brown_basketball::analysis::impl::trial_rank_counts>,
           brown_basketball::common::g_k_pool_size>
brown_basketball::analysis::impl::accum_state_init_accum_state(
    const std::array<brown_basketball::common::player,
                     brown_basketball::common::g_k_pool_size> &database) {
  std::array<
      std::pair<const brown_basketball::common::player *, trial_rank_counts>,
      brown_basketball::common::g_k_pool_size>
      ret_val{};

  for (std::size_t i_player{0}; i_player < database.size(); ++i_player) {
    ret_val[i_player].first = &(database[i_player]);
  }

  return ret_val;
}

unsigned long
brown_basketball::analysis::impl::accum_state_init_total_trial_count() {
  return 0;
}

void brown_basketball::analysis::impl::accum_state_add(
    std::array<std::pair<const brown_basketball::common::player *,
                         brown_basketball::analysis::impl::trial_rank_counts>,
               brown_basketball::common::g_k_pool_size> &accum_state,
    unsigned long &total_trial_count,
    const std::array<brown_basketball::scoring::team_ranks,
                     brown_basketball::common::g_k_league_size> &league) {

  ++total_trial_count;

  for (auto p_team{league.begin()}; p_team != league.end(); ++p_team) {
    for (auto p_player{p_team->m_team->m_players.begin()};
         p_player != p_team->m_team->m_players.end(); ++p_player) {
      ++(accum_state[(*p_player)->m_idx].second.m_trial_count);
      {
        if (p_team->m_ranks.m_points ==
            brown_basketball::common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_points.m_top);
        }
        if (p_team->m_ranks.m_points <=
            brown_basketball::common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_points.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_rebounds ==
            brown_basketball::common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_rebounds.m_top);
        }
        if (p_team->m_ranks.m_rebounds <=
            brown_basketball::common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_rebounds.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_assists ==
            brown_basketball::common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_assists.m_top);
        }
        if (p_team->m_ranks.m_assists <=
            brown_basketball::common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_assists.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_steals ==
            brown_basketball::common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_steals.m_top);
        }
        if (p_team->m_ranks.m_steals <=
            brown_basketball::common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_steals.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_blocks ==
            brown_basketball::common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_blocks.m_top);
        }
        if (p_team->m_ranks.m_blocks <=
            brown_basketball::common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_blocks.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_threes ==
            brown_basketball::common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_threes.m_top);
        }
        if (p_team->m_ranks.m_threes <=
            brown_basketball::common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_threes.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_field_goals ==
            brown_basketball::common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_field_goals.m_top);
        }
        if (p_team->m_ranks.m_field_goals <=
            brown_basketball::common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_field_goals.m_cutoff);
        }
      }
      {
        if (p_team->m_ranks.m_free_throws ==
            brown_basketball::common::g_k_rank_top) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_free_throws.m_top);
        }
        if (p_team->m_ranks.m_free_throws <=
            brown_basketball::common::g_k_rank_cutoff) {
          ++(accum_state[(*p_player)->m_idx]
                 .second.m_rank_counts.m_free_throws.m_cutoff);
        }
      }
    }
  }
}

const std::array<std::pair<const brown_basketball::common::player *,
                           brown_basketball::analysis::rank_probs>,
                 brown_basketball::common::g_k_pool_size> &
brown_basketball::analysis::impl::accum_state_read(
    const std::array<std::pair<const brown_basketball::common::player *,
                               impl::trial_rank_counts>,
                     brown_basketball::common::g_k_pool_size> &accum_state,
    const unsigned long total_trial_count) {

  static std::array<std::pair<const brown_basketball::common::player *,
                              brown_basketball::analysis::rank_probs>,
                    brown_basketball::common::g_k_pool_size>
      ret_val{};

  static bool first_call{true};
  if (first_call == true) {
    first_call = false;
    for (std::size_t i_player{0}; i_player < accum_state.size(); ++i_player) {
      ret_val[i_player].first = accum_state[i_player].first;
    }
  }

  static const std::array<std::pair<const brown_basketball::common::player *,
                                    impl::trial_rank_counts>,
                          brown_basketball::common::g_k_pool_size>
      *prev_accum_state{&accum_state};
  static bool prev_total_trial_count{0};

  if ((prev_accum_state != &accum_state) ||
      (prev_total_trial_count != total_trial_count)) {
    for (std::size_t i_player{0}; i_player < accum_state.size(); ++i_player) {

      ret_val[i_player].second.m_points.m_top =
          (accum_state[i_player].second.m_rank_counts.m_points.m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second.m_points.m_cutoff =
          (accum_state[i_player].second.m_rank_counts.m_points.m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));

      ret_val[i_player].second.m_rebounds.m_top =
          (accum_state[i_player].second.m_rank_counts.m_rebounds.m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second.m_rebounds.m_cutoff =
          (accum_state[i_player].second.m_rank_counts.m_rebounds.m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));

      ret_val[i_player].second.m_assists.m_top =
          (accum_state[i_player].second.m_rank_counts.m_assists.m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second.m_assists.m_cutoff =
          (accum_state[i_player].second.m_rank_counts.m_assists.m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));

      ret_val[i_player].second.m_steals.m_top =
          (accum_state[i_player].second.m_rank_counts.m_steals.m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second.m_steals.m_cutoff =
          (accum_state[i_player].second.m_rank_counts.m_steals.m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));

      ret_val[i_player].second.m_blocks.m_top =
          (accum_state[i_player].second.m_rank_counts.m_blocks.m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second.m_blocks.m_cutoff =
          (accum_state[i_player].second.m_rank_counts.m_blocks.m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));

      ret_val[i_player].second.m_threes.m_top =
          (accum_state[i_player].second.m_rank_counts.m_threes.m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second.m_threes.m_cutoff =
          (accum_state[i_player].second.m_rank_counts.m_threes.m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));

      ret_val[i_player].second.m_field_goals.m_top =
          (accum_state[i_player].second.m_rank_counts.m_field_goals.m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second.m_field_goals.m_cutoff =
          (accum_state[i_player].second.m_rank_counts.m_field_goals.m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));

      ret_val[i_player].second.m_free_throws.m_top =
          (accum_state[i_player].second.m_rank_counts.m_free_throws.m_top /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
      ret_val[i_player].second.m_free_throws.m_cutoff =
          (accum_state[i_player].second.m_rank_counts.m_free_throws.m_cutoff /
           static_cast<double>(accum_state[i_player].second.m_trial_count));
    }
    prev_accum_state = &accum_state;
    prev_total_trial_count = total_trial_count;
  }
  return ret_val;
}
