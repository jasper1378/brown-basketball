#ifndef BROWN_BASKETBALL_DATABASE_HPP
#define BROWN_BASKETBALL_DATABASE_HPP

#include "common.hpp"

#include <array>
#include <string>
#include <string_view>

namespace brown_basketball {

namespace database {

std::array<common::player, common::k_pool_size>
read_database(const std::string &file_path);

namespace impl {
static constexpr std::string k_key_str_player_database{"player_database"};
static constexpr std::string k_key_str_name{"name"};
static constexpr std::string k_key_str_position{"positions"};
static const std::string k_key_str_draft_range_begin{"draft_range_begin"};
static constexpr std::string k_key_str_draft_range_end{"draft_range_end"};
static constexpr auto &k_key_str_categories{common::k_category_split_strs};

std::array<common::player, common::k_pool_size>
read_database(const std::string &file_path);

common::position position_string_to_enum(const std::string_view str);
} // namespace impl
} // namespace database

} // namespace brown_basketball
#endif
