#ifndef BROWN_BASKETBALL_PRINTING_HPP
#define BROWN_BASKETBALL_PRINTING_HPP

#include "analysis.hpp"

#include <iostream>

namespace brown_basketball {
namespace printing {
void print_result(std::ostream &out, const analysis1::read_t &result);
}; // namespace printing

} // namespace brown_basketball
#endif
