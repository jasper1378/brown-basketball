#ifndef BROWN_BASKETBALL_DATABASE_HPP
#define BROWN_BASKETBALL_DATABASE_HPP

#include "common.hpp"

#include <array>
#include <string>
#include <string_view>

namespace brown_basketball {

namespace database {

std::array<common::player, common::g_k_pool_size>
read_database(const std::string &file_path);

namespace impl {
static constexpr std::string g_k_key_str_player_database{"player_database"};
static constexpr std::string g_k_key_str_name{"name"};
static constexpr std::string g_k_key_str_position{"positions"};
static const std::string g_k_key_str_draft_range_begin{"draft_range_begin"};
static constexpr std::string g_k_key_str_draft_range_end{"draft_range_end"};
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

common::position position_string_to_enum(const std::string_view str);
} // namespace impl
} // namespace database

} // namespace brown_basketball
#endif
