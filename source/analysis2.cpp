#include "analysis2.hpp"

#include "common.hpp"
#include "misc.hpp"
#include "scoring.hpp"

#include <array>
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

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    ret_val.m_points[i_team].m_points.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_points[i_team].m_rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_points[i_team].m_assists.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_points[i_team].m_steals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_points[i_team].m_blocks.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_points[i_team].m_threes.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_points[i_team].m_field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_points[i_team].m_free_throws.resize(
        brown_basketball::common::g_k_trial_count);

    ret_val.m_rebounds[i_team].m_points.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_rebounds[i_team].m_rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_rebounds[i_team].m_assists.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_rebounds[i_team].m_steals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_rebounds[i_team].m_blocks.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_rebounds[i_team].m_threes.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_rebounds[i_team].m_field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_rebounds[i_team].m_free_throws.resize(
        brown_basketball::common::g_k_trial_count);

    ret_val.m_assists[i_team].m_points.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_assists[i_team].m_rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_assists[i_team].m_assists.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_assists[i_team].m_steals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_assists[i_team].m_blocks.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_assists[i_team].m_threes.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_assists[i_team].m_field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_assists[i_team].m_free_throws.resize(
        brown_basketball::common::g_k_trial_count);

    ret_val.m_steals[i_team].m_points.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_steals[i_team].m_rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_steals[i_team].m_assists.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_steals[i_team].m_steals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_steals[i_team].m_blocks.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_steals[i_team].m_threes.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_steals[i_team].m_field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_steals[i_team].m_free_throws.resize(
        brown_basketball::common::g_k_trial_count);

    ret_val.m_blocks[i_team].m_points.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_blocks[i_team].m_rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_blocks[i_team].m_assists.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_blocks[i_team].m_steals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_blocks[i_team].m_blocks.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_blocks[i_team].m_threes.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_blocks[i_team].m_field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_blocks[i_team].m_free_throws.resize(
        brown_basketball::common::g_k_trial_count);

    ret_val.m_threes[i_team].m_points.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_threes[i_team].m_rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_threes[i_team].m_assists.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_threes[i_team].m_steals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_threes[i_team].m_blocks.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_threes[i_team].m_threes.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_threes[i_team].m_field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_threes[i_team].m_free_throws.resize(
        brown_basketball::common::g_k_trial_count);

    ret_val.m_field_goals[i_team].m_points.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_field_goals[i_team].m_rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_field_goals[i_team].m_assists.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_field_goals[i_team].m_steals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_field_goals[i_team].m_blocks.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_field_goals[i_team].m_threes.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_field_goals[i_team].m_field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_field_goals[i_team].m_free_throws.resize(
        brown_basketball::common::g_k_trial_count);

    ret_val.m_free_throws[i_team].m_points.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_free_throws[i_team].m_rebounds.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_free_throws[i_team].m_assists.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_free_throws[i_team].m_steals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_free_throws[i_team].m_blocks.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_free_throws[i_team].m_threes.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_free_throws[i_team].m_field_goals.resize(
        brown_basketball::common::g_k_trial_count);
    ret_val.m_free_throws[i_team].m_free_throws.resize(
        brown_basketball::common::g_k_trial_count);
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
  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    accum_state.m_points[league.second[i_team].m_ranks.m_points - 1]
        .m_points[trial_count] = league.first[i_team].m_stats.m_points;
    accum_state.m_points[league.second[i_team].m_ranks.m_points - 1]
        .m_rebounds[trial_count] = league.first[i_team].m_stats.m_rebounds;
    accum_state.m_points[league.second[i_team].m_ranks.m_points - 1]
        .m_assists[trial_count] = league.first[i_team].m_stats.m_assists;
    accum_state.m_points[league.second[i_team].m_ranks.m_points - 1]
        .m_steals[trial_count] = league.first[i_team].m_stats.m_steals;
    accum_state.m_points[league.second[i_team].m_ranks.m_points - 1]
        .m_blocks[trial_count] = league.first[i_team].m_stats.m_blocks;
    accum_state.m_points[league.second[i_team].m_ranks.m_points - 1]
        .m_threes[trial_count] = league.first[i_team].m_stats.m_threes;
    accum_state.m_points[league.second[i_team].m_ranks.m_points - 1]
        .m_field_goals[trial_count] =
        league.first[i_team].m_stats.m_field_goals;
    accum_state.m_points[league.second[i_team].m_ranks.m_points - 1]
        .m_free_throws[trial_count] =
        league.first[i_team].m_stats.m_free_throws;

    accum_state.m_rebounds[league.second[i_team].m_ranks.m_rebounds - 1]
        .m_points[trial_count] = league.first[i_team].m_stats.m_points;
    accum_state.m_rebounds[league.second[i_team].m_ranks.m_rebounds - 1]
        .m_rebounds[trial_count] = league.first[i_team].m_stats.m_rebounds;
    accum_state.m_rebounds[league.second[i_team].m_ranks.m_rebounds - 1]
        .m_assists[trial_count] = league.first[i_team].m_stats.m_assists;
    accum_state.m_rebounds[league.second[i_team].m_ranks.m_rebounds - 1]
        .m_steals[trial_count] = league.first[i_team].m_stats.m_steals;
    accum_state.m_rebounds[league.second[i_team].m_ranks.m_rebounds - 1]
        .m_blocks[trial_count] = league.first[i_team].m_stats.m_blocks;
    accum_state.m_rebounds[league.second[i_team].m_ranks.m_rebounds - 1]
        .m_threes[trial_count] = league.first[i_team].m_stats.m_threes;
    accum_state.m_rebounds[league.second[i_team].m_ranks.m_rebounds - 1]
        .m_field_goals[trial_count] =
        league.first[i_team].m_stats.m_field_goals;
    accum_state.m_rebounds[league.second[i_team].m_ranks.m_rebounds - 1]
        .m_free_throws[trial_count] =
        league.first[i_team].m_stats.m_free_throws;

    accum_state.m_assists[league.second[i_team].m_ranks.m_assists - 1]
        .m_points[trial_count] = league.first[i_team].m_stats.m_points;
    accum_state.m_assists[league.second[i_team].m_ranks.m_assists - 1]
        .m_rebounds[trial_count] = league.first[i_team].m_stats.m_rebounds;
    accum_state.m_assists[league.second[i_team].m_ranks.m_assists - 1]
        .m_assists[trial_count] = league.first[i_team].m_stats.m_assists;
    accum_state.m_assists[league.second[i_team].m_ranks.m_assists - 1]
        .m_steals[trial_count] = league.first[i_team].m_stats.m_steals;
    accum_state.m_assists[league.second[i_team].m_ranks.m_assists - 1]
        .m_blocks[trial_count] = league.first[i_team].m_stats.m_blocks;
    accum_state.m_assists[league.second[i_team].m_ranks.m_assists - 1]
        .m_threes[trial_count] = league.first[i_team].m_stats.m_threes;
    accum_state.m_assists[league.second[i_team].m_ranks.m_assists - 1]
        .m_field_goals[trial_count] =
        league.first[i_team].m_stats.m_field_goals;
    accum_state.m_assists[league.second[i_team].m_ranks.m_assists - 1]
        .m_free_throws[trial_count] =
        league.first[i_team].m_stats.m_free_throws;

    accum_state.m_steals[league.second[i_team].m_ranks.m_steals - 1]
        .m_points[trial_count] = league.first[i_team].m_stats.m_points;
    accum_state.m_steals[league.second[i_team].m_ranks.m_steals - 1]
        .m_rebounds[trial_count] = league.first[i_team].m_stats.m_rebounds;
    accum_state.m_steals[league.second[i_team].m_ranks.m_steals - 1]
        .m_assists[trial_count] = league.first[i_team].m_stats.m_assists;
    accum_state.m_steals[league.second[i_team].m_ranks.m_steals - 1]
        .m_steals[trial_count] = league.first[i_team].m_stats.m_steals;
    accum_state.m_steals[league.second[i_team].m_ranks.m_steals - 1]
        .m_blocks[trial_count] = league.first[i_team].m_stats.m_blocks;
    accum_state.m_steals[league.second[i_team].m_ranks.m_steals - 1]
        .m_threes[trial_count] = league.first[i_team].m_stats.m_threes;
    accum_state.m_steals[league.second[i_team].m_ranks.m_steals - 1]
        .m_field_goals[trial_count] =
        league.first[i_team].m_stats.m_field_goals;
    accum_state.m_steals[league.second[i_team].m_ranks.m_steals - 1]
        .m_free_throws[trial_count] =
        league.first[i_team].m_stats.m_free_throws;

    accum_state.m_blocks[league.second[i_team].m_ranks.m_blocks - 1]
        .m_points[trial_count] = league.first[i_team].m_stats.m_points;
    accum_state.m_blocks[league.second[i_team].m_ranks.m_blocks - 1]
        .m_rebounds[trial_count] = league.first[i_team].m_stats.m_rebounds;
    accum_state.m_blocks[league.second[i_team].m_ranks.m_blocks - 1]
        .m_assists[trial_count] = league.first[i_team].m_stats.m_assists;
    accum_state.m_blocks[league.second[i_team].m_ranks.m_blocks - 1]
        .m_steals[trial_count] = league.first[i_team].m_stats.m_steals;
    accum_state.m_blocks[league.second[i_team].m_ranks.m_blocks - 1]
        .m_blocks[trial_count] = league.first[i_team].m_stats.m_blocks;
    accum_state.m_blocks[league.second[i_team].m_ranks.m_blocks - 1]
        .m_threes[trial_count] = league.first[i_team].m_stats.m_threes;
    accum_state.m_blocks[league.second[i_team].m_ranks.m_blocks - 1]
        .m_field_goals[trial_count] =
        league.first[i_team].m_stats.m_field_goals;
    accum_state.m_blocks[league.second[i_team].m_ranks.m_blocks - 1]
        .m_free_throws[trial_count] =
        league.first[i_team].m_stats.m_free_throws;

    accum_state.m_threes[league.second[i_team].m_ranks.m_threes - 1]
        .m_points[trial_count] = league.first[i_team].m_stats.m_points;
    accum_state.m_threes[league.second[i_team].m_ranks.m_threes - 1]
        .m_rebounds[trial_count] = league.first[i_team].m_stats.m_rebounds;
    accum_state.m_threes[league.second[i_team].m_ranks.m_threes - 1]
        .m_assists[trial_count] = league.first[i_team].m_stats.m_assists;
    accum_state.m_threes[league.second[i_team].m_ranks.m_threes - 1]
        .m_steals[trial_count] = league.first[i_team].m_stats.m_steals;
    accum_state.m_threes[league.second[i_team].m_ranks.m_threes - 1]
        .m_blocks[trial_count] = league.first[i_team].m_stats.m_blocks;
    accum_state.m_threes[league.second[i_team].m_ranks.m_threes - 1]
        .m_threes[trial_count] = league.first[i_team].m_stats.m_threes;
    accum_state.m_threes[league.second[i_team].m_ranks.m_threes - 1]
        .m_field_goals[trial_count] =
        league.first[i_team].m_stats.m_field_goals;
    accum_state.m_threes[league.second[i_team].m_ranks.m_threes - 1]
        .m_free_throws[trial_count] =
        league.first[i_team].m_stats.m_free_throws;

    accum_state.m_field_goals[league.second[i_team].m_ranks.m_field_goals - 1]
        .m_points[trial_count] = league.first[i_team].m_stats.m_points;
    accum_state.m_field_goals[league.second[i_team].m_ranks.m_field_goals - 1]
        .m_rebounds[trial_count] = league.first[i_team].m_stats.m_rebounds;
    accum_state.m_field_goals[league.second[i_team].m_ranks.m_field_goals - 1]
        .m_assists[trial_count] = league.first[i_team].m_stats.m_assists;
    accum_state.m_field_goals[league.second[i_team].m_ranks.m_field_goals - 1]
        .m_steals[trial_count] = league.first[i_team].m_stats.m_steals;
    accum_state.m_field_goals[league.second[i_team].m_ranks.m_field_goals - 1]
        .m_blocks[trial_count] = league.first[i_team].m_stats.m_blocks;
    accum_state.m_field_goals[league.second[i_team].m_ranks.m_field_goals - 1]
        .m_threes[trial_count] = league.first[i_team].m_stats.m_threes;
    accum_state.m_field_goals[league.second[i_team].m_ranks.m_field_goals - 1]
        .m_field_goals[trial_count] =
        league.first[i_team].m_stats.m_field_goals;
    accum_state.m_field_goals[league.second[i_team].m_ranks.m_field_goals - 1]
        .m_free_throws[trial_count] =
        league.first[i_team].m_stats.m_free_throws;

    accum_state.m_free_throws[league.second[i_team].m_ranks.m_free_throws - 1]
        .m_points[trial_count] = league.first[i_team].m_stats.m_points;
    accum_state.m_free_throws[league.second[i_team].m_ranks.m_free_throws - 1]
        .m_rebounds[trial_count] = league.first[i_team].m_stats.m_rebounds;
    accum_state.m_free_throws[league.second[i_team].m_ranks.m_free_throws - 1]
        .m_assists[trial_count] = league.first[i_team].m_stats.m_assists;
    accum_state.m_free_throws[league.second[i_team].m_ranks.m_free_throws - 1]
        .m_steals[trial_count] = league.first[i_team].m_stats.m_steals;
    accum_state.m_free_throws[league.second[i_team].m_ranks.m_free_throws - 1]
        .m_blocks[trial_count] = league.first[i_team].m_stats.m_blocks;
    accum_state.m_free_throws[league.second[i_team].m_ranks.m_free_throws - 1]
        .m_threes[trial_count] = league.first[i_team].m_stats.m_threes;
    accum_state.m_free_throws[league.second[i_team].m_ranks.m_free_throws - 1]
        .m_field_goals[trial_count] =
        league.first[i_team].m_stats.m_field_goals;
    accum_state.m_free_throws[league.second[i_team].m_ranks.m_free_throws - 1]
        .m_free_throws[trial_count] =
        league.first[i_team].m_stats.m_free_throws;
  }

  ++trial_count;
}

