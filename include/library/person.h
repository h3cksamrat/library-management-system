/**
 * @file person.h
 * @author Samrat Neupane (samratneupane215@gmail.com)
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <iostream>
#include "nlohmann/json.hpp"
#include "uuid.h"

class LibraryBook;
class Person
{
  std::string name, address, id;
  int age;

  friend class LibraryBook;

public:
  Person() {}

  Person(std::string name, std::string address, int age)
  {
    UUID u;
    this->name = name;
    this->address = address;
    this->age = age;
    id = u.uuid();
  }

  nlohmann::json to_json()
  {
    if (name == "")
      throw;
    return {
        {"id", id},
        {"name", name},
        {"address", address},
        {"age", age},
    };
  }

};
