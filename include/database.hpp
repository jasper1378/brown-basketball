#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "common.hpp"

#include <array>
#include <string>

namespace database {

std::array<common::player, common::g_k_pool_size>
read_database(const std::string &file_path);

namespace impl {
static constexpr std::string g_k_key_str_player_database{"player_database"};
static constexpr std::string g_k_key_str_name{"name"};
static constexpr std::string g_k_key_str_position{"position"};
static constexpr std::string g_k_key_str_points{"points"};
static constexpr std::string g_k_key_str_rebounds{"rebounds"};
static constexpr std::string g_k_key_str_assists{"assists"};
static constexpr std::string g_k_key_str_steals{"steals"};
static constexpr std::string g_k_key_str_blocks{"blocks"};
static constexpr std::string g_k_key_str_threes{"threes"};
static const std::string g_k_key_str_field_goals_made{"field_goals_made"};
static const std::string g_k_key_str_field_goals_attempted{
    "field_goals_attempted"};
static const std::string g_k_key_str_free_throws_made{"free_throws_made"};
static const std::string g_k_key_str_free_throws_attempted{
    "free_throws_attempted"};

std::array<common::player, common::g_k_pool_size>
read_database(const std::string &file_path);

common::position::type position_string_to_enum(const std::string &str);
} // namespace impl
} // namespace database

#endif
