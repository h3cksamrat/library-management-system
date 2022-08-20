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
#include "library/person.h"

using json = nlohmann::json;

BlockChain *BlockChain::blockchain;
long unsigned int BlockChain::numberOfBlocks{0};

int main()
{
  BlockChain *chain = BlockChain::getInstance();
  Book book("C++", "Samrat", json({{"ISBN", "123456789"}}));
  LibraryBook libraryBook(book);
  Person person("Samrat", "USA", 20), person2("Santra", "USA", 20);
  libraryBook.rentBook(person);
  libraryBook.rentBook(person2);
  libraryBook.returnBook();
  libraryBook.returnBook();
  std::cout << (*chain).getBlockById(5).dump() << std::endl;
  return 0;
}
