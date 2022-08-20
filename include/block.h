/**
 * @file block.h
 * @author Samrat Neupane (samratneupane215@gmail.com)
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <iostream>

struct Block
{
    Block *next;        // address of next block
    Block *prev;        // address of previous block
    std::string actual_hash; // stores actual hash
    std::string prev_hash;   // stores hash for previous block
    std::string data;        // data for current block
};



