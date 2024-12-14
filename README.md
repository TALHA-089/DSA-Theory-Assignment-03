# DSA-Theory-Assignment-03
This program implements Huffman Coding to compress and decompress strings.

This code implements a Huffman Coding algorithm to compress and decompress strings. Here’s a breakdown of the approach and logic:

1. Classes and Data Structures:**
- Node Class:
  - Represents a node in the frequency table. It holds a character, its frequency, and a pointer to the next node (for creating a linked list).
  
- FrequencyTable Class: 
  - Manages the creation and display of the frequency table, which tracks how often each character appears in the input string.
  - MakeTable creates this table, updating the frequency for each character in the string, and uses a linked list (Node class) to store the characters and their frequencies.

- HuffmanNode Struct: 
  - Represents a node in the Huffman Tree. It holds a character, frequency, and pointers to the left and right child nodes.

- PriorityQueue Class: 
  - Implements a min-heap (priority queue) to efficiently select nodes with the smallest frequencies while building the Huffman Tree.
  - It has methods for adding nodes (push), removing the smallest node (pop), and maintaining the heap property using heapifyUp and heapifyDown.

- HuffmanTree Class:
  - Manages the construction of the Huffman Tree and the generation of Huffman codes.
  - buildTree constructs the tree using nodes from the frequency table, combining the nodes with the smallest frequencies at each step.
  - generateCodes traverses the Huffman Tree and assigns binary codes (0 for left branches, 1 for right branches) to each character.
  - encode converts the input string into its encoded Huffman representation.
  - decode converts the encoded string back into the original string.

2. Main Menu and Input Validation:
- The program presents a menu to the user with two options: 
  - Option 1: Allows the user to input a string, generates the frequency table, constructs the Huffman tree, and displays the encoded and decoded results along with size and compression ratio.
  - Option 2: Exits the program.
  
- Input is validated using the isValidChoice function, which ensures that the user enters either 1 or 2 (numeric).

3. Huffman Coding Process:
- Step 1: Frequency Table Creation - The input string's character frequencies are counted and displayed in a frequency table.
- Step 2: Huffman Tree Construction - The priority queue is used to build the Huffman tree by repeatedly merging the nodes with the lowest frequencies.
- Step 3: Generate Huffman Codes - The tree is traversed to generate binary Huffman codes for each character.
- Step 4: Encoding - The input string is encoded using the generated Huffman codes.
- Step 5: Decoding - The encoded string is decoded back into the original string using the Huffman tree.
- Step 6: Size and Compression Analysis - The original and encoded sizes in bits are compared, and the compression ratio is displayed.

Key Features:
- Dynamic Memory Management:
  - The program uses dynamic memory allocation for linked list nodes (Node class) and Huffman tree nodes (HuffmanNode struct), which are properly deleted to avoid memory leaks.
  
- Efficiency:
  - A priority queue (min-heap) is used to ensure that the Huffman tree is built efficiently by always selecting the two nodes with the lowest frequencies for merging.
  
- Menu and User Interaction:
  - The program provides a user-friendly menu and input validation to guide the user through the process. The input string is encoded and decoded with clear steps, and the results are displayed in a readable format.

Overall Flow:
1. The user inputs a string.
2. The frequency table is built, and the Huffman tree is generated.
3. Huffman codes are displayed, and the string is encoded and decoded.
4. The program displays the results, including the compression ratio, and allows the user to repeat or exit.

This approach ensures that the program works efficiently, with clear steps and proper memory management, while providing a user-friendly interface for Huffman coding tasks.
