/**
 * @file main.cpp
 * @author Samrat Neupane (samratneupane215@gmail.com)
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include "blockchain.h"
#include "nlohmann/json.hpp"
#include "library/libraryBook.h"
#include "library/book.h"
#include "library/person.h"
#include "crow.h"
#include "api/app.h"

using json = nlohmann::json;

BlockChain *BlockChain::blockchain;
App *App::app;
long unsigned int BlockChain::numberOfBlocks{0};

int main()
{
  App *app = App::getInstance();
  BlockChain *chain = BlockChain::getInstance();
  Book book("C++", "Samrat", json({{"ISBN", "123456789"}}));
  LibraryBook libraryBook(book);
  Person person("Samrat", "USA", 20), person2("Santra", "USA", 20);
  libraryBook.rentBook(person);
  libraryBook.rentBook(person2);
  libraryBook.returnBook();
  libraryBook.returnBook();

  CROW_ROUTE((*app), "/block/<int>")
  ([](int id)
   { return BlockChain::getInstance()->getBlockById(id).dump(); });

  CROW_ROUTE((*app), "/book")
      .methods("POST"_method)([](const crow::request &req)
    {
      BlockChain *chain = BlockChain::getInstance();
      nlohmann::json j;
      try {
        j = nlohmann::json::parse(req.body);
      } catch (nlohmann::json::parse_error &e) {
        return crow::response(400, "Invalid JSON");
      }

      if (j.find("name") == j.end() || j.find("author") == j.end() || j.find("additionalInfo") == j.end())
        return crow::response(400);
      if (!j["name"].is_string() || !j["author"].is_string() || !j["additionalInfo"].is_object())
        return crow::response(400);

      const std::string name = j["name"].get<std::string>();
      const std::string author = j["author"].get<std::string>();
      const nlohmann::json additionalInfo = j["additionalInfo"].get<nlohmann::json>();

      if (name == "" || author == "" || additionalInfo.empty())
        return crow::response(400);

      Book book(name, author, additionalInfo);
      nlohmann::json bookJson = book.to_json();
      const int blockId = chain -> addNode(bookJson.dump());
      bookJson["blockId"] = blockId;
      return crow::response{
        200,
        bookJson.dump(),
      };
    });

  (*app).port(18080).multithreaded().run();
  return 0;
}
