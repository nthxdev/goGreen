Here is the completely revised and professionally structured `README.md`. It incorporates your development roadmap, highlights the beginner-friendly architecture, and maintains a high-density, technical aesthetic.

# GitHub Contribution Graph Customizer
A Node.js toolset designed to manipulate Git objects and temporally spoof commit history, allowing you to draw pixel art or generate dense contribution graphs on your GitHub profile. 
**Educational Focus:** The core `index.js` engine is explicitly designed for beginners and developers who want to master Git internals. The codebase is exhaustively commented, breaking down exactly how the V8 engine, asynchronous recursion, and the Git binary interact under the hood to bypass the system clock.

---
### ⚠️ Disclaimer
**This repository is strictly for educational purposes.** It demonstrates vulnerability in relying on unverified temporal data and visual graph metrics. Do not use this tool to deceive employers, falsify professional history, or manipulate hiring algorithms.

**Credits:** Original concept by [Fenrir on YouTube](https://www.youtube.com/@Fenrir26) / [Original - goGreen Repository](https://github.com/fenrir2608/goGreen).

---
### 🗺️ Feature Roadmap
**Currently Implemented:**
- [x] **Core Injection Engine:** Asynchronous Node.js script (`index.js`) for recursive commit batching.
- [x] **Dual Execution Modes:** Support for both Stochastic (random noise) and Deterministic (pixel art) matrix generation.
- [x] **Gradient Multipliers:** Native support for mapping GitHub's 4-tier color intensity via commit stacking.
- [x] **Visual Matrix Generator:** A standalone interactive Web GUI to easily paint shapes and instantly compile the required JavaScript coordinate array.
**Planned Future Features:**
- [ ] **Full E2E GUI Integration:** Execute the entire workflow (repo creation, commit generation, remote push) directly from a local browser interface without touching the CLI.
- [ ] **Automated Achievements Hub:** A GUI module to systematically trigger and unlock GitHub profile badges (Quick Draw, Pull Shark, Pair Extraordinaire, etc.).
- [ ] **Live Profile Sync:** Fetch and render the user's live GitHub profile matrix in the GUI for real-time visualization before pushing the spoofed payload.

---
### 🛠️ Setup Instructions
**1. Initialize the Node environment and enable ES6 modules:**
```bash
npm init -y
npm pkg set type="module"
```
**2. Install core dependencies:**
```bash
npm install jsonfile moment simple-git random
```
**3. Bind your GitHub Identity:**
Ensure your local repository directory is configured to use the primary email explicitly tied to your GitHub account. Without this, the remote server will reject the graph mapping.
```bash
git config user.email "your-github-email@example.com"
```
---
### 📦 Internal Architecture & Dependencies
* **`jsonfile`**: Forces a persistent file diff (tree change) by overwriting a local dummy file, satisfying Git's strict requirement to instantiate a new commit object.
* **`moment`**: Calculates the precise historical ISO 8601 timestamps required to target specific X/Y graph coordinates.
* **`simple-git`**: Interfaces directly with the native Git binary to execute local staging, spoofed commits via the `--date` flag, and batched remote pushes.
* **`random`**: Synthesizes X/Y coordinates for stochastic (random) graph distribution.

---
### ⚙️ Engine Configuration (`index.js`)
You control the engine's behavior by modifying the global constants at the top of `index.js`.
**Execution Modes:**
* `const MODE = 'ART';` Iterates over a specific coordinate array to draw deterministic pixel art.
* `const MODE = 'RANDOM';` Generates randomized green squares based on the `TOTAL_COMMITS` count.

**Temporal & Density Parameters:**
* **`TARGET_YEARS_BACK`**: The temporal anchor. Determines how far back the generated timeline starts (e.g., `1` for the previous year).
* **`TOTAL_COMMITS`**: Injection density for `RANDOM` mode. Defines the total number of commits generated.
* **Coordinate Mapping (`x`, `y`)**:
* `x`: X-Axis (Weeks). Valid range is `0` to `54`.
* `y`: Y-Axis (Days). Valid range is `0` (Sunday) to `6` (Saturday).

---
### 🚀 Execution
Run the injection engine through the V8 runtime. The script optimizes network latency by batching all local commits recursively and executing a single, compressed network push upon completion.
```bash
node index.js
```