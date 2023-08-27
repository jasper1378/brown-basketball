#include "random.hpp"

#include <chrono>
#include <random>

random::random()
    : m_rd{},
      m_ss{static_cast<unsigned int>(
               std::chrono::steady_clock::now().time_since_epoch().count()),
           m_rd(),
           m_rd(),
           m_rd(),
           m_rd(),
           m_rd(),
           m_rd(),
           m_rd(),
           m_rd()},
      m_mt{m_ss} {}

random::~random() {}

std::mt19937 &random::get_generator() { return m_mt; }
