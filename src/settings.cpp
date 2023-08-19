#include "settings.hpp"

#include "player.hpp"

#include <vector>

bool settings::verify(const std::vector<player::team> &league) {
  if (league.size() != g_k_league_size) {
    return false;
  } else {
    for (auto p{league.begin()}; p != league.end(); ++p) {
      if (p->m_players.size() != g_k_team_size) {
        return false;
      }
    }
  }
  return true;
}
