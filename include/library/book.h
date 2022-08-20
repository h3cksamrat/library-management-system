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
#include "uuid.h"

class Book
{
protected:
  std::string bookId;
  std::string name, author;
  nlohmann::json additionalInfo;

public:
  Book() {}

  Book(std::string name, std::string author, nlohmann::json additionalInfo)
  {
    UUID uuid;
    this->name = name;
    this->author = author;
    this->additionalInfo = additionalInfo;
    this->bookId = uuid.uuid();
  }

  Book(Book &book)
  {
    this->name = book.name;
    this->author = book.author;
    this->additionalInfo = book.additionalInfo;
    this->bookId = book.bookId;
  }

  nlohmann::json to_json()
  {
    if (name == "" || bookId == "")
      throw;
    return {
        {"name", name},
        {"author", author},
        {"additionalInfo", additionalInfo},
        {"bookId", bookId},
    };
  }
};
