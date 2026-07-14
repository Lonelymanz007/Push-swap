*This project has been created as part of the 42 curriculum by tphuwian.*

# Push_Swap

An efficient integer sorting algorithm project using two stacks and a limited set of instructions, developed as part of the 42 curriculum.

---

## Description
The goal of **Push_Swap** is to sort a stack of random integers in ascending order with the minimum number of operations. You are provided with two stacks: **Stack A** (which initially contains a random list of unique integers) and **Stack B** (which is initially empty). 

To accomplish the sorting, you have access to a set of predefined operations (swaps, pushes, and rotations). The efficiency of the sorting algorithm is evaluated based on the total operation count:
*   For **100 integers**, a full score requires less than **700 operations**.
*   For **500 integers**, a full score requires less than **5500 operations**.

This implementation utilizes a customized **K-Sort (Hourglass Sorting)** algorithm to meet and exceed these performance benchmarks.

---

## Instructions

### 1. Compilation
The project is built using a `Makefile`. To compile the source files and generate the `push_swap` binary, run:
```bash
make
```

### 2. Execution
To run the program and sort a list of integers, pass them as arguments:
```bash
./push_swap 4 67 3 87 23
```
You can also pass them as a single string (the parser will split them automatically):
```bash
./push_swap "4 67 3 87 23"
```
The program will output the sequence of instructions required to sort the stack.

### 3. Measuring Performance (Instruction Count)
To count how many operations your sorting generated:
```bash
./push_swap 4 67 3 87 23 | wc -l
```

### 4. Cleaning Build Files
*   To clean all compiled object files (`.o`):
    ```bash
    make clean
    ```
*   To clean object files and the executable binary:
    ```bash
    make fclean
    ```
*   To perform a fresh recompilation:
    ```bash
    make re
    ```

---

## Resources

### References
*   **Coordinate Compression:** A technique to simplify the range of input values by mapping them to their sorted rank indices (from `0` to `N-1`).
*   **Local Interactive Visualizer:** An offline pipeline visualizer developed to trace parsing steps, memory allocations, and stack movements.
    *   👉 **[Click to open local Visualizer](file:///Users/bookmacbook/Documents/VsCode/42_code/Rank2/push_swap/push_swap_visualizer.html)**

### AI Usage Description
In accordance with the 42 project requirements, AI (Antigravity AI Assistant) was utilized as a pair-programming partner during the development of this project:
1.  **Helper Tools & Visualizer:** AI assisted in designing the HTML and CSS layout of the [push_swap_visualizer.html](file:///Users/bookmacbook/Documents/VsCode/42_code/Rank2/push_swap/push_swap_visualizer.html) file to display the stack states in real-time.
2.  **Explanations & Documentation:** AI was used to draft conceptual explanations of the doubly linked list connections and compile this documentation.
3.  **No Direct Core Algorithm Injection:** The core implementation of the C sorting functions, error checking, parsing, and stack manipulations were written and debugged by the student.

---

## Technical Choices & Algorithms

### 1. Data Structures

#### Doubly Linked List (`t_node`)
A node represents a single number inside the stack. Each node contains:
*   `value`: The original integer value.
*   `index`: The compressed index (from `0` to `N-1`).
*   `prev`: Pointer to the node above (towards the top of the stack).
*   `next`: Pointer to the node below (towards the bottom of the stack).

```text
                  [ Node Structure ]
       ┌──────────────────────────────────────────┐
 ◀──── ─ prev (holds upper node)     value/index  ─ next (holds lower node) ──▶
       └──────────────────────────────────────────┘
```
*Choice Rationale:* The doubly linked list allows us to perform forward and backward lookups in $O(1)$ time complexity. This is crucial for reverse rotations (`rra`/`rrb`), where the bottom-most node needs to shift to the top, and the second-to-last node must become the new bottom immediately.

#### 2-Anchor Stack Manager (`t_stack`)
The stack manager tracks the state of the stack using:
*   `top`: Points to the top-most node.
*   `bottom`: Points to the bottom-most node.
*   `size`: Represents the number of elements in the stack.

*Choice Rationale:* Storing both `top` and `bottom` pointers avoids traversing the list to locate the tail, ensuring all push and rotate operations run in $O(1)$ time.

---

### 2. Push Swap Operations
*   **Swap (`s`):** `sa` / `sb` / `ss` - Swaps the top two elements of a stack.
*   **Push (`p`):** `pa` / `pb` - Pushes the top element from one stack to another.
*   **Rotate (`r`):** `ra` / `rb` / `rr` - Shifts all elements up by 1 (top becomes bottom).
*   **Reverse Rotate (`rr`):** `rra` / `rrb` / `rrr` - Shifts all elements down by 1 (bottom becomes top).

---

### 3. K-Sort Algorithm (Hourglass Sorting)

The sorting for larger datasets is achieved through a two-phase K-Sort algorithm:

#### Phase 1: Hourglass Formation (A to B)
We push elements from Stack A to Stack B using a sliding window of size `k`:
*   Initialize `i = 0`.
*   For each element at the top of Stack A:
    1.  If `index <= i`, push to B (`pb`) and increment `i`.
    2.  If `index <= i + k`, push to B (`pb`), rotate B (`rb`) to send it to the bottom, and increment `i`.
    3.  Otherwise, rotate A (`ra`) to search for other elements within the sliding window.
*   *Outcome:* Stack B is populated in an **hourglass shape** (smaller values in the middle, larger values concentrated at both the top and bottom of Stack B).

#### Phase 2: Sorted Retrieval (B to A)
Once Stack A is empty, we retrieve elements from Stack B back to Stack A in descending order:
*   Find the position (`pos`) of the maximum index (`max`) in Stack B.
*   If `pos` is in the upper half of Stack B (`pos <= size / 2`), perform `rb` rotations to bring it to the top.
*   If `pos` is in the lower half of Stack B (`pos > size / 2`), perform `rrb` reverse rotations to bring it to the top.
*   Once the target is at the top (`pos == 0`), push it back to Stack A (`pa`) and decrement `max`.
*   *Outcome:* Stack A is reconstructed from largest to smallest, resulting in a sorted stack.

#### Why K = 15 and 35?
*   **Too small (e.g., K = 2):** Phase 1 requires excessive `ra` rotations to find matching elements, increasing operation counts.
*   **Too large (e.g., K = 150):** The hourglass profile in B becomes disorganized. Phase 2 requires extensive `rb`/`rrb` operations to locate the maximum values.
*   **Optimal Balances:**
    *   For **$N \le 100$**, $k = 15$ yields ~700 operations.
    *   For **$N = 500$**, $k = 35$ yields ~4800 operations.