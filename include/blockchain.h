/**
 * @file blockchain.h
 * @author Samrat Neupane (samratneupane215@gmail.com)
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <iostream>
#include "block.h"
#include "sha256.h"
#include "uuid.h"
#include "nlohmann/json.hpp"

class BlockChain
{
private:
  Block *previous;
  Block *head;

  static BlockChain *blockchain;
  // private constructor to force use of getInstance() to create Singleton object
  BlockChain()
  {
    previous = nullptr;
    head = nullptr;
    std::cout << __FUNCTION__ << " Created" << std::endl;
  }

public:
  static long unsigned int numberOfBlocks;

  static BlockChain *getInstance()
  {
    if (blockchain == nullptr)
    {
      blockchain = new BlockChain;
    }
    return blockchain;
  }

  std::string uuid()
  {
    UUID u;
    return u.uuid();
  }

  std::string generateHashSHA256(std::string toHash)
  {
    return sha256(toHash);
  }

  int addNode(std::string new_data)
  {

    Block *new_block = new Block;

    new_block->data = new_data;
    new_block->next = nullptr;

    if (previous != nullptr)
    {
      previous = head;
      head = new_block;
      new_block->actual_hash = generateHashSHA256(new_data + previous->actual_hash);
      new_block->prev_hash = previous->actual_hash;

      new_block->prev = previous;
    }

    if (previous == nullptr)
    {
      head = new_block;
      previous = head;

      new_block->prev_hash = generateHashSHA256(uuid());
      new_block->data = new_data;
      new_block->actual_hash = generateHashSHA256(new_data);
    }

    std::cout << previous << " :: " << head << std::endl;

    numberOfBlocks++;

    return numberOfBlocks;
  }

  void traverseBlockChain(BlockChain &chain)
  {

    Block *actual_node = chain.head;
    int currentBlock = numberOfBlocks;

    while (actual_node != nullptr)
    {
      std::cout << "block : " << currentBlock << std::endl;
      std::cout << "data  : " << actual_node->data << std::endl;
      actual_node = actual_node->prev;
      currentBlock--;
    }
  }

  int getNumberOfBlocks()
  {
    return numberOfBlocks;
  }

  void checkChainConsistency(BlockChain &chain)
  {
    Block *actual_node = chain.head;
    int currentBlock = numberOfBlocks;

    while ((actual_node->prev != nullptr) && (currentBlock > 2))
    {
      std::cout << std::endl
                << "block : " << currentBlock << std::endl;
      std::string check_hash;
      std::string check_data;
      std::string check_hashFWD;
      std::string check_dataFWD;

      check_data = (actual_node->prev)->data;
      check_hash = (actual_node->prev)->prev_hash;

      check_dataFWD = actual_node->data;
      check_hashFWD = actual_node->prev_hash;

      if (actual_node->prev != nullptr)
      {
        std::string FWDCalculatedHash = generateHashSHA256(check_dataFWD + check_hashFWD);
        std::string injectedCalculatedHash = generateHashSHA256(check_data + check_hash);

        std::string storedHash = (actual_node->prev)->actual_hash;

        if (injectedCalculatedHash == check_hashFWD)
        {
          std::cout << " HASH OK ==> " << currentBlock - 1 << " Block Healthy !! " << std::endl;
        }
        if (injectedCalculatedHash != check_hashFWD)
        {
          std::cout << " HASH WRONG ==> " << currentBlock - 1 << " Block MANIPULATED !! " << std::endl;
        }
      }

      actual_node = actual_node->prev;
      currentBlock--;
    }
  }

  void recalulcateChain(BlockChain &chain)
  {

    Block *node = chain.head;

    std::vector<std::string> tempChainData;
    std::vector<Block *> ptr_node{node};
    std::vector<Block *> recal_node{numberOfBlocks};

    while (node->prev != nullptr)
    {

      tempChainData.push_back(node->data);
      node = node->prev;
      ptr_node.push_back(node);

      if (node->prev == nullptr)
      {
        tempChainData.push_back(node->data);
      }
    }

    int i = 0;
    for (auto &ii : ptr_node)
    {
      recal_node[numberOfBlocks - 1 - i] = ii;
      i++;
    }

    int j = 0;
    for (auto &ii : recal_node)
    {

      if (j == 0)
      {
        ii->prev_hash = generateHashSHA256(uuid());
        ii->actual_hash = generateHashSHA256(ii->data);
      }

      if (j > 0)
      {

        ii->actual_hash = generateHashSHA256(ii->data + (ii->prev)->actual_hash);
        ii->prev_hash = (ii->prev)->actual_hash;
      }

      j++;
    }
  }

  void injectDataInBlock(BlockChain &chain, int injectToBlock, std::string injectData)
  {

    Block *actual_node = chain.head;
    int currentBlock = numberOfBlocks;

    if (injectToBlock == 1)
    {
      std::cout << "Cannot inject to Genesis Block" << std::endl;
      return;
    }

    if (injectToBlock > numberOfBlocks)
    {
      std::cout << "Block not found" << std::endl;
      return;
    }

    while (actual_node->prev != nullptr)
    {
      if (currentBlock == injectToBlock)
      {
        std::cout << "Injecting data in block " << injectToBlock << std::endl;
        actual_node->data = injectData;
        actual_node->actual_hash = generateHashSHA256(injectData + actual_node->prev_hash);
        break;
      }

      actual_node = actual_node->prev;
      currentBlock--;
    }
  }

  nlohmann::json getBlockById(int id)
  {
    if (id > numberOfBlocks || id < 1)
    {
      std::cout << "Block not found" << std::endl;
      return nlohmann::json({
          {"error", "Block not found"},
      });
    }

    Block *actual_node = head;
    int currentBlock = numberOfBlocks;
    nlohmann::json json;
    while (actual_node != nullptr)
    {
      if (currentBlock == id)
      {
        json["data"] = actual_node->data;
        json["actual_hash"] = actual_node->actual_hash;
        json["prev_hash"] = actual_node->prev_hash;
        break;
      }
      actual_node = actual_node->prev;
      currentBlock--;
    }
    return json;
  }
};
