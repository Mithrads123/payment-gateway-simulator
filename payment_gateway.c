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
    int amount;
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
        printf("INSUFFICIENT_BALANCE\n");
        return;
    }

    users[uIndex].balance -= amount;
    merchants[mIndex].balance += amount;

    strcpy(transactions[txnCount].txnId, txnId);
    transactions[txnCount].amount = amount;
    txnCount++;

    printf("PAYMENT_SUCCESS\n");
}

// --------- Main ---------
int main() {

    addUser("U1", 1000);
    addMerchant("M1");

    makePayment("T1", "U1", "M1", 500);
    makePayment("T1", "U1", "M1", 500);

    return 0;
}

