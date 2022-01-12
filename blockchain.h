#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include "block.h"
#include "transaction_data.h"

class Blockchain {
    auto createFirstBlock() {
        std::hash<std::string> dataHash;
        std::hash<std::string> prevHash;

        TransactionData transactionData = {
            .amount = 0,
            .senderKey = "None",
            .receiverKey = "None"
        };

        auto toHash = std::to_string(transactionData.amount)
                            + transactionData.receiverKey
                            + transactionData.senderKey;

        auto hash = dataHash(toHash) ^ (prevHash(std::to_string(0)) << 1);

        return Block(0, transactionData, hash);
    }

public:
    std::vector<Block> chain;
    
    Blockchain() {
        chain.push_back(createFirstBlock());
    }

    auto isChainValid() {
        auto flag = true;
        
        for_each_n(chain.begin(), chain.size(), [&](auto &item) {
            if (!item.isHashValid()) {
                flag = false;
            } else if (chain.size() > 1 && (item.getPreviousHash() != (&item)[-1].getHash())) {
                flag = false;
            }
        });

        return flag;
    }

    auto getLatestBlock() { return chain.back(); }

    auto addBlock(TransactionData data) {
        chain.push_back(Block(chain.size() - 1, data, getLatestBlock().getHash()));
        return *this;
    }

    auto printChain() {
        for_each_n(chain.begin(), chain.size(), [](auto &item) {
            std::cout<<std::boolalpha<<item.isHashValid()<<std::endl;
            std::cout<<item.getTransactionData().amount<<std::endl;
            std::cout<<item.getTransactionData().senderKey<<std::endl;
            std::cout<<item.getTransactionData().receiverKey<<std::endl;
            std::cout<<item.getHash()<<std::endl;
            std::cout<<item.getPreviousHash()<<std::endl<<std::endl;
        });
    }
};

#endif
