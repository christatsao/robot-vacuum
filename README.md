# 🧹 Robot Vacuum Cleaner – Pathfinding & Grid Sweeping (C++)

This project simulates a robot vacuum that navigates a 20×20 grid to clean garbage (`.`) while avoiding obstacles (`*`). It uses **Breadth-First Search (BFS)** to find the shortest path to each piece of garbage and reports a score based on cleaning efficiency.

---

## 🔍 Overview

- Randomly generated room:
  - `.` = Garbage
  - `*` = Obstacle
  - `'V'` = Robot's current position
- Robot starts at the top-left `(0, 0)`
- Moves to nearest garbage one cell at a time
- Avoids obstacles and cleans all reachable garbage

---

## 🎯 Features

- ✅ Random grid with obstacles and garbage
- ✅ Movement validation (no diagonal or large jumps)
- ✅ Adjacency graph of the grid
- ✅ Shortest path using BFS
- ✅ Repeats cleaning until garbage is gone
- ✅ Scoring system (accuracy and efficiency)

---

## 🧠 How It Works

### `initGrid()`
Initializes the grid with:
- 25% chance of obstacle
- 75% garbage

### `create_adj_matrix()`
Builds a graph of legal moves (non-obstacle, within 1 cell).

### `shortest_path()`
Finds the shortest path to a garbage cell using **BFS**.

### `sweepGrid()`
Main logic:
- While garbage exists:
  - Find shortest path to closest garbage
  - Move vacuum along that path
  - Clean and repeat

### `printScore()`
Evaluates cleaning quality:
- Penalty for missed garbage
- Penalty for removing obstacles
- Reports move efficiency and final score out of 100

---

## 📸 Example Output

