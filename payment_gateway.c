#include <stdio.h>
#include <string.h>

#define MAX 100

// --------- Structures ---------
typedef struct {
    char userId[10];
    int balance;
} User;

typedef struct {
    char merchantId[10];
    int balance;
} Merchant;

typedef struct {
    char txnId[10];
    char userId[10];
    char merchantId[10];
    int amount;
    char status[20];      // SUCCESS / FAILED / REFUNDED
    int refunded;         // 0 = not refunded, 1 = refunded
} Transaction;



// --------- In-Memory Storage ---------
User users[MAX];
Merchant merchants[MAX];
Transaction transactions[MAX];

int userCount = 0;
int merchantCount = 0;
int txnCount = 0;

// --------- Utility Functions ---------
int findUser(char *userId) {
    for (int i = 0; i < userCount; i++)
        if (strcmp(users[i].userId, userId) == 0)
            return i;
    return -1;
}

int findMerchant(char *merchantId) {
    for (int i = 0; i < merchantCount; i++)
        if (strcmp(merchants[i].merchantId, merchantId) == 0)
            return i;
    return -1;
}

int txnExists(char *txnId) {
    for (int i = 0; i < txnCount; i++)
        if (strcmp(transactions[i].txnId, txnId) == 0)
            return 1;
    return 0;
}

// --------- Core Functions ---------
void addUser(char *userId, int balance) {
    strcpy(users[userCount].userId, userId);
    users[userCount].balance = balance;
    userCount++;
}

void addMerchant(char *merchantId) {
    strcpy(merchants[merchantCount].merchantId, merchantId);
    merchants[merchantCount].balance = 0;
    merchantCount++;
}
int findTransaction(char *txnId) {
    for (int i = 0; i < txnCount; i++) {
        if (strcmp(transactions[i].txnId, txnId) == 0)
            return i;
    }
    return -1;
}

void makePayment(char *txnId, char *userId, char *merchantId, int amount) {

    if (txnExists(txnId)) {
        printf("DUPLICATE_TRANSACTION\n");
        return;
    }

    int uIndex = findUser(userId);
    int mIndex = findMerchant(merchantId);

    if (uIndex == -1 || mIndex == -1) {
        printf("INVALID_USER_OR_MERCHANT\n");
        return;
    }

    if (users[uIndex].balance < amount) {
        strcpy(transactions[txnCount].txnId, txnId);
        strcpy(transactions[txnCount].userId, userId);
        strcpy(transactions[txnCount].merchantId, merchantId);
        transactions[txnCount].amount = amount;
        strcpy(transactions[txnCount].status, "FAILED");
        transactions[txnCount].refunded = 0;
        txnCount++;

printf("INSUFFICIENT_BALANCE\n");
return;

    }

    users[uIndex].balance -= amount;
    merchants[mIndex].balance += amount;
    
    strcpy(transactions[txnCount].txnId, txnId);
    strcpy(transactions[txnCount].userId, userId);
    strcpy(transactions[txnCount].merchantId, merchantId);
    transactions[txnCount].amount = amount;
    strcpy(transactions[txnCount].status, "SUCCESS");
    transactions[txnCount].refunded = 0;
    txnCount++;


    printf("PAYMENT_SUCCESS\n");
}

void printTransactionHistory() {
    printf("\n--- Transaction History ---\n");
    for (int i = 0; i < txnCount; i++) {
        printf("TxnID: %s | User: %s | Merchant: %s | Amount: %d | Status: %s\n",
               transactions[i].txnId,
               transactions[i].userId,
               transactions[i].merchantId,
               transactions[i].amount,
               transactions[i].status);
    }
}
void refundPayment(char *txnId) {

    int tIndex = findTransaction(txnId);

    if (tIndex == -1) {
        printf("TRANSACTION_NOT_FOUND\n");
        return;
    }

    if (strcmp(transactions[tIndex].status, "SUCCESS") != 0) {
        printf("REFUND_NOT_ALLOWED\n");
        return;
    }

    if (transactions[tIndex].refunded == 1) {
        printf("ALREADY_REFUNDED\n");
        return;
    }

    int uIndex = findUser(transactions[tIndex].userId);
    int mIndex = findMerchant(transactions[tIndex].merchantId);

    users[uIndex].balance += transactions[tIndex].amount;
    merchants[mIndex].balance -= transactions[tIndex].amount;

    strcpy(transactions[tIndex].status, "REFUNDED");
    transactions[tIndex].refunded = 1;

    printf("REFUND_SUCCESS\n");
}


// --------- Main ---------
int main() {

    addUser("U1", 1000);
    addMerchant("M1");

    makePayment("T1", "U1", "M1", 500);
    makePayment("T2", "U1", "M1", 700);

    refundPayment("T1");
    refundPayment("T1");   // double refund attempt
    refundPayment("T2");   // failed txn refund

    printTransactionHistory();

    return 0;
}


