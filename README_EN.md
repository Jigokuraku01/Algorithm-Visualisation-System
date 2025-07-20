# Algorithms Visualization

*Interactive, step-by-step visualizer for classic algorithms written in C++20 with SFML.*

[Русская версия ниже ⬇️]

---

## Table of Contents
1. [About the project](#about-the-project)  
2. [Key features](#key-features)  
3. [User workflow](#user-workflow)  
4. [Tech stack](#tech-stack)  
5. [Building & Running](#building-running)  
6. [Adding new algorithms](#adding-new-algorithms)  
7. [Supported Platforms](#supported-platforms)  
8. [Authors](#authors)

---

## About the project
**Algorithms Visualization** is an educational application that illustrates how classical algorithms—sorting routines and pathfinding—operate under the hood.  
Users can specify an algorithm and input data; the program then executes each algorithm **step-by-step**, visualizing comparisons, swaps, and more in real time using SFML.

## Key features
- **Interactive playback**: play/pause, step forward/back.  
- **Built-in algorithms**: BubbleSort, QuickSort, MergeSort.  
- **Visual highlights**: active elements (comparisons, swaps).  
- **Source-code viewer**: live line highlighting.  
- **Modular design**: integrate custom algorithms with minimal changes.  
- **FPS display**: runs at maximum speed by default and shows current FPS.  
- **Keyboard & buttons**: control via both keyboard shortcuts and on-screen buttons.

## User workflow
1. **Launch** the application:
   ```bash
   ./AlgorithmsVisualization -a bubblesort -d 5,2,9,1,7 --auto
   ```
2. **Available options**:
   - `-a` / `--algorithm`: algorithm identifier (e.g. `bubblesort`). **Required**  
   - `-d` / `--data`: comma-separated values or path to a file. Default = random data  
   - `--auto`: run continuously instead of manual stepping. Default = off  
   - `-w` / `--width`: window width (px). Default = 800  
   - `-h` / `--height`: window height (px). Default = 600  
   - `--show-fps`: display current frames per second in the window.

3. **In-window controls**:
   - **Space**: play/pause  
   - **→**: step forward  
   - **←**: step backward (if supported)  
   - **R**: reset to initial state  
   - **C**: toggle source-code view  
   - **Esc**: close application  
   - **Mouse wheel**: change playback speed  
   - **Mouse click**: display value or focus element  
   - On-screen buttons mirror all shortcut commands.

4. **Runtime menu** (press **M**): switch algorithms, load data from file, toggle theme, export GIF (experimental).

## Tech stack
- **C++20**  
- **SFML 2.5+** for graphics and window management  
- **CMake ≥3.18**  
- **GoogleTest** (optional testing)  

## Building & Running
```bash
git clone https://github.com/your-username/algovis.git
cd algovis
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
./build/AlgorithmsVisualization -a bubblesort --auto
```

## Adding new algorithms
1. Create a class in `src/Algorithms/` inheriting from `IVisualizedAlgorithm`.  
2. Implement logic and return drawable elements (`IAlgoObject[]`).  
3. Register the name in `AlgoHandler::createAlgorithm()` and add the CLI option in the parser.  
4. Rebuild – your algorithm is immediately available.  
> **Note:** Graph algorithms (BFS, DFS, Dijkstra) will be added in a future release.

## Supported Platforms
- **Linux** (Ubuntu/Debian)  
- **Windows** (make sure to copy SFML DLLs next to the executable)  
- **macOS** (install SFML via Homebrew or other package managers)

## Authors
- **Andrey Kashenin** – architecture, core modules  
- **Dmitry Kokorev** – design & code review  
- **Tigran Pogosyan** – UI & interaction design
