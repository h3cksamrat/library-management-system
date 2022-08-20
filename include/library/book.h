/**
 * @file book.h
 * @author Samrat Neupane (samratneupane215@gmail.com)
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <iostream>
#include "nlohmann/json.hpp"

class Book
{
protected:
  std::string name, author;
  nlohmann::json additionalInfo;

public:
  Book() {}

  Book(std::string name, std::string author, nlohmann::json additionalInfo)
  {
    this->name = name;
    this->author = author;
    this->additionalInfo = additionalInfo;
  }

  Book(Book &book)
  {
    this->name = book.name;
    this->author = book.author;
    this->additionalInfo = book.additionalInfo;
  }

  nlohmann::json to_json()
  {
    if (name == "")
      throw;
    return {
        {"name", name},
        {"author", author},
        {"additionalInfo", additionalInfo},
    };
  }
};
