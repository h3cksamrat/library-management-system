/**
 * @file blockchain.h
 * @author Samrat Neupane (samratneupane215@gmail.com)
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include "block.h"
#include "sha256.h"
#include "uuid.h"

using namespace std;

class BlockChain
{
private:
    Block *previous;
    Block *head;

public:
    static int numberOfBlocks;

    BlockChain()
    {
        previous = nullptr;
        head = nullptr;
        cout << __FUNCTION__ << " Created" << endl;
    }

    string uuid()
    {
        UUID u;
        return u.uuid();
    }

    string generateHashSHA256(string toHash)
    {
        return sha256(toHash);
    }

    void addNode(string new_data)
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

            cout << "actual hash: " << new_block->actual_hash << endl;
            cout << "prev hash: " << previous->actual_hash << endl;
            new_block->prev = previous;
        }

        if (previous == nullptr)
        {
            head = new_block;
            previous = head;

            new_block->prev_hash = generateHashSHA256(uuid());
            new_block->data = new_data;
            new_block->actual_hash = generateHashSHA256(new_data);
            cout << "Genesis Data: " << new_block->data << endl;
        }

        cout << previous << " :: " << head << endl;

        numberOfBlocks++;
    }

    void traverseBlockChain(BlockChain &chain)
    {

        Block *actual_node = chain.head;
        int currentBlock = numberOfBlocks;

        while (actual_node->prev != nullptr)
        {
            cout << "block : " << currentBlock << endl;
            cout << "data  : " << actual_node->data << endl;
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

            string check_hash;
            string check_data;
            string check_hashFWD;
            string check_dataFWD;
            cout << __FUNCTION__ << "for block : " << currentBlock - 1 << endl;

            check_data = (actual_node->prev)->data;
            check_hash = (actual_node->prev)->prev_hash;

            check_dataFWD = actual_node->data;
            check_hashFWD = actual_node->prev_hash;

            cout << "DATA CHECKED : " << (actual_node->prev)->data << endl;

            if (actual_node->prev != nullptr)
            {
                string FWDCalculatedHash = generateHashSHA256(check_dataFWD + check_hashFWD);
                string injectedCalculatedHash = generateHashSHA256(check_data + check_hash);

                string storedHash = (actual_node->prev)->actual_hash;

                if (injectedCalculatedHash == check_hashFWD)
                {
                    cout << " HASH OK ==> Block Healthy !! " << endl;
                }
                if (injectedCalculatedHash != check_hashFWD)
                {
                    cout << " HASH WRONG ==> Block MANIPULATED !! " << endl;
                }
            }

            actual_node = actual_node->prev;
            currentBlock--;
        }
    }

    void recalulcateChain(BlockChain &chain)
    {

        Block *node = chain.head;

        vector<string> tempChainData;
        vector<Block *> ptr_node{node};
        vector<Block *> recal_node{numberOfBlocks};

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

            cout << " DATA PTR NODE  " << ii->data << endl;
            recal_node[numberOfBlocks - 1 - i] = ii;
            i++;
        }

        int j = 0;
        for (auto &ii : recal_node)
        {

            cout << " RECAL DATA   " << ii->data << endl;

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

        Block *node2 = chain.head;
        int currentBlock = numberOfBlocks;

        while (node2->prev != nullptr)
        {
            cout << endl;
            cout << "block : " << currentBlock << endl;
            cout << "data  : " << node2->data << endl;
            cout << "actual hash : " << node2->actual_hash << endl;
            cout << "NODE prev hash : " << node2->prev_hash << endl;
            cout << "prev hash : " << (node2->prev)->actual_hash << endl;
            node2 = node2->prev;
            currentBlock--;
        }
    }

    void injectDataInBlock(BlockChain &chain, int injectToBlock, string injectData)
    {

        Block *actual_node = chain.head;
        int currentBlock = numberOfBlocks;

        while (actual_node->prev != nullptr)
        {

            if (currentBlock == injectToBlock)
            {

                cout << "HASH__1 " << actual_node->actual_hash << endl;
                cout << "BEFORE INJECTION " << actual_node->data << endl;
                actual_node->data = injectData;
                actual_node->actual_hash = generateHashSHA256(injectData + actual_node->prev_hash);
                cout << "HASH__2 " << actual_node->actual_hash << endl;
            }

            actual_node = actual_node->prev;
            currentBlock--;
        }
    }
};
