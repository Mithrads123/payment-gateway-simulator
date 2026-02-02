# Payment Gateway Simulator (C)

A simplified, in-memory payment gateway system implemented in C, inspired by real-world fintech payment flows.

This project focuses on **core backend logic**, **failure handling**, and **transaction safety**, similar to systems used in high-scale payment platforms.

---

## 🔹 Features Implemented

- User and merchant account management
- Payment processing with balance validation
- Idempotent transaction handling (duplicate prevention)
- Transaction history logging
- Refund system with double-refund protection
- Failure tracking for audit and reconciliation

---

## 🔹 Design Decisions

- **In-memory storage** using arrays and structs to simulate database behavior
- **Idempotency** ensured using transaction ID checks
- **State management** using transaction status transitions:
  - SUCCESS → REFUNDED
  - FAILED (non-refundable)
- Explicit refund flags to prevent double refunds

---

## 🔹 Core Concepts Demonstrated

- Payment lifecycle management
- Failure handling and audit trails
- State transitions in distributed systems
- Defensive programming for financial systems
- Separation of responsibilities in procedural C

---

## 🔹 Sample Output

PAYMENT_SUCCESS
INSUFFICIENT_BALANCE
REFUND_SUCCESS
ALREADY_REFUNDED
REFUND_NOT_ALLOWED

--- Transaction History ---
TxnID: T1 | User: U1 | Merchant: M1 | Amount: 500 | Status: REFUNDED
TxnID: T2 | User: U1 | Merchant: M1 | Amount: 700 | Status: FAILED

Possible Extensions

Concurrency-safe transaction handling

Persistent storage integration

Batch reconciliation reports

API-style interface

Why This Project

This project was built to understand how real payment systems handle money safely, rather than focusing on UI or frameworks.
