# Matching Engine

A limit order book and matching engine implemented in C++. Built as a learning project to understand exchange-style order matching and market microstructure fundamentals.

## Features

- Resting bids and asks organized by price level, with **price-time priority** (FIFO within a price level)
- Full and partial order matching, including orders that consume multiple price levels in a single submission
- Order **cancellation** by ID, with automatic cleanup of empty price levels
- **Trade log** recording every executed match (price, quantity, buyer, seller)
- Trades execute at the **resting order's price**, not the incoming order's price (standard price-time priority behavior)

## How it works

- `Order` — a single order (uid, side, price, quantity)
- `OrderBook` — holds the bid/ask books and implements:
  - `add(order)` — insert a resting order into the book
  - `cancel(uid)` — remove a resting order by ID
  - `placeOrder(order)` — submit a new order; matches it against the opposite side of the book first, then rests any unfilled quantity
  - `printBook()` — print the current state of the book
- `Trade` — a record of one executed match

Prices are stored internally as scaled integers (not floats) to avoid floating-point precision issues when comparing or grouping by price level.

## Building

```
make
./matchingEngine
```

## Project structure

```
order.h        - Order class
trade.h        - Trade struct
orderbook.h    - OrderBook class (storage + matching logic)
main.cpp       - test / demo driver
Makefile
```

## Status

Core order book and matching engine are implemented and tested against hand-traced scenarios (partial fills, multi-level matching, cancellation, edge cases like empty books and self-crossing).

Not yet implemented:
- Synthetic order flow generator
- Market-making strategy / PnL tracking
- Performance optimization (this is a correctness-first implementation, not a low-latency one)