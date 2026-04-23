# Course Planner (CS 300)

A C++ course management application designed for academic advisors. The program parses CSV data into a Binary Search Tree (BST) to allow for efficient alphanumeric sorting and course lookups for their prerequisites information.

---

### Input Format
The program prompts the user for a `.csv` file where each line represents a single course using the following structure:
`CourseCode,CourseName,Prerequisite1,Prerequisite2,...`

**Example:**<br>
CSCI100,Introduction to Programming<br>
CSCI200,Data Structures,CSCI100<br>
CSCI300,Advanced Algorithms,CSCI200,MATH201

---

## Part 1: Project Reflection

**1. What was the problem you were solving?**
Academic advisors often need to search through specific courses and go over their prerequisites. To make their lives easier,
I built a tool for them to manage and search through courses quickly and easily. The program takes in a CSV, filled with course codes, course names and prerequisites and allows them to view a sorted list of the courses and look up specific ones for information about prerequisites.

**2. How did you approach the problem?**
After considering different data structures, I went with a **Binary Search Tree (BST)**. It’s the most efficient for our task, as it keeps the data sorted by default. A more detailed explanation can be viewed below inside Part 2.

**3. How did you overcome roadblocks?**
One of the biggest roadblocks was deciding on how to organize the different elements in the program such as the Binary Search Tree and the program itself. I intended to break the BST apart into a class and header file and import it into the program but we were tasked with making sure everything fits inside a single .cpp file. I overcame this by adding BST related methods inside the BST class as private methods, and implementing public 'wrapper' methods. These provided a clean way for the menu to trigger tree operations while maintaining encapsulation, allowing me to keep the entire program logic organized inside a single .cpp file.

**4. How has this expanded your approach to software design?**
It strengthened in my mind the idea that for any non-trivial task, we should always plan ahead of time before jumping into coding. Such as writing the pseudo code or taking the time to decide on the right data structures to use to keep the program efficient and scalable.

**5. How has this evolved the way you write maintainable code?**
I focused on keeping the BST logic separate from the menu code. It makes the file easier to read and means I could technically reuse that tree structure for a different project without having to rewrite everything.

---

## Part 2: Data Structures Runtime & Memory Analysis

We were tasked with deciding on the best data structure for this project, choosing between a **Vector**, a **Hash Table**, and a **Binary Search Tree (BST)**. Each structure was evaluated based on how efficiently it could load course data from a file, search for a specific course, and print all courses in sorted order.

The core file-loading logic is the same across all three implementations — the only difference is the final insertion line. Here is the shared pseudocode for reference:

    Iterate line by line until we reach the end of the file:          // n iterations
        If amount of parameters in line is less than 2:
            Print error message
            return

        Declare newCourse as Course
        newCourse.code = line[0]
        newCourse.name = line[1]

        If line has more than 2 parameters:
            For each remaining word (p prerequisites):
                newCourse.prerequisites.add(word)

        courses.add(newCourse)   // <-- this line's cost differs per data structure

> **Note on `p` (prerequisites):** The variable `p` represents the number of prerequisites per course. Since `p` is typically very small (1–3), we treat it as a constant and it does not affect the overall Big-O analysis.

The analysis for each data structure follows below.

---

### Vector

**Total Worst Case Runtime:** O(n²)

**Explanation:**
Since a vector is a dynamically growing array, adding an element typically takes O(1). However, when the size surpasses the capacity, resizing the array and copying all existing elements takes O(n). Since we are adding n courses, this means we have a line with a worst case cost of O(n), nested inside a loop which runs n times. Therefore the worst case scenario for loading all courses is O(n²).

**Advantages:**
A vector provides random access, meaning we can directly check specific indexes for values with O(1) time efficiency, and it has an average insert time of O(1). It is true that insertion is amortized — in the case that the insertion causes the vector size to exceed the capacity threshold, it will need to allocate memory for a bigger array and copy over the elements, which takes O(n) — but in the average case, inserting is constant time.

Also, all elements are stored in a single unbroken block of memory (contiguous memory), which makes iterating through it quicker because CPUs can cache sequential data efficiently.

