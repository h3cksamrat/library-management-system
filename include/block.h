/**
 * @file block.h
 * @author Samrat Neupane (samratneupane215@gmail.com)
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>

using namespace std;

struct Block
{
    Block *next;        // address of next block
    Block *prev;        // address of previous block
    string actual_hash; // stores actual hash
    string prev_hash;   // stores hash for previous block
    string data;        // data for current block
};



