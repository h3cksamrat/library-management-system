/**
 * @file main.cpp
 * @author Samrat Neupane (samratneupane215@gmail.com)
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

#include "blockchain.h"

int BlockChain::numberOfBlocks{0};

int main()
{

  BlockChain chain;
  json j = {
    {"book", {
              {"name", "EDC"},
              {"code", 2020},
            }
    },
    {"student", "samrat neupane"},
    {"taken-date", "2022-06-15"},
    {"given-date", "2025-09-16"}
  };
  
  chain.addNode(to_string(j));
  chain.addNode("important info 2");

  chain.traverseBlockChain(chain);
  chain.checkChainConsistency(chain);
  chain.injectDataInBlock(chain, 2, "changed info");
  chain.traverseBlockChain(chain);
  chain.checkChainConsistency(chain);
  chain.recalulcateChain(chain);
  chain.checkChainConsistency(chain);

  return 0;
}
