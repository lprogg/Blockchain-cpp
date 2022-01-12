#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include "transaction_data.h"

class Block {
    int index;
    size_t blockHash;
    size_t previousHash;
    TransactionData transactionData;

    auto generateHash() {
        std::hash<std::string> dataHash;
        std::hash<std::string> prevHash;

        auto toHash = std::to_string(transactionData.amount)
                            + transactionData.receiverKey
                            + transactionData.senderKey;

        return dataHash(toHash) ^ (prevHash(std::to_string(previousHash)) << 1);
    }

public:
    Block(int idx, TransactionData data, size_t prevHash) {
        index = idx;
        transactionData = data;
        previousHash = prevHash;
        blockHash = generateHash();
    }

    auto getHash() { return blockHash; }
    auto getTransactionData() { return transactionData; }
    auto getPreviousHash() { return previousHash; }
    auto isHashValid() { return generateHash() == blockHash; }
};

#endif
