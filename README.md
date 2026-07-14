# Push_Swap

This project is part of the 42 curriculum. It is an algorithmic project that requires sorting data on a stack, with a limited set of instructions, using the lowest possible number of actions.

---



## Table of Contents
1. [Data Structure Theory](#1-data-structure-theory)
   - [Doubly Linked List (`t_node`)](#doubly-linked-list-t_node)
   - [2-Head Stack Manager (`t_stack`)](#2-head-stack-manager-t_stack)
2. [Push Swap Operations](#2-push-swap-operations)
   - [Swap (`s`)](#swap-s)
   - [Push (`p`)](#push-p)
   - [Rotate (`r`)](#rotate-r)
   - [Reverse Rotate (`rr`)](#reverse-rotate-rr)
3. [K-Sort Algorithm (Hourglass Sorting)](#3-k-sort-algorithm-hourglass-sorting)
   - [Phase 1: Hourglass Formation (A to B)](#phase-1-hourglass-formation-a-to-b)
   - [Phase 2: Sorted Retrieval (B to A)](#phase-2-sorted-retrieval-b-to-a)
   - [Why K = 15 and 35?](#why-k--15-and-35)

---

## 1. Data Structure Theory

### Doubly Linked List (`t_node`)
A node is the basic block of the stack. In a **Doubly Linked List**, each node contains its data and two pointers:
*   `value`: The actual integer value.
*   `index`: The relative sorted index of the value (from `0` to `N-1`), resolved via coordinate compression.
*   `prev`: Pointer to the node above (towards the top of the stack).
*   `next`: Pointer to the node below (towards the bottom of the stack).

```text
                  [ Node Structure ]
       ┌──────────────────────────────────────────┐
 ◀──── ─ prev (holds upper node)     value/index  ─ next (holds lower node) ──▶
       └──────────────────────────────────────────┘
```

#### Why a Doubly Linked List?
Using a doubly linked list allows us to navigate the stack both upwards and downwards in $O(1)$ time complexity. This is crucial for operations like `rra` / `rrb` (reverse rotating), where we need to detach the bottom-most element and find the new bottom node (`bottom->prev`) instantly without looping through the entire stack.

### 2-Head Stack Manager (`t_stack`)
Instead of just keeping a single head pointer, the stack manager `t_stack` stores two anchor pointers:
*   `top`: Points to the top-most node.
*   `bottom`: Points to the bottom-most node.
*   `size`: Keeps track of the current number of elements.

#### Why two anchors?
Push Swap operations frequently target both ends of the stack (swapping at the `top`, pushing from `top`, and rotating to/from the `bottom`). Keeping constant references to both `top` and `bottom` ensures we can execute rotations and pushes in $O(1)$ time complexity rather than traversing the list.

---

## 2. Push Swap Operations

The program manipulates the stacks using the following standard operations:

### Swap (`s`)
*   **Operations:** `sa` (Stack A), `sb` (Stack B), `ss` (Both Stacks)
*   **Logic:** Swaps the first two elements at the top of the stack. If there is only one or no elements, it does nothing.
*   **Visual:**
    ```text
    Before Swap: Top -> [ A ] -> [ B ] -> [ C ] -> Bottom
    After Swap:  Top -> [ B ] -> [ A ] -> [ C ] -> Bottom
    ```

### Push (`p`)
*   **Operations:** `pa` (Push to A), `pb` (Push to B)
*   **Logic:** Takes the first element at the top of one stack and puts it at the top of the other stack. If the source stack is empty, it does nothing.
*   **Visual (pb):**
    ```text
    Stack A: Top -> [ A ] -> [ B ]              Stack B: Top -> [ C ]
    Result:  Stack A: Top -> [ B ]              Stack B: Top -> [ A ] -> [ C ]
    ```

### Rotate (`r`)
*   **Operations:** `ra` (Rotate A), `rb` (Rotate B), `rr` (Both Stacks)
*   **Logic:** Shifts up all elements of the stack by 1. The first element becomes the last one.
*   **Visual:**
    ```text
    Before Rotate: Top -> [ A ] -> [ B ] -> [ C ] -> Bottom
    After Rotate:  Top -> [ B ] -> [ C ] -> [ A ] -> Bottom
    ```

### Reverse Rotate (`rr`)
*   **Operations:** `rra` (Reverse Rotate A), `rrb` (Reverse Rotate B), `rrr` (Both Stacks)
*   **Logic:** Shifts down all elements of the stack by 1. The last element becomes the first one.
*   **Visual:**
    ```text
    Before Rev-Rotate: Top -> [ A ] -> [ B ] -> [ C ] -> Bottom
    After Rev-Rotate:  Top -> [ C ] -> [ A ] -> [ B ] -> Bottom
    ```

---

## 3. K-Sort Algorithm (Hourglass Sorting)

The K-sort algorithm is a highly optimized algorithm designed to sort large sets of numbers (100 to 500+) with a minimal instruction count. It is divided into two main phases:

### Phase 1: Hourglass Formation (A to B)
In this phase, we push elements from Stack A to Stack B based on a sliding window of size `k`.
*   We initialize `i = 0`.
*   For each element at the top of Stack A:
    1.  If `index <= i`, we push it to B (`pb`), and increment `i`.
    2.  If `index <= i + k`, we push it to B (`pb`) and rotate B (`rb`) to send it to the bottom, then increment `i`.
    3.  Otherwise, we rotate A (`ra`) to look for other elements within the window boundary.
*   **Result:** Stack B ends up sorted in an **Hourglass shape** (smaller indices are concentrated in the middle of Stack B, while larger indices are pushed towards both the top and bottom of Stack B).

### Phase 2: Sorted Retrieval (B to A)
Once Stack A is empty, we retrieve elements from Stack B back to Stack A in descending order.
*   We look for the maximum index `max` remaining in Stack B.
*   We find its position (`pos`) in Stack B:
    *   If the target is in the upper half (`pos <= size / 2`), we run `rb` to rotate it up to the top.
    *   If the target is in the lower half (`pos > size / 2`), we run `rrb` to reverse rotate it up to the top.
*   Once the target is at `pos == 0` (top of Stack B), we push it to Stack A (`pa`), and decrement `max`.
*   **Result:** Stack A is rebuilt from largest to smallest, resulting in a perfectly sorted stack.

### Why K = 15 and 35?
The window size `k` acts as a sliding boundary filter. If `k` is chosen poorly, the total operations count will skyrocket:
*   **If K is too small:** Phase 1 requires too many `ra` rotations to find matching elements, increasing A's rotation overhead.
*   **If K is too large:** The hourglass shape in B becomes distorted and unorganized. In Phase 2, retrieving elements requires massive numbers of `rb` / `rrb` searches.
*   **Optimal Values:** 
    *   For **$N \le 100$**, $k = 15$ is optimal, yielding around ~700 operations (well below the 700 full-score limit).
    *   For **$N = 500$**, $k = 35$ is optimal, yielding around ~4800 operations (well below the 5500 full-score limit).

---


## สารบัญ
1. [ทฤษฎีโครงสร้างข้อมูล](#1-ทฤษฎีโครงสร้างข้อมูล)
   - [รายการเชื่อมโยงสองทิศทาง (`t_node`)](#รายการเชื่อมโยงสองทิศทาง-t_node)
   - [ตัวจัดการสแต็กแบบ 2 หัวท้าย (`t_stack`)](#ตัวจัดการสแต็กแบบ-2-หัวท้าย-t_stack)
2. [คำสั่งควบคุมสแต็ก (Push Swap Operations)](#2-คำสั่งควบคุมสแต็ก-push-swap-operations)
   - [Swap (การสลับคู่บน - `s`)](#swap-การสลับคู่บน---s)
   - [Push (การผลักย้ายสแต็ก - `p`)](#push-การผลักย้ายสแต็ก---p)
   - [Rotate (การหมุนขึ้น - `r`)](#rotate-การหมุนขึ้น---r)
   - [Reverse Rotate (การหมุนลง - `rr`)](#reverse-rotate-การหมุนลง---rr)
3. [อัลกอริทึม K-Sort (การจัดเรียงรูปนาฬิกาทราย)](#3-อัลกอริทึม-k-sort-การจัดเรียงรูปนาฬิกาทราย)
   - [Phase 1: การขึ้นรูปนาฬิกาทราย (A ไป B)](#phase-1-การขึ้นรูปนาฬิกาทราย-a-ไป-b)
   - [Phase 2: การดึงข้อมูลจัดเรียงกลับ (B ไป A)](#phase-2-การดึงข้อมูลจัดเรียงกลับ-b-ไป-a)
   - [ทำไมต้องเป็น K = 15 และ 35?](#ทำไมต้องเป็น-k--15-และ-35)

---

## 1. ทฤษฎีโครงสร้างข้อมูล

### รายการเชื่อมโยงสองทิศทาง (`t_node`)
Node คือหน่วยเก็บข้อมูลย่อยพื้นฐานที่สุดในขบวนสแต็ก ในรูปแบบ **Doubly Linked List** แต่ละ Node จะมีพอยเตอร์สำหรับจับยึดโบกี้ข้างเคียง 2 ตัว:
*   `value`: ค่าตัวเลขจำนวนเต็มจริงที่รับเข้ามา
*   `index`: อันดับที่จัดเรียงแล้ว (ค่าตั้งแต่ `0` ถึง `N-1`) ซึ่งได้มาจากการบีบอัดพิกัด (Coordinate Compression)
*   `prev`: พอยเตอร์ชี้ไปหา Node ด้านบน (ทิศทางเข้าหายอดสแต็ก)
*   `next`: พอยเตอร์ชี้ไปหา Node ด้านล่าง (ทิศทางเข้าหาก้นสแต็ก)

```text
                  [ โครงสร้างของ Node ]
       ┌──────────────────────────────────────────┐
 ◀──── ─ prev (ชี้ไปหาตัวด้านบน)   value/index (ค่า)  ─ next (ชี้ไปหาตัวด้านล่าง) ──▶
       └──────────────────────────────────────────┘
```

#### ทำไมต้องเป็น Doubly Linked List?
การมีพอยเตอร์ชี้สองทิศทางช่วยให้เราสามารถเข้าถึงข้อมูลทั้งทิศทางขึ้นและลงได้ในเวลา $O(1)$ ซึ่งมีความสำคัญอย่างยิ่งสำหรับคำสั่งหมุนย้อนกลับอย่าง `rra` / `rrb` ที่เราต้องตัดพอยเตอร์ตัวท้ายสุดและเลื่อนป้ายก้นสแต็กขึ้นมาที่ตัวก่อนหน้า (`bottom->prev`) ได้ทันทีโดยไม่ต้องเขียนลูปวิ่งไล่หาตั้งแต่หัวแถว

### ตัวจัดการสแต็กแบบ 2 หัวท้าย (`t_stack`)
แทนที่จะมีตัวชี้หัวแถวเพียงจุดเดียว ตัวควบคุมสแต็ก `t_stack` จะถือพอยเตอร์สมอไว้ 2 ด้านพร้อมกันคือ:
*   `top`: พอยเตอร์ชี้โบกี้บนสุด
*   `bottom`: พอยเตอร์ชี้โบกี้ล่างสุด
*   `size`: บันทึกจำนวนโบกี้ทั้งหมด ณ ปัจจุบัน

#### ทำไมต้องคุมทั้งหัวและท้าย?
เนื่องจากคำสั่งใน Push Swap ส่วนใหญ่ต้องย้ายของจากบนสุด (`top`) และเอาของไปแปะหรือดึงขึ้นมาจากล่างสุด (`bottom`) เสมอ การล็อกตำแหน่ง `top` และ `bottom` แช่ไว้แบบถาวรทำให้เราสั่งปรับเปลี่ยนลิงก์เชื่อมต่อพอยเตอร์ได้ทันทีในเวลาคงที่ $O(1)$ โดยไม่ต้องเขียนลูปเดินสแกนหาตำแหน่งปลายแถว

---

## 2. คำสั่งควบคุมสแต็ก (Push Swap Operations)

โปรแกรมควบคุมการจัดเรียงตัวเลขผ่านชุดคำสั่งมาตรฐานดังต่อไปนี้:

### Swap (การสลับคู่บน - `s`)
*   **คำสั่ง:** `sa` (สแต็ก A), `sb` (สแต็ก B), `ss` (ทั้งคู่)
*   **ตรรกะ:** สลับตำแหน่งข้อมูลของคู่บนสุด 2 ตัว หากสแต็กมีขนาดน้อยกว่า 2 จะไม่ทำอะไร
*   **ภาพจำลอง:**
    ```text
    ก่อนสลับ: Top -> [ A ] -> [ B ] -> [ C ] -> Bottom
    หลังสลับ: Top -> [ B ] -> [ A ] -> [ C ] -> Bottom
    ```

### Push (การผลักย้ายสแต็ก - `p`)
*   **คำสั่ง:** `pa` (ย้ายไป A), `pb` (ย้ายไป B)
*   **ตรรกะ:** ดึงโบกี้บนสุดของสแต็กต้นทาง ไปวางปักไว้บนสุดของสแต็กปลายทาง หากต้นทางว่างจะไม่มีอะไรเกิดขึ้น
*   **ภาพจำลอง (pb):**
    ```text
    สแต็ก A: Top -> [ A ] -> [ B ]              สแต็ก B: Top -> [ C ]
    ผลลัพธ์:  สแต็ก A: Top -> [ B ]              สแต็ก B: Top -> [ A ] -> [ C ]
    ```

### Rotate (การหมุนขึ้น - `r`)
*   **คำสั่ง:** `ra` (หมุน A), `rb` (หมุน B), `rr` (หมุนทั้งคู่)
*   **ตรรกะ:** ขยับข้อมูลทุกตัวขึ้นด้านบน 1 สเต็ป โดยตัวบนสุดจะหลุดลงไปเชื่อมต่อที่ก้นสแต็กแทน
*   **ภาพจำลอง:**
    ```text
    ก่อนหมุนขึ้น: Top -> [ A ] -> [ B ] -> [ C ] -> Bottom
    หลังหมุนขึ้น: Top -> [ B ] -> [ C ] -> [ A ] -> Bottom
    ```

### Reverse Rotate (การหมุนลง - `rr`)
*   **คำสั่ง:** `rra` (หมุนลง A), `rrb` (หมุนลง B), `rrr` (หมุนลงทั้งคู่)
*   **ตรรกะ:** ขยับข้อมูลทุกตัวลงด้านล่าง 1 สเต็ป โดยตัวล่างสุดจะหลุดวนกลับขึ้นมาปักเป็นหัวแถวบนสุดแทน
*   **ภาพจำลอง:**
    ```text
    ก่อนหมุนลง: Top -> [ A ] -> [ B ] -> [ C ] -> Bottom
    หลังหมุนลง: Top -> [ C ] -> [ A ] -> [ B ] -> Bottom
    ```

---

## 3. อัลกอริทึม K-Sort (การจัดเรียงรูปนาฬิกาทราย)

K-Sort คืออัลกอริทึมที่มีประสิทธิภาพสูงในการกรองเพื่อคัดแยกข้อมูลจำนวนมาก (100 ถึง 500+ ตัว) ให้มีทิศทางกึ่งเรียงลำดับล่วงหน้าก่อนทำการดึงกลับ แบ่งการทำงานออกเป็น 2 ช่วงหลัก:

### Phase 1: การขึ้นรูปนาฬิกาทราย (A ไป B)
ทำการย้ายตัวเลขจากสแต็ก A ไปสแต็ก B โดยใช้เกณฑ์ขอบเขตหน้าต่างสไลด์ (Sliding Window) ขนาดกว้าง `k` 
*   กำหนดตัวแปรเปรียบเทียบ `i = 0`
*   ตรวจสอบข้อมูลตัวบนสุดของสแต็ก A:
    1.  ถ้า `index <= i` ให้ผลักไป B ทันที (`pb`) และเพิ่มค่า `i` ทีละหนึ่ง
    2.  ถ้า `index <= i + k` ให้ผลักไป B (`pb`) แล้วสั่งหมุน B (`rb`) ส่งมันไปกองไว้ก้นสแต็ก จากนั้นเพิ่มค่า `i`
    3.  หากไม่ใช่ทั้งคู่ ให้หมุนสแต็ก A หลบหลีกเพื่อค้นหาตัวที่อยู่ในขอบเขตถัดไป (`ra`)
*   **ผลลัพธ์:** สแต็ก B จะมีรูปร่างที่เรียงตัวเป็น **นาฬิกาทราย (Hourglass)** คือตัวเลขดัชนีค่าน้อยจะจมอยู่ตรงกลางแถว ส่วนตัวเลขค่าใหญ่จะปูดออกไปกองที่หัวแถวและก้นแถวของสแต็ก B

### Phase 2: การดึงข้อมูลจัดเรียงกลับ (B ไป A)
เมื่อย้ายข้อมูลไปสแต็ก B จนหมดแล้ว เราจะเริ่มทำการดึงกลับมาเรียงที่สแต็ก A จากค่ามากที่สุดลงไปหาค่าน้อยที่สุด
*   ค้นหาตำแหน่งดัชนีค่าสูงสุดเป้าหมาย `max` ที่ยังเหลืออยู่ในสแต็ก B
*   ตรวจสอบว่าตัวเป้าหมายนั้นอยู่พิกัดใด (`pos`) ในสแต็ก B:
    *   หากอยู่ครึ่งบนของสแต็ก (`pos <= size / 2`): สั่งหมุนขยับขึ้น `rb` ไปเรื่อยๆ จนถึงบนสุด
    *   หากอยู่ครึ่งล่างของสแต็ก (`pos > size / 2`): สั่งหมุนย้อนกลับ `rrb` เพื่อเลื่อนดึงจากก้นสแต็กขึ้นมาบนสุด
*   เมื่อเป้าหมายมาถึงบนสุด (`pos == 0`) ให้สั่งดันกลับไปปักที่สแต็ก A ทันที (`pa`) และปรับเป้าหมายถัดไป `max--`
*   **ผลลัพธ์:** สแต็ก A จะถูกสร้างเรียงลำดับจากค่าที่สูงที่สุดไล่ลงไปหาค่าต่ำสุด ทำให้สแต็ก A จัดเรียงเสร็จสมบูรณ์เรียบร้อย

### ทำไมต้องเป็น K = 15 และ 35?
ค่าความกว้างหน้าต่าง `k` คือจุดสมดุล หากเลือกค่าอื่นที่ไม่เหมาะสม จำนวนคำสั่งคำนวณรวมจะเพิ่มสูงขึ้นมาก:
*   **หาก K แคบเกินไป (เช่น k = 2):** ใน Phase 1 สแต็ก A จะต้องทนหมุน `ra` ค้นหาข้อมูลเปล่าบ่อยครั้ง ส่งผลให้คำสั่ง ra พุ่งทะยาน
*   **หาก K กว้างเกินไป (เช่น k = 150 ในกรณี 500 ตัว):** รูปร่างของนาฬิกาทรายใน B จะกระจัดกระจายไม่เป็นระเบียบ ทำให้ใน Phase 2 ตัวเป้าหมาย `max` มักจมอยู่ลึกตรงกลางแถว ต้องใช้คำสั่ง `rb`/`rrb` เพื่อดึงขึ้นมาเป็นจำนวนมหาศาล
*   **จุดสมดุลที่ดีที่สุด:**
    *   สำหรับ **$N \le 100$**: ค่า $k = 15$ จะรันคำสั่งเฉลี่ยเพียง ~700 ครั้ง (ผ่านเกณฑ์คะแนนเต็ม)
    *   สำหรับ **$N = 500$**: ค่า $k = 35$ จะรันคำสั่งเฉลี่ยเพียง ~4800 ครั้ง (ผ่านเกณฑ์คะแนนเต็ม 5,500 ครั้ง)