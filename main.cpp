#include <iostream>
#include "blockchain.h"
#include "transaction_data.h"

int main() {
    Blockchain block;

    TransactionData transactionData = {
        .amount = 1,
        .senderKey = "Sender",
        .receiverKey = "Receiver"
    };

    block
        .addBlock(transactionData)
        .printChain();
}
