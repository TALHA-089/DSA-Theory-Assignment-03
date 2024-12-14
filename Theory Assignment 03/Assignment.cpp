/*
This program implements Huffman Coding to compress and decompress strings. 
It works by creating a frequency table of characters in the input string, 
then constructing a Huffman Tree using a priority queue (min-heap). 
Each character is assigned a unique binary code based on the tree structure. 
The string is then encoded using these codes and can be decoded back to 
the original string. The program also calculates the compression ratio 
by comparing the original and encoded string sizes in bits. A menu-based 
approach allows the user to interact with the program, validate choices, 
and perform encoding/decoding tasks. Memory is dynamically managed and 
the linked list and tree are properly cleaned up after use.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

// Node class represents a character and its frequency in the linked list
class Node{
    private:
    int freq;  // Frequency of the character
    char Character;  // Character represented by this node
    Node * next;  // Pointer to the next node in the list

    public:
    // Constructor to initialize a node with character and frequency
    Node(char C, int f) {
        this->Character = C;
        this->freq = f;
        next = nullptr;
    }

    // Getter and setter methods for frequency and character
    Node* getNext() { return this->next; }
    void setNext(Node* next) { this->next = next; }
    int getFreq() { return this->freq; }
    char getChar() { return this->Character; }
    void setCharacter(char C) { this->Character = C; }
    void setfreq(int f) { this->freq = f; }
};

// FrequencyTable class manages the creation and display of the frequency table
class FrequencyTable{
    private:
    Node * head;  // Head of the linked list storing characters and their frequencies
    string huffmanString;  // The input string for which we create the frequency table

    public:
    // Constructor initializes head to nullptr
    FrequencyTable() { head = nullptr; }

    // Destructor to free memory by deleting the nodes in the linked list
    ~FrequencyTable() {
        Node *p = head;
        Node *q;
        while(p != nullptr) {
            q = p->getNext();
            delete p;
            p = q;
        }
        head = nullptr;
    }

    // Setters and getters for the Huffman string
    void sethuffmanString(string s) { this->huffmanString = s; }
    string gethuffmanString() { return this->huffmanString; }

    // Create a frequency table by counting occurrences of each character
    void MakeTable() {
        if (isEmpty()) {
            if (huffmanString.empty()) {
                cout << "\nError! Huffman String is Empty!";
                return;
            }

            // Loop through the input string and update the frequency table
            for (int i = 0; i < huffmanString.length(); i++) {
                char Character = huffmanString[i];
                Node* temp = head;
                bool found = false;

                while (temp != nullptr) {
                    if (temp->getChar() == Character) {
                        temp->setfreq(temp->getFreq() + 1);
                        found = true;
                        break;
                    }
                    temp = temp->getNext();
                }

                // If character is not found, create a new node and add it to the list
                if (!found) {
                    Node* newNode = new Node(Character, 1);
                    if (head == nullptr) {
                        head = newNode;
                    } else {
                        Node* current = head;
                        while (current->getNext() != nullptr) {
                            current = current->getNext();
                        }
                        current->setNext(newNode);
                    }
                }
            }
        } else {
            cout << "\nTable is already populated!";
        }
    }

    // Check if the table is empty
    bool isEmpty() { return (head == nullptr); }

    // Display the frequency table
    void DisplayTable() {
        if (head == nullptr) {
            cout << "\nFrequency table is empty.\n";
            return;
        }

        Node* p = head;
        int TotalFreq = 0;

        cout << left << setw(15) << "Character" << setw(15) << "Frequency" << endl;
        cout << string(30, '-') << endl;

        // Loop through the linked list and display each character and its frequency
        while (p != nullptr) {
            cout << left << setw(15) << p->getChar() << setw(15) << p->getFreq() << endl;
            TotalFreq += p->getFreq();
            p = p->getNext();
        }

        cout << string(30, '-') << endl;
        cout << left << setw(15) << "Total" << setw(15) << TotalFreq << endl;
    }

    // Getter for the head node of the list
    Node* getHead() { return this->head; }
};

// HuffmanNode structure represents each node in the Huffman tree
struct HuffmanNode {
    char Character;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    // Constructor initializes a Huffman node with character and frequency
    HuffmanNode(char C, int f) {
        Character = C;
        freq = f;
        left = right = nullptr;
    }
};

// PriorityQueue class manages the min-heap structure for building the Huffman tree
class PriorityQueue {
public:
    vector<HuffmanNode*> queue;  // Vector to hold the Huffman nodes (min-heap)

private:
    // Helper function to maintain heap property when moving nodes upwards
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (queue[index]->freq < queue[parent]->freq) {
                swap(queue[index], queue[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Helper function to maintain heap property when moving nodes downwards
    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < queue.size() && queue[left]->freq < queue[smallest]->freq) {
            smallest = left;
        }
        if (right < queue.size() && queue[right]->freq < queue[smallest]->freq) {
            smallest = right;
        }
        if (smallest != index) {
            swap(queue[index], queue[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Push a new node into the queue and maintain the heap property
    void push(HuffmanNode* node) {
        queue.push_back(node);
        heapifyUp(queue.size() - 1);
    }

    // Pop the node with the smallest frequency from the queue
    HuffmanNode* pop() {
        if (queue.empty()) return nullptr;
        HuffmanNode* root = queue[0];
        queue[0] = queue.back();
        queue.pop_back();
        heapifyDown(0);
        return root;
    }

    // Check if the queue is empty
    bool isEmpty() { return queue.empty(); }
};

// HuffmanTree class is responsible for building the Huffman tree and generating codes
class HuffmanTree {
private:
    HuffmanNode* root;  // Root node of the Huffman tree
    string encodedString;  // Encoded string after Huffman encoding

    // Helper function to build Huffman codes for each character
    void buildCodes(HuffmanNode* node, string code, unordered_map<char, string>& codes) {
        if (!node) return;

        if (!node->left && !node->right) {
            codes[node->Character] = code;
        }

        buildCodes(node->left, code + "0", codes);
        buildCodes(node->right, code + "1", codes);
    }

    // Encode the input string using the generated Huffman codes
    void encodeString(string input, unordered_map<char, string>& codes) {
        for (char c : input) {
            encodedString += codes[c];
        }
    }

public:
    // Constructor initializes root to nullptr
    HuffmanTree() { root = nullptr; }

    // Build the Huffman tree from the frequency table
    void buildTree(FrequencyTable& table) {
        PriorityQueue pq;
        Node* p = table.getHead();

        // Push each character and its frequency to the priority queue
        while (p != nullptr) {
            pq.push(new HuffmanNode(p->getChar(), p->getFreq()));
            p = p->getNext();
        }

        // Merge nodes with the lowest frequencies to create the tree
        while (pq.queue.size() > 1) {
            HuffmanNode* left = pq.pop();
            HuffmanNode* right = pq.pop();

            HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
            merged->left = left;
            merged->right = right;

            pq.push(merged);
        }

        root = pq.pop();  // The remaining node is the root of the tree
    }

    // Generate Huffman codes for each character
    unordered_map<char, string> generateCodes() {
        unordered_map<char, string> codes;
        buildCodes(root, "", codes);
        return codes;
    }

    // Encode the input string using Huffman codes
    string encode(string input, unordered_map<char, string>& codes) {
        encodedString.clear();
        encodeString(input, codes);
        return encodedString;
    }

    // Decode the encoded string back to the original string
    string decode(string encoded) {
        string decoded;
        HuffmanNode* current = root;

        // Traverse the tree to decode the string
        for (char bit : encoded) {
            current = (bit == '0') ? current->left : current->right;

            // When we reach a leaf node, append the character to the decoded string
            if (!current->left && !current->right) {
                decoded += current->Character;
                current = root;
            }
        }

        return decoded;
    }
};

// Display the main menu for user interaction
void MainMenu(){
    cout << "\n\n--------------Welcome to Huffman Coding --------------\n\n";
    cout << "1. Enter String and Encode/Decode\n";
    cout << "2. Exit\n";
    cout << "\nEnter your choice: ";
}

// Validate if the user's choice is either 1 or 2
bool isValidChoice(const string& choice) {
    stringstream ss(choice);
    int num;
    ss >> num;
    return !ss.fail() && ss.eof() && (num == 1 || num == 2);
}

// Main function to execute the Huffman coding process
int main() {
    int choice;
    string myString;
    string encoded, decoded;
    unordered_map<char, string> codes;
    FrequencyTable table;
    HuffmanTree hTree;
    string inputChoice;

    do {
        MainMenu();  // Display the menu
        getline(cin, inputChoice);  // Get user input for menu choice

        if (isValidChoice(inputChoice)) {
            stringstream(inputChoice) >> choice;
            switch(choice) {
                case 1:
                    cout << "\nEnter a String: ";
                    getline(cin, myString);

                    // Step 1: Create a Frequency Table
                    cout << "\nStep 1: Create a Frequency Table\n\n";
                    table.sethuffmanString(myString);
                    table.MakeTable();
                    cout << "\n------------ Frequency Table ------------\n\n";
                    table.DisplayTable();

                    // Step 2: Build the Huffman Tree and Generate Huffman Codes
                    cout << "\nStep 2: Build a Huffman Tree and Generate Huffman Codes\n\n";
                    hTree.buildTree(table);
                    codes = hTree.generateCodes();
                    cout << "\n------------ Huffman Codes ------------\n\n";
                    cout << left << setw(15) << "Character" << setw(20) << "Huffman Code" << endl;
                    cout << string(35, '-') << endl;

                    for (const pair<char, string>& p : codes) {
                        cout << left << setw(15) << p.first << setw(20) << p.second << endl;
                    }
                    cout << string(35, '-') << endl;

                    // Step 3: Encode the Input String
                    cout << "\nStep 3: Encode the Input String\n\n";
                    encoded = hTree.encode(myString, codes);
                    cout << "\nEncoded String: " << encoded << endl;

                    // Step 4: Decode the Encoded String and Match it with the Original String
                    cout << "\nStep 4: Decode the Encoded String and Match it with the Original String\n\n";
                    decoded = hTree.decode(encoded);
                    cout << "\nDecoded String: " << decoded << endl;

                    if (decoded == myString) {
                        cout << "\nThe decoded string matches the original!" << endl;
                    } else {
                        cout << "\nError: Decoded string does not match the original." << endl;
                    }

                    // Step 5: Analyze and Compare the Sizes
                    cout << "\nStep 5: Analyze and Compare the Sizes\n\n";
                    cout << "\nOriginal Size (in bits): " << myString.length() * 8 << endl;
                    cout << "Encoded Size (in bits): " << encoded.length() << endl;
                    cout << "Compression Ratio: " << (float)encoded.length() / (myString.length() * 8) * 100 << "%\n";
                    break;

                case 2:
                    cout << "\nExiting program. Goodbye!" << endl;
                    break;

                default:
                    cout << "\nInvalid choice. Please enter a valid option." << endl;
            }
        } else {
            cout << "\nInvalid input. Please enter a valid numeric choice (1 or 2)." << endl;
        }

    } while (choice != 2);
    cout << endl << endl;
    return 0;
}
