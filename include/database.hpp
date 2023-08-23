#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "common.hpp"

#include <array>
#include <string>

namespace database {

std::array<common::player, common::g_k_player_count>
read_database(const std::string &file_path);

namespace impl {
static constexpr std::string g_k_player_database_key_str{"player_database"};
static constexpr std::string g_k_name_key_str{"name"};
static constexpr std::string g_k_position_key_str{"position"};
static constexpr std::string g_k_rebounds_key_str{"rebounds"};
static constexpr std::string g_k_assists_key_str{"assists"};
static constexpr std::string g_k_steals_key_str{"steals"};
static constexpr std::string g_k_blocks_key_str{"blocks"};
static constexpr std::string g_k_threes_key_str{"threes"};
static const std::string g_k_field_goals_made_key_str{"field_goals_made"};
static const std::string g_k_field_goals_attempted_key_str{
    "field_goals_attempted"};
static const std::string g_k_free_throws_made_key_str{"free_throws_made"};
static const std::string g_k_free_throws_attempted_key_str{
    "free_throws_attempted"};

std::array<common::player, common::g_k_player_count>
read_database(const std::string &file_path);

common::position position_string_to_enum(const std::string &str);
} // namespace impl
} // namespace database

#endif
