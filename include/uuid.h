#include <vector>
#include <iostream>
#include <sstream>
#include <random>
/**
 * @file uuid.h
 * @author Samrat Neupane (samratneupane215@gmail.com)
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string>

class UUID
{
private:
  unsigned char random_char()
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return static_cast<unsigned char>(dis(gen));
  }

  std::string generate_hex(const unsigned int len)
  {
    std::stringstream ss;
    for (auto i = 0; i < len; i++)
    {
      const auto rc = random_char();
      std::stringstream hexstream;
      hexstream << std::hex << int(rc);
      auto hex = hexstream.str();
      ss << (hex.length() < 2 ? '0' + hex : hex);
    }
    return ss.str();
  }

public:
  std::string uuid()
  {
    return generate_hex(16);
  }
};
