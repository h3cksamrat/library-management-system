/**
 * @file libraryBook.h
 * @author Samrat Neupane (samratneupane215@gmail.com)
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <iostream>
#include "nlohmann/json.hpp"
#include "library/book.h"
#include "library/person.h"
#include "uuid.h"
#include "blockchain.h"

class LibraryBook : public Book
{
  std::string id;
  int rentStatus = 0;

public:
  LibraryBook() {}
  LibraryBook(Book &book) : Book(book)
  {
    UUID u;
    id = u.uuid();
  }

  nlohmann::json to_json()
  {
    if (name == "")
      throw;
    return {
        {"id", id},
        {"name", name},
        {"author", author},
        {"additionalInfo", additionalInfo},
    };
  }

  int rentBook(Person &person)
  {
    if (rentStatus)
    {
      std::cout << "Book is already rented" << std::endl;
      return -1;
    }

    BlockChain* chain = BlockChain::getInstance();
    nlohmann::json j = {
        {"libraryBook", id},
        {"rentedBy", person.id},
        {"rentedAt", __DATE__},
    };

    rentStatus = 1;

    return (*chain).addNode(j.dump());
  }

  int returnBook()
  {
    if (!rentStatus)
    {
      std::cout << "Book is not rented" << std::endl;
      return -1;
    }

    BlockChain* chain = BlockChain::getInstance();
    nlohmann::json j = {
        {"libraryBook", id},
        {"returnedAt", __DATE__},
    };

    rentStatus = 0;

    return (*chain).addNode(j.dump());
  }
};
