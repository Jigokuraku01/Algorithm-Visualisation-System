# Algorithms Visualization

*Interactive step-by-step visualizer of classic sorting algorithms in C++20 using Qt.*

## Table of Contents

1. [About](#about)
2. [Key Features](#key-features)
3. [User Workflow](#user-workflow)
4. [Technology Stack](#technology-stack)
5. [Building and Running](#building-and-running)
6. [Supported Platforms](#supported-platforms)
7. [Authors](#authors)

---

## About

**Algorithms Visualization** is an educational application demonstrating how classic sorting algorithms work «under the hood». The user specifies the algorithm and input data; the application executes the algorithm **step by step**, visualizing comparisons, swaps, and other operations in real time using Qt.

## Key Features

- **Interactive playback**: play/pause.
- **Built-in algorithms**: BubbleSort, QuickSort, MergeSort.
- **Visual highlights**: active elements (comparisons, swaps).
- **Controls**: use the in-window buttons.

## User Workflow

1. **Launch** the application:

   ```bash
   ./AlgorithmsVisualization -a bubblesort -d 5,2,9,1,7 --auto
   ```

2. **Options**:

   - `-a` / `--algorithm`: algorithm identifier (e.g., `bubblesort`). **Required**
   - `-d` / `--data`: comma-separated values or path to a file. Default: random data
   - `--auto`: automatic mode (steps run without manual control). Default: off
   - `-w` / `--width`: window width (px). Default: 800
   - `-h` / `--height`: window height (px). Default: 600

3. **In-window Controls**
   In the bottom panel, there are buttons:

|            QStyle Icon           |         Action        | Key (Alternative) |
| :------------------------------: | :-------------------: | :---------------: |
| `SP_MediaPlay` / `SP_MediaPause` |      Play / Pause     |       Space       |
|     `SP_TitleBarCloseButton`     |    Exit application   |        Esc        |
|              `speed`             | Adjust playback speed |    Mouse wheel    |

> All keyboard keys mirror the corresponding buttons.

4. **Runtime Menu**
   Press **M** or the ☰ icon to:

- Change the algorithm
- Load data from a file
- Switch theme

## Technology Stack

- **C++20**
- **Qt ≥ 5** for graphics and window management
- **CMake ≥ 3.15**
- **Google Test**

## Building and Running

```bash
# 1. Clone the repository and navigate into it
git clone https://github.com/your-username/Algorithm-Visualisation-System.git
cd Algorithm-Visualisation-System

# 2. Create and enter the build directory
mkdir build
cd build

# 3. Configure the project for Release and specify Qt5
#    Replace /path/to/Qt5 with your actual path, e.g., /opt/Qt/5.15.2/gcc_64
cmake -DCMAKE_BUILD_TYPE=Release -DQT5_DIR=/path/to/Qt5/lib/cmake/Qt5 ../

# 4. Build using all available cores
cmake --build . --target build

# 5. Run the visualizer
./AlgorithmsVisualization -a bubblesort --auto
```

## Supported Platforms

- **Linux** (Ubuntu/Debian)

## Authors

- **Andrey Kashenin**
- **Dmitry Kokorev**
- **Tigran Pogosyan**
