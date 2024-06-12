#ifndef BROWN_BASKETBALL_ANALYSIS1_HPP
#define BROWN_BASKETBALL_ANALYSIS1_HPP

#include "common.hpp"
#include "scoring.hpp"

#include <array>
#include <type_traits>
#include <utility>

namespace brown_basketball {
namespace analysis1 {

namespace impl {

struct rank_cats_counts {
  unsigned long m_top;
  unsigned long m_cutoff;
};

using rank_counts = common::categories<rank_cats_counts>;

struct trial_rank_counts {
  unsigned long m_trial_count;
  rank_counts m_rank_counts;
};
} // namespace impl

struct rank_cats_probs {
  double m_top;
  double m_cutoff;
};

using rank_probs = common::categories<rank_cats_probs>;

using accum_state_t =
    std::array<std::pair<const common::player *, impl::trial_rank_counts>,
               common::k_pool_size>;
using add_t = std::array<scoring::team_ranks, common::k_league_size>;
using read_t = std::array<std::pair<const common::player *, rank_probs>,
                          common::k_pool_size>;

class accum_state {
private:
  accum_state_t m_accum_state;
  unsigned long m_trial_count;

public:
  accum_state(
      const std::array<common::player, common::k_pool_size> &database);
  accum_state(const accum_state &other) = default;
  accum_state(accum_state &&other) noexcept(
      std::is_nothrow_move_constructible_v<decltype(m_accum_state)>) = default;

  ~accum_state() = default;

  accum_state &operator=(const accum_state &other) = default;
  accum_state &operator=(accum_state &&other) noexcept(
      std::is_nothrow_move_assignable_v<decltype(m_accum_state)>) = default;

public:
  void add(const add_t &league);
  read_t read() const;
};

namespace impl {
accum_state_t accum_state_init_accum_state(
    const std::array<common::player, common::k_pool_size> &database);
unsigned long accum_state_init_trial_count();
void accum_state_add(accum_state_t &accum_state, unsigned long &trial_count,
                     const add_t &league);
read_t accum_state_read(const accum_state_t &accum_state,
                        const unsigned long trial_count);
} // namespace impl
} // namespace analysis1
} // namespace brown_basketball
#endif
