# Royal Hunt (Vânătoarea Regală)

A modular C application developed for the **Algorithm Design** course at the Faculty of Automatic Control and Computer Science (POLITEHNICA Bucharest). The project simulates a multi-stage tournament selection, leaderboard ranking, and route generation system using fundamental data structures implemented from scratch.

## How to Build & Run

The project includes an automated testing script (`checker.sh`) that compiles the source files, runs all 7 stages, and validates the generated output files against the expected references.

1. **Grant execution permissions to the checker script (if needed):**

```bash
chmod +x checker.sh
```

2. **Run the automated test suite:**

```bash
./checker.sh
```

_(Alternatively, to compile manually using the `Makefile`, run `make` followed by `./main` or the target executable name)._

---

## Project Overview & Task Breakdown

The application processes candidate data across 7 sequential stages, where the output of each step feeds into the next:

- **Step 1 – Candidate Ingestion (Queues):**
  Reads raw candidate records from CSV files, maps social statuses (`Lord`, `Knight`, `Adventurer`) using enumerations, and stores the entries in a dynamically allocated FIFO queue.
- **Step 2 – Categorization & Sorting (Binary Search Trees):**
  Splits candidates into two separate Binary Search Trees based on their social status. Nodes are ordered by experience points (with age acting as a tie-breaker) and exported via in-order traversal.
- **Step 3 – Disqualification Filtering (List/Queue Manipulation):**
  Cross-references the sorted Lords list against a contestation file and removes disqualified participants using a two-pointer approach while preserving list integrity.
- **Step 4 – Participant Selection & Track Assignment (Binary Max-Heap):**
  Alternately selects the top 8 contenders from the two BSTs, assigns each participant a tournament track, and organizes them into a Max-Heap ordered descending by experience.
- **Step 5 – Dynamic Leaderboard Update (Heapify Operations):**
  Simulates track completion by adding newly gained experience to each contender and dynamically restoring the Max-Heap property step by step.
- **Step 6 – Final Standings (`qsort`):**
  Computes the total accumulated experience for all finalists and generates the final ranking using the standard C `qsort()` function with a custom comparator.
- **Step 7 – Tournament Route Generation (Directed Graphs & DFS):**
  Models the tournament map as a directed graph using sorted adjacency lists and performs a Depth-First Search (DFS) from all entry nodes (`in-degree == 0`) to terminal nodes (`out-degree == 0`) to enumerate all valid routes.

## Technologies & Concepts Used

- **Language:** C (Standard C99/C11)
- **Data Structures:** Queues, Binary Search Trees (BST), Binary Heaps, Directed Graphs
- **Key Practices:** Modular architecture (separate `.h`/`.c` files per stage), manual dynamic memory management (zero memory leaks), and CSV file parsing.
