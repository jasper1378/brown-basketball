#include "database.hpp"

#include "common.hpp"

#include "libconfigfile/libconfigfile.hpp"

#include <array>
#include <exception>
#include <stdexcept>
#include <string>
#include <string_view>

std::array<brown_basketball::common::player,
           brown_basketball::common::g_k_pool_size>
brown_basketball::database::read_database(const std::string &file_path) {
  return impl::read_database(file_path);
}

std::array<brown_basketball::common::player,
           brown_basketball::common::g_k_pool_size>
brown_basketball::database::impl::read_database(const std::string &file_path) {
  libconfigfile::node_ptr<libconfigfile::map_node> parsed_database{nullptr};
  try {
    parsed_database = libconfigfile::parse_file(file_path);
  } catch (const std::exception &e) {
    throw std::runtime_error{"error in libconfigfile while parsing \"" +
                             file_path + "\": " + e.what()};
  }

  if (auto p_player_database{
          parsed_database->find(g_k_key_str_player_database)};
      p_player_database != parsed_database->end()) {
    libconfigfile::node_ptr<libconfigfile::node> player_database{
        std::move(p_player_database->second)};
    if (player_database->get_node_type() == libconfigfile::node_type::Array) {
      libconfigfile::node_ptr<libconfigfile::array_node>
          player_database_as_array{
              libconfigfile::node_ptr_cast<libconfigfile::array_node>(
                  std::move(player_database))};
      if (player_database_as_array->size() == common::g_k_pool_size) {
        std::array<common::player, common::g_k_pool_size> ret_val{};

        for (std::size_t i_player{0};
             i_player < player_database_as_array->size(); ++i_player) {

          if (player_database_as_array->operator[](i_player)->get_node_type() ==
              libconfigfile::node_type::Map) {
            libconfigfile::node_ptr<libconfigfile::map_node>
                player_database_player_as_map{
                    libconfigfile::node_ptr_cast<libconfigfile::map_node>(
                        std::move(
                            player_database_as_array->operator[](i_player)))};
            const auto check_contains_and_type{
                [&player_database_player_as_map](
                    const std::string &key, const libconfigfile::node_type type)
                    -> libconfigfile::node_ptr<libconfigfile::node> {
                  if (auto p_field{player_database_player_as_map->find(key)};
                      p_field != player_database_player_as_map->end()) {
                    if (p_field->second->get_node_type() == type) {
                      return p_field->second;
                    } else {
                      throw std::runtime_error{
                          "incorrect data type in player database"};
                    }
                  } else {
                    throw std::runtime_error{
                        "missing field in player database"};
                  }
                }};

            ret_val[i_player].m_idx = i_player;

            libconfigfile::node_ptr<libconfigfile::string_node> field_name{
                libconfigfile::node_ptr_cast<libconfigfile::string_node>(
                    check_contains_and_type(g_k_key_str_name,
                                            libconfigfile::node_type::String))};
            ret_val[i_player].m_info.m_name =
                libconfigfile::node_to_base(std::move(*field_name));

            libconfigfile::node_ptr<libconfigfile::array_node> field_position{
                libconfigfile::node_ptr_cast<libconfigfile::array_node>(
                    check_contains_and_type(g_k_key_str_position,
                                            libconfigfile::node_type::Array))};
            ret_val[i_player].m_info.m_positions = {
                [](const libconfigfile::node_ptr<libconfigfile::array_node>
                       &arr) -> common::position::type {
                  common::position::type ret_val{0};
                  for (auto p_pos{arr->begin()}; p_pos != arr->end(); ++p_pos) {
                    if ((*p_pos)->get_node_type() ==
                        libconfigfile::node_type::String) {
                      common::position::type next_pos{
                          position_string_to_enum(libconfigfile::node_to_base(
                              std::move(*libconfigfile::node_ptr_cast<
                                        libconfigfile::string_node>(
                                  std::move(*p_pos)))))};
                      if (next_pos == common::position::NONE) {
                        throw std::runtime_error{
                            "invalid position string in player database"};
                      } else {
                        ret_val |= next_pos;
                      }
                    } else {
                      throw std::runtime_error{
                          "incorrect data type in player database"};
                    }
                  }
                  return ret_val;
                }(field_position)};

            libconfigfile::node_ptr<libconfigfile::integer_node>
                field_draft_range_begin{
                    libconfigfile::node_ptr_cast<libconfigfile::integer_node>(
                        check_contains_and_type(
                            g_k_key_str_draft_range_begin,
                            libconfigfile::node_type::Integer))};
            if (!((field_draft_range_begin->get() > 0) &&
                  (field_draft_range_begin->get() <= common::g_k_pool_size))) {
              throw std::runtime_error{
                  "invalid draft range in player database"};
            }
            ret_val[i_player].m_info.m_draft_range_begin =
                libconfigfile::node_to_base(
                    std::move(*field_draft_range_begin));

            libconfigfile::node_ptr<libconfigfile::integer_node>
                field_draft_range_end{
                    libconfigfile::node_ptr_cast<libconfigfile::integer_node>(
                        check_contains_and_type(
                            g_k_key_str_draft_range_end,
                            libconfigfile::node_type::Integer))};
            if (!((field_draft_range_end->get() > 0) &&
                  (field_draft_range_end->get() <= common::g_k_pool_size))) {
              throw std::runtime_error{
                  "invalid draft range in player database"};
            }
            ret_val[i_player].m_info.m_draft_range_end =
                libconfigfile::node_to_base(std::move(*field_draft_range_end));

            if (ret_val[i_player].m_info.m_draft_range_begin >
                ret_val[i_player].m_info.m_draft_range_end) {
              throw std::runtime_error{
                  "invalid draft range in player database"};
            }

            libconfigfile::node_ptr<libconfigfile::float_node> field_points{
                libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                    check_contains_and_type(g_k_key_str_points,
                                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_points =
                libconfigfile::node_to_base(std::move(*field_points));

            libconfigfile::node_ptr<libconfigfile::float_node> field_rebounds{
                libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                    check_contains_and_type(g_k_key_str_rebounds,
                                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_rebounds =
                libconfigfile::node_to_base(std::move(*field_rebounds));

            libconfigfile::node_ptr<libconfigfile::float_node> field_assists{
                libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                    check_contains_and_type(g_k_key_str_assists,
                                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_assists =
                libconfigfile::node_to_base(std::move(*field_assists));

            libconfigfile::node_ptr<libconfigfile::float_node> field_steals{
                libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                    check_contains_and_type(g_k_key_str_steals,
                                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_steals =
                libconfigfile::node_to_base(std::move(*field_steals));

            libconfigfile::node_ptr<libconfigfile::float_node> field_blocks{
                libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                    check_contains_and_type(g_k_key_str_blocks,
                                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_blocks =
                libconfigfile::node_to_base(std::move(*field_blocks));

            libconfigfile::node_ptr<libconfigfile::float_node> field_threes{
                libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                    check_contains_and_type(g_k_key_str_threes,
                                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_threes =
                libconfigfile::node_to_base(std::move(*field_threes));

            libconfigfile::node_ptr<libconfigfile::float_node>
                field_field_goals_made{
                    libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                        check_contains_and_type(
                            g_k_key_str_field_goals_made,
                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_field_goals_made =
                libconfigfile::node_to_base(std::move(*field_field_goals_made));

            libconfigfile::node_ptr<libconfigfile::float_node>
                field_field_goals_attempted{
                    libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                        check_contains_and_type(
                            g_k_key_str_field_goals_attempted,
                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_field_goals_attempted =
                libconfigfile::node_to_base(
                    std::move(*field_field_goals_attempted));

            libconfigfile::node_ptr<libconfigfile::float_node>
                field_free_throws_made{
                    libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                        check_contains_and_type(
                            g_k_key_str_free_throws_made,
                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_free_throws_made =
                libconfigfile::node_to_base(std::move(*field_free_throws_made));

            libconfigfile::node_ptr<libconfigfile::float_node>
                field_free_throws_attempted{
                    libconfigfile::node_ptr_cast<libconfigfile::float_node>(
                        check_contains_and_type(
                            g_k_key_str_free_throws_attempted,
                            libconfigfile::node_type::Float))};
            ret_val[i_player].m_stats.m_free_throws_attempted =
                libconfigfile::node_to_base(
                    std::move(*field_free_throws_attempted));

          } else {
            throw std::runtime_error{"incorrect data type in player database"};
          }
        }
        return ret_val;
      } else {
        throw std::runtime_error{"incorrect player count in player database"};
      }
    } else {
      throw std::runtime_error{"incorrect data type in player database"};
    }
  } else {
    throw std::runtime_error{
        "configuration file does not contain player database"};
  }
}

brown_basketball::common::position::type
brown_basketball::database::impl::position_string_to_enum(
    const std::string_view str) {
  if (str == "PG") {
    return common::position::POINT_GUARD;
  } else if (str == "SG") {
    return common::position::SHOOTING_GUARD;
  } else if (str == "SF") {
    return common::position::SMALL_FORWARD;
  } else if (str == "PF") {
    return common::position::POWER_FORWARD;
  } else if (str == "C") {
    return common::position::CENTER;
  } else {
    return common::position::NONE;
  }
}
