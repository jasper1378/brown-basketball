#include "database.hpp"

#include "common.hpp"

#include "libconfigfile.hpp"

#include <array>
#include <exception>
#include <stdexcept>
#include <string>

std::array<common::player, common::g_k_player_count>
database::read_database(const std::string &file_path) {
  return impl::read_database(file_path);
}

std::array<common::player, common::g_k_player_count>
database::impl::read_database(const std::string &file_path) {
  libconfigfile::node_ptr<libconfigfile::map_node> parsed_database{
      libconfigfile::parse_file(file_path)};

  if (parsed_database->contains(g_k_player_database_key_str)) {
    // TODO continue from here
  } else {
    throw std::runtime_error{
        "configuration file does not contain player database"};
  }
}

common::position
database::impl::position_string_to_enum(const std::string &str) {
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