**Disadvantages:**
While random access provides O(1) lookup at a specific index, if we want to delete from a specific index we would need to shift all subsequent elements, resulting in an O(n) operation. Lookup of a specific value is also O(n) because we would need to iterate the entire array to check for a match. Lastly, vectors have memory overhead: when we allocate memory for a vector, we allocate more than we actually need and resize as needed. While having less overhead per element compared to a linked list, a vector reserves a chunk of memory for future elements, thus taking up more memory than strictly needed.

---

### Hash Table

**Total Worst Case Runtime:** O(n)

**Explanation:**
The logic is identical to the vector implementation except for the final insertion line. In a hash table, insertion typically takes O(1). Technically, if the hash function is poor and all insertions land in the same bucket, the structure essentially behaves as a linked list with a worst case of O(n) per insertion. However, we generally do not consider that degenerate case when analyzing the typical efficiency of a hash table.

Since we loop n times and each insertion is O(1), the total worst case time cost is O(n).

**Advantages:**
A hash table gives us extremely fast lookups and insertions. With a good hash function, we can find a specific course or insert a new one in an average time of O(1). It does this by taking a key — like our course code — and running it through a hash function which translates that key into a specific array index, letting us jump right to the data without searching through the rest of the elements.

Technically, it isn't truly O(1), because we may need to iterate a linked list at that index of the array (a bucket). However, assuming the hash function distributes keys well, those lists will be very small, so we treat their length as a constant, which gives us O(1) for the average case.

**Disadvantages:**
Hash tables don't maintain any sort of order. If we want to print our course list alphabetically, we can't simply iterate through it — we would have to pull everything out into an array and sort it, costing additional time and memory. Collisions can also degrade performance: when two different keys hash to the same index, the elements get chained together. A bad hash function can effectively turn the table into a linked list, degrading all O(1) operations to O(n).

The hash table also has additional overhead: memory for the buckets array itself, and additional structural data per element (node pointers for chaining).

---

### Binary Search Tree

**Total Worst Case Runtime:** O(n log n)

**Explanation:**
Again, the logic is identical to the hash table implementation except for the insertion line. For a BST, insertion time depends on whether the tree is balanced. If balanced, insertion takes O(log n). However, if the tree does not self-balance and elements are inserted in sorted order, the tree degenerates into a single long branch — essentially a linked list — where insertion takes O(n), making the total O(n²).

I assumed our course list is not pre-sorted and is inserted in a random order, therefore insertion takes O(log n) per element, which when nested in a loop that runs n times results in O(n log n) overall.

**Advantages:**
A BST keeps all data sorted by default as we add it. The tree automatically places smaller keys to the left and larger keys to the right, so we can print our entire course list in alphanumeric order just by performing an in-order traversal in O(n) time — no separate sorting function needed. Assuming the tree is balanced, searching for a course and inserting a new one both take O(log n) on average.

**Disadvantages:**
Every node must allocate memory for both a left and right child pointer, creating more memory overhead per element. While lookup is generally faster than a vector at O(log n), a standard BST doesn't self-balance. If we load courses that are already sorted, the tree will keep adding nodes to one side and become a straight line, degrading O(log n) search and insert times to O(n).

---

### Recommendation

I recommend using a **Binary Search Tree**.

Our data structure needs to primarily serve two purposes:
1. **Search** for a specific course and print its info (title, prerequisites).
2. **Print** a complete list of all courses in sorted order.

A BST provides a significant advantage for both operations. Assuming courses aren't pre-sorted, choosing a BST allows us to print all courses by simply performing an in-order traversal — O(n) time with no extra memory.

A lookup for a specific course takes only O(log n).

It is true that the initial load time is slower due to O(log n) insertions compared to O(1) for a vector or hash table, but after that initial load we enjoy the benefits of having our data sorted, which is a significant advantage for our use case.

**BST vs. Vector:** The BST wins on both fronts. Lookup is O(log n) vs. O(n), and printing in sorted order is O(n) vs. O(n log n) (since the vector would require sorting first).

**BST vs. Hash Table:** While a hash table offers O(1) average lookup, the BST has a major advantage when printing all elements in order. A hash table would require copying elements into an array and sorting — O(n log n) time plus additional memory — while the BST needs only an O(n) in-order traversal.

Essentially, we sacrifice a bit of extra overhead per element and a longer initial load time in exchange for faster operations afterward. I believe these trade-offs are worth it, so my recommendation is a **Binary Search Tree**.