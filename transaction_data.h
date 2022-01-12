#ifndef TRANSACTION_DATA_H
#define TRANSACTION_DATA_H

#include <iostream>

struct TransactionData {
    size_t amount;
    std::string senderKey;
    std::string receiverKey;
};

#endif