brown_basketball::analysis2::read_t
brown_basketball::analysis2::impl::accum_state_read(
    const accum_state_t &accum_state,
    [[maybe_unused]] const unsigned long trial_count) {
  read_t ret_val{};

  for (std::size_t i_team{0}; i_team < common::g_k_league_size; ++i_team) {
    ret_val.m_points[i_team].m_points.m_mean =
        misc::mean<double>(accum_state.m_points[i_team].m_points.begin(),
                           accum_state.m_points[i_team].m_points.end());
    ret_val.m_points[i_team].m_points.m_min =
        misc::min<double>(accum_state.m_points[i_team].m_points.begin(),
                          accum_state.m_points[i_team].m_points.end());
    ret_val.m_points[i_team].m_points.m_max =
        misc::max<double>(accum_state.m_points[i_team].m_points.begin(),
                          accum_state.m_points[i_team].m_points.end());
    ret_val.m_points[i_team].m_points.m_stdev =
        misc::stdev<double>(accum_state.m_points[i_team].m_points.begin(),
                            accum_state.m_points[i_team].m_points.end(),
                            ret_val.m_points[i_team].m_points.m_mean);
    ret_val.m_points[i_team].m_rebounds.m_mean =
        misc::mean<double>(accum_state.m_points[i_team].m_rebounds.begin(),
                           accum_state.m_points[i_team].m_rebounds.end());
    ret_val.m_points[i_team].m_rebounds.m_min =
        misc::min<double>(accum_state.m_points[i_team].m_rebounds.begin(),
                          accum_state.m_points[i_team].m_rebounds.end());
    ret_val.m_points[i_team].m_rebounds.m_max =
        misc::max<double>(accum_state.m_points[i_team].m_rebounds.begin(),
                          accum_state.m_points[i_team].m_rebounds.end());
    ret_val.m_points[i_team].m_rebounds.m_stdev =
        misc::stdev<double>(accum_state.m_points[i_team].m_rebounds.begin(),
                            accum_state.m_points[i_team].m_rebounds.end(),
                            ret_val.m_points[i_team].m_rebounds.m_mean);
    ret_val.m_points[i_team].m_assists.m_mean =
        misc::mean<double>(accum_state.m_points[i_team].m_assists.begin(),
                           accum_state.m_points[i_team].m_assists.end());
    ret_val.m_points[i_team].m_assists.m_min =
        misc::min<double>(accum_state.m_points[i_team].m_assists.begin(),
                          accum_state.m_points[i_team].m_assists.end());
    ret_val.m_points[i_team].m_assists.m_max =
        misc::max<double>(accum_state.m_points[i_team].m_assists.begin(),
                          accum_state.m_points[i_team].m_assists.end());
    ret_val.m_points[i_team].m_assists.m_stdev =
        misc::stdev<double>(accum_state.m_points[i_team].m_assists.begin(),
                            accum_state.m_points[i_team].m_assists.end(),
                            ret_val.m_points[i_team].m_assists.m_mean);
    ret_val.m_points[i_team].m_steals.m_mean =
        misc::mean<double>(accum_state.m_points[i_team].m_steals.begin(),
                           accum_state.m_points[i_team].m_steals.end());
    ret_val.m_points[i_team].m_steals.m_min =
        misc::min<double>(accum_state.m_points[i_team].m_steals.begin(),
                          accum_state.m_points[i_team].m_steals.end());
    ret_val.m_points[i_team].m_steals.m_max =
        misc::max<double>(accum_state.m_points[i_team].m_steals.begin(),
                          accum_state.m_points[i_team].m_steals.end());
    ret_val.m_points[i_team].m_steals.m_stdev =
        misc::stdev<double>(accum_state.m_points[i_team].m_steals.begin(),
                            accum_state.m_points[i_team].m_steals.end(),
                            ret_val.m_points[i_team].m_steals.m_mean);
    ret_val.m_points[i_team].m_blocks.m_mean =
        misc::mean<double>(accum_state.m_points[i_team].m_blocks.begin(),
                           accum_state.m_points[i_team].m_blocks.end());
    ret_val.m_points[i_team].m_blocks.m_min =
        misc::min<double>(accum_state.m_points[i_team].m_blocks.begin(),
                          accum_state.m_points[i_team].m_blocks.end());
    ret_val.m_points[i_team].m_blocks.m_max =
        misc::max<double>(accum_state.m_points[i_team].m_blocks.begin(),
                          accum_state.m_points[i_team].m_blocks.end());
    ret_val.m_points[i_team].m_blocks.m_stdev =
        misc::stdev<double>(accum_state.m_points[i_team].m_blocks.begin(),
                            accum_state.m_points[i_team].m_blocks.end(),
                            ret_val.m_points[i_team].m_blocks.m_mean);
    ret_val.m_points[i_team].m_threes.m_mean =
        misc::mean<double>(accum_state.m_points[i_team].m_threes.begin(),
                           accum_state.m_points[i_team].m_threes.end());
    ret_val.m_points[i_team].m_threes.m_min =
        misc::min<double>(accum_state.m_points[i_team].m_threes.begin(),
                          accum_state.m_points[i_team].m_threes.end());
    ret_val.m_points[i_team].m_threes.m_max =
        misc::max<double>(accum_state.m_points[i_team].m_threes.begin(),
                          accum_state.m_points[i_team].m_threes.end());
    ret_val.m_points[i_team].m_threes.m_stdev =
        misc::stdev<double>(accum_state.m_points[i_team].m_threes.begin(),
                            accum_state.m_points[i_team].m_threes.end(),
                            ret_val.m_points[i_team].m_threes.m_mean);
    ret_val.m_points[i_team].m_field_goals.m_mean =
        misc::mean<double>(accum_state.m_points[i_team].m_field_goals.begin(),
                           accum_state.m_points[i_team].m_field_goals.end());
    ret_val.m_points[i_team].m_field_goals.m_min =
        misc::min<double>(accum_state.m_points[i_team].m_field_goals.begin(),
                          accum_state.m_points[i_team].m_field_goals.end());
    ret_val.m_points[i_team].m_field_goals.m_max =
        misc::max<double>(accum_state.m_points[i_team].m_field_goals.begin(),
                          accum_state.m_points[i_team].m_field_goals.end());
    ret_val.m_points[i_team].m_field_goals.m_stdev =
        misc::stdev<double>(accum_state.m_points[i_team].m_field_goals.begin(),
                            accum_state.m_points[i_team].m_field_goals.end(),
                            ret_val.m_points[i_team].m_field_goals.m_mean);
    ret_val.m_points[i_team].m_free_throws.m_mean =
        misc::mean<double>(accum_state.m_points[i_team].m_free_throws.begin(),
                           accum_state.m_points[i_team].m_free_throws.end());
    ret_val.m_points[i_team].m_free_throws.m_min =
        misc::min<double>(accum_state.m_points[i_team].m_free_throws.begin(),
                          accum_state.m_points[i_team].m_free_throws.end());
    ret_val.m_points[i_team].m_free_throws.m_max =
        misc::max<double>(accum_state.m_points[i_team].m_free_throws.begin(),
                          accum_state.m_points[i_team].m_free_throws.end());
    ret_val.m_points[i_team].m_free_throws.m_stdev =
        misc::stdev<double>(accum_state.m_points[i_team].m_free_throws.begin(),
                            accum_state.m_points[i_team].m_free_throws.end(),
                            ret_val.m_points[i_team].m_free_throws.m_mean);

    ret_val.m_rebounds[i_team].m_points.m_mean =
        misc::mean<double>(accum_state.m_rebounds[i_team].m_points.begin(),
                           accum_state.m_rebounds[i_team].m_points.end());
    ret_val.m_rebounds[i_team].m_points.m_min =
        misc::min<double>(accum_state.m_rebounds[i_team].m_points.begin(),
                          accum_state.m_rebounds[i_team].m_points.end());
    ret_val.m_rebounds[i_team].m_points.m_max =
        misc::max<double>(accum_state.m_rebounds[i_team].m_points.begin(),
                          accum_state.m_rebounds[i_team].m_points.end());
    ret_val.m_rebounds[i_team].m_points.m_stdev =
        misc::stdev<double>(accum_state.m_rebounds[i_team].m_points.begin(),
                            accum_state.m_rebounds[i_team].m_points.end(),
                            ret_val.m_rebounds[i_team].m_points.m_mean);
    ret_val.m_rebounds[i_team].m_rebounds.m_mean =
        misc::mean<double>(accum_state.m_rebounds[i_team].m_rebounds.begin(),
                           accum_state.m_rebounds[i_team].m_rebounds.end());
    ret_val.m_rebounds[i_team].m_rebounds.m_min =
        misc::min<double>(accum_state.m_rebounds[i_team].m_rebounds.begin(),
                          accum_state.m_rebounds[i_team].m_rebounds.end());
    ret_val.m_rebounds[i_team].m_rebounds.m_max =
        misc::max<double>(accum_state.m_rebounds[i_team].m_rebounds.begin(),
                          accum_state.m_rebounds[i_team].m_rebounds.end());
    ret_val.m_rebounds[i_team].m_rebounds.m_stdev =
        misc::stdev<double>(accum_state.m_rebounds[i_team].m_rebounds.begin(),
                            accum_state.m_rebounds[i_team].m_rebounds.end(),
                            ret_val.m_rebounds[i_team].m_rebounds.m_mean);
    ret_val.m_rebounds[i_team].m_assists.m_mean =
        misc::mean<double>(accum_state.m_rebounds[i_team].m_assists.begin(),
                           accum_state.m_rebounds[i_team].m_assists.end());
    ret_val.m_rebounds[i_team].m_assists.m_min =
        misc::min<double>(accum_state.m_rebounds[i_team].m_assists.begin(),
                          accum_state.m_rebounds[i_team].m_assists.end());
    ret_val.m_rebounds[i_team].m_assists.m_max =
        misc::max<double>(accum_state.m_rebounds[i_team].m_assists.begin(),
                          accum_state.m_rebounds[i_team].m_assists.end());
    ret_val.m_rebounds[i_team].m_assists.m_stdev =
        misc::stdev<double>(accum_state.m_rebounds[i_team].m_assists.begin(),
                            accum_state.m_rebounds[i_team].m_assists.end(),
                            ret_val.m_rebounds[i_team].m_assists.m_mean);
    ret_val.m_rebounds[i_team].m_steals.m_mean =
        misc::mean<double>(accum_state.m_rebounds[i_team].m_steals.begin(),
                           accum_state.m_rebounds[i_team].m_steals.end());
    ret_val.m_rebounds[i_team].m_steals.m_min =
        misc::min<double>(accum_state.m_rebounds[i_team].m_steals.begin(),
                          accum_state.m_rebounds[i_team].m_steals.end());
    ret_val.m_rebounds[i_team].m_steals.m_max =
        misc::max<double>(accum_state.m_rebounds[i_team].m_steals.begin(),
                          accum_state.m_rebounds[i_team].m_steals.end());
    ret_val.m_rebounds[i_team].m_steals.m_stdev =
        misc::stdev<double>(accum_state.m_rebounds[i_team].m_steals.begin(),
                            accum_state.m_rebounds[i_team].m_steals.end(),
                            ret_val.m_rebounds[i_team].m_steals.m_mean);
    ret_val.m_rebounds[i_team].m_blocks.m_mean =
        misc::mean<double>(accum_state.m_rebounds[i_team].m_blocks.begin(),
                           accum_state.m_rebounds[i_team].m_blocks.end());
    ret_val.m_rebounds[i_team].m_blocks.m_min =
        misc::min<double>(accum_state.m_rebounds[i_team].m_blocks.begin(),
                          accum_state.m_rebounds[i_team].m_blocks.end());
    ret_val.m_rebounds[i_team].m_blocks.m_max =
        misc::max<double>(accum_state.m_rebounds[i_team].m_blocks.begin(),
                          accum_state.m_rebounds[i_team].m_blocks.end());
    ret_val.m_rebounds[i_team].m_blocks.m_stdev =
        misc::stdev<double>(accum_state.m_rebounds[i_team].m_blocks.begin(),
                            accum_state.m_rebounds[i_team].m_blocks.end(),
                            ret_val.m_rebounds[i_team].m_blocks.m_mean);
    ret_val.m_rebounds[i_team].m_threes.m_mean =
        misc::mean<double>(accum_state.m_rebounds[i_team].m_threes.begin(),
                           accum_state.m_rebounds[i_team].m_threes.end());
    ret_val.m_rebounds[i_team].m_threes.m_min =
        misc::min<double>(accum_state.m_rebounds[i_team].m_threes.begin(),
                          accum_state.m_rebounds[i_team].m_threes.end());
    ret_val.m_rebounds[i_team].m_threes.m_max =
        misc::max<double>(accum_state.m_rebounds[i_team].m_threes.begin(),
                          accum_state.m_rebounds[i_team].m_threes.end());
    ret_val.m_rebounds[i_team].m_threes.m_stdev =
        misc::stdev<double>(accum_state.m_rebounds[i_team].m_threes.begin(),
                            accum_state.m_rebounds[i_team].m_threes.end(),
                            ret_val.m_rebounds[i_team].m_threes.m_mean);
    ret_val.m_rebounds[i_team].m_field_goals.m_mean =
        misc::mean<double>(accum_state.m_rebounds[i_team].m_field_goals.begin(),
                           accum_state.m_rebounds[i_team].m_field_goals.end());
    ret_val.m_rebounds[i_team].m_field_goals.m_min =
        misc::min<double>(accum_state.m_rebounds[i_team].m_field_goals.begin(),
                          accum_state.m_rebounds[i_team].m_field_goals.end());
    ret_val.m_rebounds[i_team].m_field_goals.m_max =
        misc::max<double>(accum_state.m_rebounds[i_team].m_field_goals.begin(),
                          accum_state.m_rebounds[i_team].m_field_goals.end());
    ret_val.m_rebounds[i_team].m_field_goals.m_stdev = misc::stdev<double>(
        accum_state.m_rebounds[i_team].m_field_goals.begin(),
        accum_state.m_rebounds[i_team].m_field_goals.end(),
        ret_val.m_rebounds[i_team].m_field_goals.m_mean);
    ret_val.m_rebounds[i_team].m_free_throws.m_mean =
        misc::mean<double>(accum_state.m_rebounds[i_team].m_free_throws.begin(),
                           accum_state.m_rebounds[i_team].m_free_throws.end());
    ret_val.m_rebounds[i_team].m_free_throws.m_min =
        misc::min<double>(accum_state.m_rebounds[i_team].m_free_throws.begin(),
                          accum_state.m_rebounds[i_team].m_free_throws.end());
    ret_val.m_rebounds[i_team].m_free_throws.m_max =
        misc::max<double>(accum_state.m_rebounds[i_team].m_free_throws.begin(),
                          accum_state.m_rebounds[i_team].m_free_throws.end());
    ret_val.m_rebounds[i_team].m_free_throws.m_stdev = misc::stdev<double>(
        accum_state.m_rebounds[i_team].m_free_throws.begin(),
        accum_state.m_rebounds[i_team].m_free_throws.end(),
        ret_val.m_rebounds[i_team].m_free_throws.m_mean);

    ret_val.m_assists[i_team].m_points.m_mean =
        misc::mean<double>(accum_state.m_assists[i_team].m_points.begin(),
                           accum_state.m_assists[i_team].m_points.end());
    ret_val.m_assists[i_team].m_points.m_min =
        misc::min<double>(accum_state.m_assists[i_team].m_points.begin(),
                          accum_state.m_assists[i_team].m_points.end());
    ret_val.m_assists[i_team].m_points.m_max =
        misc::max<double>(accum_state.m_assists[i_team].m_points.begin(),
                          accum_state.m_assists[i_team].m_points.end());
    ret_val.m_assists[i_team].m_points.m_stdev =
        misc::stdev<double>(accum_state.m_assists[i_team].m_points.begin(),
                            accum_state.m_assists[i_team].m_points.end(),
                            ret_val.m_assists[i_team].m_points.m_mean);
    ret_val.m_assists[i_team].m_rebounds.m_mean =
        misc::mean<double>(accum_state.m_assists[i_team].m_rebounds.begin(),
                           accum_state.m_assists[i_team].m_rebounds.end());
    ret_val.m_assists[i_team].m_rebounds.m_min =
        misc::min<double>(accum_state.m_assists[i_team].m_rebounds.begin(),
                          accum_state.m_assists[i_team].m_rebounds.end());
    ret_val.m_assists[i_team].m_rebounds.m_max =
        misc::max<double>(accum_state.m_assists[i_team].m_rebounds.begin(),
                          accum_state.m_assists[i_team].m_rebounds.end());
    ret_val.m_assists[i_team].m_rebounds.m_stdev =
        misc::stdev<double>(accum_state.m_assists[i_team].m_rebounds.begin(),
                            accum_state.m_assists[i_team].m_rebounds.end(),
                            ret_val.m_assists[i_team].m_rebounds.m_mean);
    ret_val.m_assists[i_team].m_assists.m_mean =
        misc::mean<double>(accum_state.m_assists[i_team].m_assists.begin(),
                           accum_state.m_assists[i_team].m_assists.end());
    ret_val.m_assists[i_team].m_assists.m_min =
        misc::min<double>(accum_state.m_assists[i_team].m_assists.begin(),
                          accum_state.m_assists[i_team].m_assists.end());
    ret_val.m_assists[i_team].m_assists.m_max =
        misc::max<double>(accum_state.m_assists[i_team].m_assists.begin(),
                          accum_state.m_assists[i_team].m_assists.end());
    ret_val.m_assists[i_team].m_assists.m_stdev =
        misc::stdev<double>(accum_state.m_assists[i_team].m_assists.begin(),
                            accum_state.m_assists[i_team].m_assists.end(),
                            ret_val.m_assists[i_team].m_assists.m_mean);
    ret_val.m_assists[i_team].m_steals.m_mean =
        misc::mean<double>(accum_state.m_assists[i_team].m_steals.begin(),
                           accum_state.m_assists[i_team].m_steals.end());
    ret_val.m_assists[i_team].m_steals.m_min =
        misc::min<double>(accum_state.m_assists[i_team].m_steals.begin(),
                          accum_state.m_assists[i_team].m_steals.end());
    ret_val.m_assists[i_team].m_steals.m_max =
        misc::max<double>(accum_state.m_assists[i_team].m_steals.begin(),
                          accum_state.m_assists[i_team].m_steals.end());
    ret_val.m_assists[i_team].m_steals.m_stdev =
        misc::stdev<double>(accum_state.m_assists[i_team].m_steals.begin(),
                            accum_state.m_assists[i_team].m_steals.end(),
                            ret_val.m_assists[i_team].m_steals.m_mean);
    ret_val.m_assists[i_team].m_blocks.m_mean =
        misc::mean<double>(accum_state.m_assists[i_team].m_blocks.begin(),
                           accum_state.m_assists[i_team].m_blocks.end());
    ret_val.m_assists[i_team].m_blocks.m_min =
        misc::min<double>(accum_state.m_assists[i_team].m_blocks.begin(),
                          accum_state.m_assists[i_team].m_blocks.end());
    ret_val.m_assists[i_team].m_blocks.m_max =
        misc::max<double>(accum_state.m_assists[i_team].m_blocks.begin(),
                          accum_state.m_assists[i_team].m_blocks.end());
    ret_val.m_assists[i_team].m_blocks.m_stdev =
        misc::stdev<double>(accum_state.m_assists[i_team].m_blocks.begin(),
                            accum_state.m_assists[i_team].m_blocks.end(),
                            ret_val.m_assists[i_team].m_blocks.m_mean);
    ret_val.m_assists[i_team].m_threes.m_mean =
        misc::mean<double>(accum_state.m_assists[i_team].m_threes.begin(),
                           accum_state.m_assists[i_team].m_threes.end());
    ret_val.m_assists[i_team].m_threes.m_min =
        misc::min<double>(accum_state.m_assists[i_team].m_threes.begin(),
                          accum_state.m_assists[i_team].m_threes.end());
    ret_val.m_assists[i_team].m_threes.m_max =
        misc::max<double>(accum_state.m_assists[i_team].m_threes.begin(),
                          accum_state.m_assists[i_team].m_threes.end());
    ret_val.m_assists[i_team].m_threes.m_stdev =
        misc::stdev<double>(accum_state.m_assists[i_team].m_threes.begin(),
                            accum_state.m_assists[i_team].m_threes.end(),
                            ret_val.m_assists[i_team].m_threes.m_mean);
    ret_val.m_assists[i_team].m_field_goals.m_mean =
        misc::mean<double>(accum_state.m_assists[i_team].m_field_goals.begin(),
                           accum_state.m_assists[i_team].m_field_goals.end());
    ret_val.m_assists[i_team].m_field_goals.m_min =
        misc::min<double>(accum_state.m_assists[i_team].m_field_goals.begin(),
                          accum_state.m_assists[i_team].m_field_goals.end());
    ret_val.m_assists[i_team].m_field_goals.m_max =
        misc::max<double>(accum_state.m_assists[i_team].m_field_goals.begin(),
                          accum_state.m_assists[i_team].m_field_goals.end());
    ret_val.m_assists[i_team].m_field_goals.m_stdev =
        misc::stdev<double>(accum_state.m_assists[i_team].m_field_goals.begin(),
                            accum_state.m_assists[i_team].m_field_goals.end(),
                            ret_val.m_assists[i_team].m_field_goals.m_mean);
    ret_val.m_assists[i_team].m_free_throws.m_mean =
        misc::mean<double>(accum_state.m_assists[i_team].m_free_throws.begin(),
                           accum_state.m_assists[i_team].m_free_throws.end());
    ret_val.m_assists[i_team].m_free_throws.m_min =
        misc::min<double>(accum_state.m_assists[i_team].m_free_throws.begin(),
                          accum_state.m_assists[i_team].m_free_throws.end());
    ret_val.m_assists[i_team].m_free_throws.m_max =
        misc::max<double>(accum_state.m_assists[i_team].m_free_throws.begin(),
                          accum_state.m_assists[i_team].m_free_throws.end());
    ret_val.m_assists[i_team].m_free_throws.m_stdev =
        misc::stdev<double>(accum_state.m_assists[i_team].m_free_throws.begin(),
                            accum_state.m_assists[i_team].m_free_throws.end(),
                            ret_val.m_assists[i_team].m_free_throws.m_mean);

    ret_val.m_steals[i_team].m_points.m_mean =
        misc::mean<double>(accum_state.m_steals[i_team].m_points.begin(),
                           accum_state.m_steals[i_team].m_points.end());
    ret_val.m_steals[i_team].m_points.m_min =
        misc::min<double>(accum_state.m_steals[i_team].m_points.begin(),
                          accum_state.m_steals[i_team].m_points.end());
    ret_val.m_steals[i_team].m_points.m_max =
        misc::max<double>(accum_state.m_steals[i_team].m_points.begin(),
                          accum_state.m_steals[i_team].m_points.end());
    ret_val.m_steals[i_team].m_points.m_stdev =
        misc::stdev<double>(accum_state.m_steals[i_team].m_points.begin(),
                            accum_state.m_steals[i_team].m_points.end(),
                            ret_val.m_steals[i_team].m_points.m_mean);
    ret_val.m_steals[i_team].m_rebounds.m_mean =
        misc::mean<double>(accum_state.m_steals[i_team].m_rebounds.begin(),
                           accum_state.m_steals[i_team].m_rebounds.end());
    ret_val.m_steals[i_team].m_rebounds.m_min =
        misc::min<double>(accum_state.m_steals[i_team].m_rebounds.begin(),
                          accum_state.m_steals[i_team].m_rebounds.end());
    ret_val.m_steals[i_team].m_rebounds.m_max =
        misc::max<double>(accum_state.m_steals[i_team].m_rebounds.begin(),
                          accum_state.m_steals[i_team].m_rebounds.end());
    ret_val.m_steals[i_team].m_rebounds.m_stdev =
        misc::stdev<double>(accum_state.m_steals[i_team].m_rebounds.begin(),
                            accum_state.m_steals[i_team].m_rebounds.end(),
                            ret_val.m_steals[i_team].m_rebounds.m_mean);
    ret_val.m_steals[i_team].m_assists.m_mean =
        misc::mean<double>(accum_state.m_steals[i_team].m_assists.begin(),
                           accum_state.m_steals[i_team].m_assists.end());
    ret_val.m_steals[i_team].m_assists.m_min =
        misc::min<double>(accum_state.m_steals[i_team].m_assists.begin(),
                          accum_state.m_steals[i_team].m_assists.end());
    ret_val.m_steals[i_team].m_assists.m_max =
        misc::max<double>(accum_state.m_steals[i_team].m_assists.begin(),
                          accum_state.m_steals[i_team].m_assists.end());
    ret_val.m_steals[i_team].m_assists.m_stdev =
        misc::stdev<double>(accum_state.m_steals[i_team].m_assists.begin(),
                            accum_state.m_steals[i_team].m_assists.end(),
                            ret_val.m_steals[i_team].m_assists.m_mean);
    ret_val.m_steals[i_team].m_steals.m_mean =
        misc::mean<double>(accum_state.m_steals[i_team].m_steals.begin(),
                           accum_state.m_steals[i_team].m_steals.end());
    ret_val.m_steals[i_team].m_steals.m_min =
        misc::min<double>(accum_state.m_steals[i_team].m_steals.begin(),
                          accum_state.m_steals[i_team].m_steals.end());
    ret_val.m_steals[i_team].m_steals.m_max =
        misc::max<double>(accum_state.m_steals[i_team].m_steals.begin(),
                          accum_state.m_steals[i_team].m_steals.end());
    ret_val.m_steals[i_team].m_steals.m_stdev =
        misc::stdev<double>(accum_state.m_steals[i_team].m_steals.begin(),
                            accum_state.m_steals[i_team].m_steals.end(),
                            ret_val.m_steals[i_team].m_steals.m_mean);
    ret_val.m_steals[i_team].m_blocks.m_mean =
        misc::mean<double>(accum_state.m_steals[i_team].m_blocks.begin(),
                           accum_state.m_steals[i_team].m_blocks.end());
    ret_val.m_steals[i_team].m_blocks.m_min =
        misc::min<double>(accum_state.m_steals[i_team].m_blocks.begin(),
                          accum_state.m_steals[i_team].m_blocks.end());
    ret_val.m_steals[i_team].m_blocks.m_max =
        misc::max<double>(accum_state.m_steals[i_team].m_blocks.begin(),
                          accum_state.m_steals[i_team].m_blocks.end());
    ret_val.m_steals[i_team].m_blocks.m_stdev =
        misc::stdev<double>(accum_state.m_steals[i_team].m_blocks.begin(),
                            accum_state.m_steals[i_team].m_blocks.end(),
                            ret_val.m_steals[i_team].m_blocks.m_mean);
    ret_val.m_steals[i_team].m_threes.m_mean =
        misc::mean<double>(accum_state.m_steals[i_team].m_threes.begin(),
                           accum_state.m_steals[i_team].m_threes.end());
    ret_val.m_steals[i_team].m_threes.m_min =
        misc::min<double>(accum_state.m_steals[i_team].m_threes.begin(),
                          accum_state.m_steals[i_team].m_threes.end());
    ret_val.m_steals[i_team].m_threes.m_max =
        misc::max<double>(accum_state.m_steals[i_team].m_threes.begin(),
                          accum_state.m_steals[i_team].m_threes.end());
    ret_val.m_steals[i_team].m_threes.m_stdev =
        misc::stdev<double>(accum_state.m_steals[i_team].m_threes.begin(),
                            accum_state.m_steals[i_team].m_threes.end(),
                            ret_val.m_steals[i_team].m_threes.m_mean);
    ret_val.m_steals[i_team].m_field_goals.m_mean =
        misc::mean<double>(accum_state.m_steals[i_team].m_field_goals.begin(),
                           accum_state.m_steals[i_team].m_field_goals.end());
    ret_val.m_steals[i_team].m_field_goals.m_min =
        misc::min<double>(accum_state.m_steals[i_team].m_field_goals.begin(),
                          accum_state.m_steals[i_team].m_field_goals.end());
    ret_val.m_steals[i_team].m_field_goals.m_max =
        misc::max<double>(accum_state.m_steals[i_team].m_field_goals.begin(),
                          accum_state.m_steals[i_team].m_field_goals.end());
    ret_val.m_steals[i_team].m_field_goals.m_stdev =
        misc::stdev<double>(accum_state.m_steals[i_team].m_field_goals.begin(),
                            accum_state.m_steals[i_team].m_field_goals.end(),
                            ret_val.m_steals[i_team].m_field_goals.m_mean);
    ret_val.m_steals[i_team].m_free_throws.m_mean =
        misc::mean<double>(accum_state.m_steals[i_team].m_free_throws.begin(),
                           accum_state.m_steals[i_team].m_free_throws.end());
    ret_val.m_steals[i_team].m_free_throws.m_min =
        misc::min<double>(accum_state.m_steals[i_team].m_free_throws.begin(),
                          accum_state.m_steals[i_team].m_free_throws.end());
    ret_val.m_steals[i_team].m_free_throws.m_max =
        misc::max<double>(accum_state.m_steals[i_team].m_free_throws.begin(),
                          accum_state.m_steals[i_team].m_free_throws.end());
    ret_val.m_steals[i_team].m_free_throws.m_stdev =
        misc::stdev<double>(accum_state.m_steals[i_team].m_free_throws.begin(),
                            accum_state.m_steals[i_team].m_free_throws.end(),
                            ret_val.m_steals[i_team].m_free_throws.m_mean);

    ret_val.m_blocks[i_team].m_points.m_mean =
        misc::mean<double>(accum_state.m_blocks[i_team].m_points.begin(),
                           accum_state.m_blocks[i_team].m_points.end());
    ret_val.m_blocks[i_team].m_points.m_min =
        misc::min<double>(accum_state.m_blocks[i_team].m_points.begin(),
                          accum_state.m_blocks[i_team].m_points.end());
    ret_val.m_blocks[i_team].m_points.m_max =
        misc::max<double>(accum_state.m_blocks[i_team].m_points.begin(),
                          accum_state.m_blocks[i_team].m_points.end());
    ret_val.m_blocks[i_team].m_points.m_stdev =
        misc::stdev<double>(accum_state.m_blocks[i_team].m_points.begin(),
                            accum_state.m_blocks[i_team].m_points.end(),
                            ret_val.m_blocks[i_team].m_points.m_mean);
    ret_val.m_blocks[i_team].m_rebounds.m_mean =
        misc::mean<double>(accum_state.m_blocks[i_team].m_rebounds.begin(),
                           accum_state.m_blocks[i_team].m_rebounds.end());
    ret_val.m_blocks[i_team].m_rebounds.m_min =
        misc::min<double>(accum_state.m_blocks[i_team].m_rebounds.begin(),
                          accum_state.m_blocks[i_team].m_rebounds.end());
    ret_val.m_blocks[i_team].m_rebounds.m_max =
        misc::max<double>(accum_state.m_blocks[i_team].m_rebounds.begin(),
                          accum_state.m_blocks[i_team].m_rebounds.end());
    ret_val.m_blocks[i_team].m_rebounds.m_stdev =
        misc::stdev<double>(accum_state.m_blocks[i_team].m_rebounds.begin(),
                            accum_state.m_blocks[i_team].m_rebounds.end(),
                            ret_val.m_blocks[i_team].m_rebounds.m_mean);
    ret_val.m_blocks[i_team].m_assists.m_mean =
        misc::mean<double>(accum_state.m_blocks[i_team].m_assists.begin(),
                           accum_state.m_blocks[i_team].m_assists.end());
    ret_val.m_blocks[i_team].m_assists.m_min =
        misc::min<double>(accum_state.m_blocks[i_team].m_assists.begin(),
                          accum_state.m_blocks[i_team].m_assists.end());
    ret_val.m_blocks[i_team].m_assists.m_max =
        misc::max<double>(accum_state.m_blocks[i_team].m_assists.begin(),
                          accum_state.m_blocks[i_team].m_assists.end());
    ret_val.m_blocks[i_team].m_assists.m_stdev =
        misc::stdev<double>(accum_state.m_blocks[i_team].m_assists.begin(),
                            accum_state.m_blocks[i_team].m_assists.end(),
                            ret_val.m_blocks[i_team].m_assists.m_mean);
    ret_val.m_blocks[i_team].m_steals.m_mean =
        misc::mean<double>(accum_state.m_blocks[i_team].m_steals.begin(),
                           accum_state.m_blocks[i_team].m_steals.end());
    ret_val.m_blocks[i_team].m_steals.m_min =
        misc::min<double>(accum_state.m_blocks[i_team].m_steals.begin(),
                          accum_state.m_blocks[i_team].m_steals.end());
    ret_val.m_blocks[i_team].m_steals.m_max =
        misc::max<double>(accum_state.m_blocks[i_team].m_steals.begin(),
                          accum_state.m_blocks[i_team].m_steals.end());
    ret_val.m_blocks[i_team].m_steals.m_stdev =
        misc::stdev<double>(accum_state.m_blocks[i_team].m_steals.begin(),
                            accum_state.m_blocks[i_team].m_steals.end(),
                            ret_val.m_blocks[i_team].m_steals.m_mean);
    ret_val.m_blocks[i_team].m_blocks.m_mean =
        misc::mean<double>(accum_state.m_blocks[i_team].m_blocks.begin(),
                           accum_state.m_blocks[i_team].m_blocks.end());
    ret_val.m_blocks[i_team].m_blocks.m_min =
        misc::min<double>(accum_state.m_blocks[i_team].m_blocks.begin(),
                          accum_state.m_blocks[i_team].m_blocks.end());
    ret_val.m_blocks[i_team].m_blocks.m_max =
        misc::max<double>(accum_state.m_blocks[i_team].m_blocks.begin(),
                          accum_state.m_blocks[i_team].m_blocks.end());
    ret_val.m_blocks[i_team].m_blocks.m_stdev =
        misc::stdev<double>(accum_state.m_blocks[i_team].m_blocks.begin(),
                            accum_state.m_blocks[i_team].m_blocks.end(),
                            ret_val.m_blocks[i_team].m_blocks.m_mean);
    ret_val.m_blocks[i_team].m_threes.m_mean =
        misc::mean<double>(accum_state.m_blocks[i_team].m_threes.begin(),
                           accum_state.m_blocks[i_team].m_threes.end());
    ret_val.m_blocks[i_team].m_threes.m_min =
        misc::min<double>(accum_state.m_blocks[i_team].m_threes.begin(),
                          accum_state.m_blocks[i_team].m_threes.end());
    ret_val.m_blocks[i_team].m_threes.m_max =
        misc::max<double>(accum_state.m_blocks[i_team].m_threes.begin(),
                          accum_state.m_blocks[i_team].m_threes.end());
    ret_val.m_blocks[i_team].m_threes.m_stdev =
        misc::stdev<double>(accum_state.m_blocks[i_team].m_threes.begin(),
                            accum_state.m_blocks[i_team].m_threes.end(),
                            ret_val.m_blocks[i_team].m_threes.m_mean);
    ret_val.m_blocks[i_team].m_field_goals.m_mean =
        misc::mean<double>(accum_state.m_blocks[i_team].m_field_goals.begin(),
                           accum_state.m_blocks[i_team].m_field_goals.end());
    ret_val.m_blocks[i_team].m_field_goals.m_min =
        misc::min<double>(accum_state.m_blocks[i_team].m_field_goals.begin(),
                          accum_state.m_blocks[i_team].m_field_goals.end());
    ret_val.m_blocks[i_team].m_field_goals.m_max =
        misc::max<double>(accum_state.m_blocks[i_team].m_field_goals.begin(),
                          accum_state.m_blocks[i_team].m_field_goals.end());
    ret_val.m_blocks[i_team].m_field_goals.m_stdev =
        misc::stdev<double>(accum_state.m_blocks[i_team].m_field_goals.begin(),
                            accum_state.m_blocks[i_team].m_field_goals.end(),
                            ret_val.m_blocks[i_team].m_field_goals.m_mean);
    ret_val.m_blocks[i_team].m_free_throws.m_mean =
        misc::mean<double>(accum_state.m_blocks[i_team].m_free_throws.begin(),
                           accum_state.m_blocks[i_team].m_free_throws.end());
    ret_val.m_blocks[i_team].m_free_throws.m_min =
        misc::min<double>(accum_state.m_blocks[i_team].m_free_throws.begin(),
                          accum_state.m_blocks[i_team].m_free_throws.end());
    ret_val.m_blocks[i_team].m_free_throws.m_max =
        misc::max<double>(accum_state.m_blocks[i_team].m_free_throws.begin(),
                          accum_state.m_blocks[i_team].m_free_throws.end());
    ret_val.m_blocks[i_team].m_free_throws.m_stdev =
        misc::stdev<double>(accum_state.m_blocks[i_team].m_free_throws.begin(),
                            accum_state.m_blocks[i_team].m_free_throws.end(),
                            ret_val.m_blocks[i_team].m_free_throws.m_mean);

    ret_val.m_threes[i_team].m_points.m_mean =
        misc::mean<double>(accum_state.m_threes[i_team].m_points.begin(),
                           accum_state.m_threes[i_team].m_points.end());
    ret_val.m_threes[i_team].m_points.m_min =
        misc::min<double>(accum_state.m_threes[i_team].m_points.begin(),
                          accum_state.m_threes[i_team].m_points.end());
    ret_val.m_threes[i_team].m_points.m_max =
        misc::max<double>(accum_state.m_threes[i_team].m_points.begin(),
                          accum_state.m_threes[i_team].m_points.end());
    ret_val.m_threes[i_team].m_points.m_stdev =
        misc::stdev<double>(accum_state.m_threes[i_team].m_points.begin(),
                            accum_state.m_threes[i_team].m_points.end(),
                            ret_val.m_threes[i_team].m_points.m_mean);
    ret_val.m_threes[i_team].m_rebounds.m_mean =
        misc::mean<double>(accum_state.m_threes[i_team].m_rebounds.begin(),
                           accum_state.m_threes[i_team].m_rebounds.end());
    ret_val.m_threes[i_team].m_rebounds.m_min =
        misc::min<double>(accum_state.m_threes[i_team].m_rebounds.begin(),
                          accum_state.m_threes[i_team].m_rebounds.end());
    ret_val.m_threes[i_team].m_rebounds.m_max =
        misc::max<double>(accum_state.m_threes[i_team].m_rebounds.begin(),
                          accum_state.m_threes[i_team].m_rebounds.end());
    ret_val.m_threes[i_team].m_rebounds.m_stdev =
        misc::stdev<double>(accum_state.m_threes[i_team].m_rebounds.begin(),
                            accum_state.m_threes[i_team].m_rebounds.end(),
                            ret_val.m_threes[i_team].m_rebounds.m_mean);
    ret_val.m_threes[i_team].m_assists.m_mean =
        misc::mean<double>(accum_state.m_threes[i_team].m_assists.begin(),
                           accum_state.m_threes[i_team].m_assists.end());
    ret_val.m_threes[i_team].m_assists.m_min =
        misc::min<double>(accum_state.m_threes[i_team].m_assists.begin(),
                          accum_state.m_threes[i_team].m_assists.end());
    ret_val.m_threes[i_team].m_assists.m_max =
        misc::max<double>(accum_state.m_threes[i_team].m_assists.begin(),
                          accum_state.m_threes[i_team].m_assists.end());
    ret_val.m_threes[i_team].m_assists.m_stdev =
        misc::stdev<double>(accum_state.m_threes[i_team].m_assists.begin(),
                            accum_state.m_threes[i_team].m_assists.end(),
                            ret_val.m_threes[i_team].m_assists.m_mean);
    ret_val.m_threes[i_team].m_steals.m_mean =
        misc::mean<double>(accum_state.m_threes[i_team].m_steals.begin(),
                           accum_state.m_threes[i_team].m_steals.end());
    ret_val.m_threes[i_team].m_steals.m_min =
        misc::min<double>(accum_state.m_threes[i_team].m_steals.begin(),
                          accum_state.m_threes[i_team].m_steals.end());
    ret_val.m_threes[i_team].m_steals.m_max =
        misc::max<double>(accum_state.m_threes[i_team].m_steals.begin(),
                          accum_state.m_threes[i_team].m_steals.end());
    ret_val.m_threes[i_team].m_steals.m_stdev =
        misc::stdev<double>(accum_state.m_threes[i_team].m_steals.begin(),
                            accum_state.m_threes[i_team].m_steals.end(),
                            ret_val.m_threes[i_team].m_steals.m_mean);
    ret_val.m_threes[i_team].m_blocks.m_mean =
        misc::mean<double>(accum_state.m_threes[i_team].m_blocks.begin(),
                           accum_state.m_threes[i_team].m_blocks.end());
    ret_val.m_threes[i_team].m_blocks.m_min =
        misc::min<double>(accum_state.m_threes[i_team].m_blocks.begin(),
                          accum_state.m_threes[i_team].m_blocks.end());
    ret_val.m_threes[i_team].m_blocks.m_max =
        misc::max<double>(accum_state.m_threes[i_team].m_blocks.begin(),
                          accum_state.m_threes[i_team].m_blocks.end());
    ret_val.m_threes[i_team].m_blocks.m_stdev =
        misc::stdev<double>(accum_state.m_threes[i_team].m_blocks.begin(),
                            accum_state.m_threes[i_team].m_blocks.end(),
                            ret_val.m_threes[i_team].m_blocks.m_mean);
    ret_val.m_threes[i_team].m_threes.m_mean =
        misc::mean<double>(accum_state.m_threes[i_team].m_threes.begin(),
                           accum_state.m_threes[i_team].m_threes.end());
    ret_val.m_threes[i_team].m_threes.m_min =
        misc::min<double>(accum_state.m_threes[i_team].m_threes.begin(),
                          accum_state.m_threes[i_team].m_threes.end());
    ret_val.m_threes[i_team].m_threes.m_max =
        misc::max<double>(accum_state.m_threes[i_team].m_threes.begin(),
                          accum_state.m_threes[i_team].m_threes.end());
    ret_val.m_threes[i_team].m_threes.m_stdev =
        misc::stdev<double>(accum_state.m_threes[i_team].m_threes.begin(),
                            accum_state.m_threes[i_team].m_threes.end(),
                            ret_val.m_threes[i_team].m_threes.m_mean);
    ret_val.m_threes[i_team].m_field_goals.m_mean =
        misc::mean<double>(accum_state.m_threes[i_team].m_field_goals.begin(),
                           accum_state.m_threes[i_team].m_field_goals.end());
    ret_val.m_threes[i_team].m_field_goals.m_min =
        misc::min<double>(accum_state.m_threes[i_team].m_field_goals.begin(),
                          accum_state.m_threes[i_team].m_field_goals.end());
    ret_val.m_threes[i_team].m_field_goals.m_max =
        misc::max<double>(accum_state.m_threes[i_team].m_field_goals.begin(),
                          accum_state.m_threes[i_team].m_field_goals.end());
    ret_val.m_threes[i_team].m_field_goals.m_stdev =
        misc::stdev<double>(accum_state.m_threes[i_team].m_field_goals.begin(),
                            accum_state.m_threes[i_team].m_field_goals.end(),
                            ret_val.m_threes[i_team].m_field_goals.m_mean);
    ret_val.m_threes[i_team].m_free_throws.m_mean =
        misc::mean<double>(accum_state.m_threes[i_team].m_free_throws.begin(),
                           accum_state.m_threes[i_team].m_free_throws.end());
    ret_val.m_threes[i_team].m_free_throws.m_min =
        misc::min<double>(accum_state.m_threes[i_team].m_free_throws.begin(),
                          accum_state.m_threes[i_team].m_free_throws.end());
    ret_val.m_threes[i_team].m_free_throws.m_max =
        misc::max<double>(accum_state.m_threes[i_team].m_free_throws.begin(),
                          accum_state.m_threes[i_team].m_free_throws.end());
    ret_val.m_threes[i_team].m_free_throws.m_stdev =
        misc::stdev<double>(accum_state.m_threes[i_team].m_free_throws.begin(),
                            accum_state.m_threes[i_team].m_free_throws.end(),
                            ret_val.m_threes[i_team].m_free_throws.m_mean);

    ret_val.m_field_goals[i_team].m_points.m_mean =
        misc::mean<double>(accum_state.m_field_goals[i_team].m_points.begin(),
                           accum_state.m_field_goals[i_team].m_points.end());
    ret_val.m_field_goals[i_team].m_points.m_min =
        misc::min<double>(accum_state.m_field_goals[i_team].m_points.begin(),
                          accum_state.m_field_goals[i_team].m_points.end());
    ret_val.m_field_goals[i_team].m_points.m_max =
        misc::max<double>(accum_state.m_field_goals[i_team].m_points.begin(),
                          accum_state.m_field_goals[i_team].m_points.end());
    ret_val.m_field_goals[i_team].m_points.m_stdev =
        misc::stdev<double>(accum_state.m_field_goals[i_team].m_points.begin(),
                            accum_state.m_field_goals[i_team].m_points.end(),
                            ret_val.m_field_goals[i_team].m_points.m_mean);
    ret_val.m_field_goals[i_team].m_rebounds.m_mean =
        misc::mean<double>(accum_state.m_field_goals[i_team].m_rebounds.begin(),
                           accum_state.m_field_goals[i_team].m_rebounds.end());
    ret_val.m_field_goals[i_team].m_rebounds.m_min =
        misc::min<double>(accum_state.m_field_goals[i_team].m_rebounds.begin(),
                          accum_state.m_field_goals[i_team].m_rebounds.end());
    ret_val.m_field_goals[i_team].m_rebounds.m_max =
        misc::max<double>(accum_state.m_field_goals[i_team].m_rebounds.begin(),
                          accum_state.m_field_goals[i_team].m_rebounds.end());
    ret_val.m_field_goals[i_team].m_rebounds.m_stdev = misc::stdev<double>(
        accum_state.m_field_goals[i_team].m_rebounds.begin(),
        accum_state.m_field_goals[i_team].m_rebounds.end(),
        ret_val.m_field_goals[i_team].m_rebounds.m_mean);
    ret_val.m_field_goals[i_team].m_assists.m_mean =
        misc::mean<double>(accum_state.m_field_goals[i_team].m_assists.begin(),
                           accum_state.m_field_goals[i_team].m_assists.end());
    ret_val.m_field_goals[i_team].m_assists.m_min =
        misc::min<double>(accum_state.m_field_goals[i_team].m_assists.begin(),
                          accum_state.m_field_goals[i_team].m_assists.end());
    ret_val.m_field_goals[i_team].m_assists.m_max =
        misc::max<double>(accum_state.m_field_goals[i_team].m_assists.begin(),
                          accum_state.m_field_goals[i_team].m_assists.end());
    ret_val.m_field_goals[i_team].m_assists.m_stdev =
        misc::stdev<double>(accum_state.m_field_goals[i_team].m_assists.begin(),
                            accum_state.m_field_goals[i_team].m_assists.end(),
                            ret_val.m_field_goals[i_team].m_assists.m_mean);
    ret_val.m_field_goals[i_team].m_steals.m_mean =
        misc::mean<double>(accum_state.m_field_goals[i_team].m_steals.begin(),
                           accum_state.m_field_goals[i_team].m_steals.end());
    ret_val.m_field_goals[i_team].m_steals.m_min =
        misc::min<double>(accum_state.m_field_goals[i_team].m_steals.begin(),
                          accum_state.m_field_goals[i_team].m_steals.end());
    ret_val.m_field_goals[i_team].m_steals.m_max =
        misc::max<double>(accum_state.m_field_goals[i_team].m_steals.begin(),
                          accum_state.m_field_goals[i_team].m_steals.end());
    ret_val.m_field_goals[i_team].m_steals.m_stdev =
        misc::stdev<double>(accum_state.m_field_goals[i_team].m_steals.begin(),
                            accum_state.m_field_goals[i_team].m_steals.end(),
                            ret_val.m_field_goals[i_team].m_steals.m_mean);
    ret_val.m_field_goals[i_team].m_blocks.m_mean =
        misc::mean<double>(accum_state.m_field_goals[i_team].m_blocks.begin(),
                           accum_state.m_field_goals[i_team].m_blocks.end());
    ret_val.m_field_goals[i_team].m_blocks.m_min =
        misc::min<double>(accum_state.m_field_goals[i_team].m_blocks.begin(),
                          accum_state.m_field_goals[i_team].m_blocks.end());
    ret_val.m_field_goals[i_team].m_blocks.m_max =
        misc::max<double>(accum_state.m_field_goals[i_team].m_blocks.begin(),
                          accum_state.m_field_goals[i_team].m_blocks.end());
    ret_val.m_field_goals[i_team].m_blocks.m_stdev =
        misc::stdev<double>(accum_state.m_field_goals[i_team].m_blocks.begin(),
                            accum_state.m_field_goals[i_team].m_blocks.end(),
                            ret_val.m_field_goals[i_team].m_blocks.m_mean);
    ret_val.m_field_goals[i_team].m_threes.m_mean =
        misc::mean<double>(accum_state.m_field_goals[i_team].m_threes.begin(),
                           accum_state.m_field_goals[i_team].m_threes.end());
    ret_val.m_field_goals[i_team].m_threes.m_min =
        misc::min<double>(accum_state.m_field_goals[i_team].m_threes.begin(),
                          accum_state.m_field_goals[i_team].m_threes.end());
    ret_val.m_field_goals[i_team].m_threes.m_max =
        misc::max<double>(accum_state.m_field_goals[i_team].m_threes.begin(),
                          accum_state.m_field_goals[i_team].m_threes.end());
    ret_val.m_field_goals[i_team].m_threes.m_stdev =
        misc::stdev<double>(accum_state.m_field_goals[i_team].m_threes.begin(),
                            accum_state.m_field_goals[i_team].m_threes.end(),
                            ret_val.m_field_goals[i_team].m_threes.m_mean);
    ret_val.m_field_goals[i_team].m_field_goals.m_mean = misc::mean<double>(
        accum_state.m_field_goals[i_team].m_field_goals.begin(),
        accum_state.m_field_goals[i_team].m_field_goals.end());
    ret_val.m_field_goals[i_team].m_field_goals.m_min = misc::min<double>(
        accum_state.m_field_goals[i_team].m_field_goals.begin(),
        accum_state.m_field_goals[i_team].m_field_goals.end());
    ret_val.m_field_goals[i_team].m_field_goals.m_max = misc::max<double>(
        accum_state.m_field_goals[i_team].m_field_goals.begin(),
        accum_state.m_field_goals[i_team].m_field_goals.end());
    ret_val.m_field_goals[i_team].m_field_goals.m_stdev = misc::stdev<double>(
        accum_state.m_field_goals[i_team].m_field_goals.begin(),
        accum_state.m_field_goals[i_team].m_field_goals.end(),
        ret_val.m_field_goals[i_team].m_field_goals.m_mean);
    ret_val.m_field_goals[i_team].m_free_throws.m_mean = misc::mean<double>(
        accum_state.m_field_goals[i_team].m_free_throws.begin(),
        accum_state.m_field_goals[i_team].m_free_throws.end());
    ret_val.m_field_goals[i_team].m_free_throws.m_min = misc::min<double>(
        accum_state.m_field_goals[i_team].m_free_throws.begin(),
        accum_state.m_field_goals[i_team].m_free_throws.end());
    ret_val.m_field_goals[i_team].m_free_throws.m_max = misc::max<double>(
        accum_state.m_field_goals[i_team].m_free_throws.begin(),
        accum_state.m_field_goals[i_team].m_free_throws.end());
    ret_val.m_field_goals[i_team].m_free_throws.m_stdev = misc::stdev<double>(
        accum_state.m_field_goals[i_team].m_free_throws.begin(),
        accum_state.m_field_goals[i_team].m_free_throws.end(),
        ret_val.m_field_goals[i_team].m_free_throws.m_mean);

    ret_val.m_free_throws[i_team].m_points.m_mean =
        misc::mean<double>(accum_state.m_free_throws[i_team].m_points.begin(),
                           accum_state.m_free_throws[i_team].m_points.end());
    ret_val.m_free_throws[i_team].m_points.m_min =
        misc::min<double>(accum_state.m_free_throws[i_team].m_points.begin(),
                          accum_state.m_free_throws[i_team].m_points.end());
    ret_val.m_free_throws[i_team].m_points.m_max =
        misc::max<double>(accum_state.m_free_throws[i_team].m_points.begin(),
                          accum_state.m_free_throws[i_team].m_points.end());
    ret_val.m_free_throws[i_team].m_points.m_stdev =
        misc::stdev<double>(accum_state.m_free_throws[i_team].m_points.begin(),
                            accum_state.m_free_throws[i_team].m_points.end(),
                            ret_val.m_free_throws[i_team].m_points.m_mean);
    ret_val.m_free_throws[i_team].m_rebounds.m_mean =
        misc::mean<double>(accum_state.m_free_throws[i_team].m_rebounds.begin(),
                           accum_state.m_free_throws[i_team].m_rebounds.end());
    ret_val.m_free_throws[i_team].m_rebounds.m_min =
        misc::min<double>(accum_state.m_free_throws[i_team].m_rebounds.begin(),
                          accum_state.m_free_throws[i_team].m_rebounds.end());
    ret_val.m_free_throws[i_team].m_rebounds.m_max =
        misc::max<double>(accum_state.m_free_throws[i_team].m_rebounds.begin(),
                          accum_state.m_free_throws[i_team].m_rebounds.end());
    ret_val.m_free_throws[i_team].m_rebounds.m_stdev = misc::stdev<double>(
        accum_state.m_free_throws[i_team].m_rebounds.begin(),
        accum_state.m_free_throws[i_team].m_rebounds.end(),
        ret_val.m_free_throws[i_team].m_rebounds.m_mean);
    ret_val.m_free_throws[i_team].m_assists.m_mean =
        misc::mean<double>(accum_state.m_free_throws[i_team].m_assists.begin(),
                           accum_state.m_free_throws[i_team].m_assists.end());
    ret_val.m_free_throws[i_team].m_assists.m_min =
        misc::min<double>(accum_state.m_free_throws[i_team].m_assists.begin(),
                          accum_state.m_free_throws[i_team].m_assists.end());
    ret_val.m_free_throws[i_team].m_assists.m_max =
        misc::max<double>(accum_state.m_free_throws[i_team].m_assists.begin(),
                          accum_state.m_free_throws[i_team].m_assists.end());
    ret_val.m_free_throws[i_team].m_assists.m_stdev =
        misc::stdev<double>(accum_state.m_free_throws[i_team].m_assists.begin(),
                            accum_state.m_free_throws[i_team].m_assists.end(),
                            ret_val.m_free_throws[i_team].m_assists.m_mean);
    ret_val.m_free_throws[i_team].m_steals.m_mean =
        misc::mean<double>(accum_state.m_free_throws[i_team].m_steals.begin(),
                           accum_state.m_free_throws[i_team].m_steals.end());
    ret_val.m_free_throws[i_team].m_steals.m_min =
        misc::min<double>(accum_state.m_free_throws[i_team].m_steals.begin(),
                          accum_state.m_free_throws[i_team].m_steals.end());
    ret_val.m_free_throws[i_team].m_steals.m_max =
        misc::max<double>(accum_state.m_free_throws[i_team].m_steals.begin(),
                          accum_state.m_free_throws[i_team].m_steals.end());
    ret_val.m_free_throws[i_team].m_steals.m_stdev =
        misc::stdev<double>(accum_state.m_free_throws[i_team].m_steals.begin(),
                            accum_state.m_free_throws[i_team].m_steals.end(),
                            ret_val.m_free_throws[i_team].m_steals.m_mean);
    ret_val.m_free_throws[i_team].m_blocks.m_mean =
        misc::mean<double>(accum_state.m_free_throws[i_team].m_blocks.begin(),
                           accum_state.m_free_throws[i_team].m_blocks.end());
    ret_val.m_free_throws[i_team].m_blocks.m_min =
        misc::min<double>(accum_state.m_free_throws[i_team].m_blocks.begin(),
                          accum_state.m_free_throws[i_team].m_blocks.end());
    ret_val.m_free_throws[i_team].m_blocks.m_max =
        misc::max<double>(accum_state.m_free_throws[i_team].m_blocks.begin(),
                          accum_state.m_free_throws[i_team].m_blocks.end());
    ret_val.m_free_throws[i_team].m_blocks.m_stdev =
        misc::stdev<double>(accum_state.m_free_throws[i_team].m_blocks.begin(),
                            accum_state.m_free_throws[i_team].m_blocks.end(),
                            ret_val.m_free_throws[i_team].m_blocks.m_mean);
    ret_val.m_free_throws[i_team].m_threes.m_mean =
        misc::mean<double>(accum_state.m_free_throws[i_team].m_threes.begin(),
                           accum_state.m_free_throws[i_team].m_threes.end());
    ret_val.m_free_throws[i_team].m_threes.m_min =
        misc::min<double>(accum_state.m_free_throws[i_team].m_threes.begin(),
                          accum_state.m_free_throws[i_team].m_threes.end());
    ret_val.m_free_throws[i_team].m_threes.m_max =
        misc::max<double>(accum_state.m_free_throws[i_team].m_threes.begin(),
                          accum_state.m_free_throws[i_team].m_threes.end());
    ret_val.m_free_throws[i_team].m_threes.m_stdev =
        misc::stdev<double>(accum_state.m_free_throws[i_team].m_threes.begin(),
                            accum_state.m_free_throws[i_team].m_threes.end(),
                            ret_val.m_free_throws[i_team].m_threes.m_mean);
    ret_val.m_free_throws[i_team].m_field_goals.m_mean = misc::mean<double>(
        accum_state.m_free_throws[i_team].m_field_goals.begin(),
        accum_state.m_free_throws[i_team].m_field_goals.end());
    ret_val.m_free_throws[i_team].m_field_goals.m_min = misc::min<double>(
        accum_state.m_free_throws[i_team].m_field_goals.begin(),
        accum_state.m_free_throws[i_team].m_field_goals.end());
    ret_val.m_free_throws[i_team].m_field_goals.m_max = misc::max<double>(
        accum_state.m_free_throws[i_team].m_field_goals.begin(),
        accum_state.m_free_throws[i_team].m_field_goals.end());
    ret_val.m_free_throws[i_team].m_field_goals.m_stdev = misc::stdev<double>(
        accum_state.m_free_throws[i_team].m_field_goals.begin(),
        accum_state.m_free_throws[i_team].m_field_goals.end(),
        ret_val.m_free_throws[i_team].m_field_goals.m_mean);
    ret_val.m_free_throws[i_team].m_free_throws.m_mean = misc::mean<double>(
        accum_state.m_free_throws[i_team].m_free_throws.begin(),
        accum_state.m_free_throws[i_team].m_free_throws.end());
    ret_val.m_free_throws[i_team].m_free_throws.m_min = misc::min<double>(
        accum_state.m_free_throws[i_team].m_free_throws.begin(),
        accum_state.m_free_throws[i_team].m_free_throws.end());
    ret_val.m_free_throws[i_team].m_free_throws.m_max = misc::max<double>(
        accum_state.m_free_throws[i_team].m_free_throws.begin(),
        accum_state.m_free_throws[i_team].m_free_throws.end());
    ret_val.m_free_throws[i_team].m_free_throws.m_stdev = misc::stdev<double>(
        accum_state.m_free_throws[i_team].m_free_throws.begin(),
        accum_state.m_free_throws[i_team].m_free_throws.end(),
        ret_val.m_free_throws[i_team].m_free_throws.m_mean);
  }

  return ret_val;
}
