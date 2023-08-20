#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "common.hpp"

#include <vector>

namespace settings {

static constexpr int g_k_league_size{12};
static constexpr int g_k_team_size{10};

bool verify(const std::vector<common::team> &league);
} // namespace settings

#endif
