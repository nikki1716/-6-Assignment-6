#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Huffman tree node
struct Node {
    char data;
    unsigned freq;
    Node *left, *right;

    Node(char data, unsigned freq, Node* left = nullptr, Node* right = nullptr)
    : data(data), freq(freq), left(left), right(right) {}
};

// For comparison of two heap nodes (needed in min heap)
struct compare {
    bool operator()(Node* left, Node* right) {
        return (left->freq > right->freq);
    }
};

// Function to print Huffman codes from the root of the Huffman Tree
void printCodes(struct Node* root, string str) {
    if (!root) {
        return;
    }

    if (root->data != '$') {
        cout << root->data << ": " << str << "\n";
    }

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// Function to build the Huffman Tree and print codes
void HuffmanCodes(char data[], int freq[], int size) {
    struct Node *left, *right, *top;

    // Create a min heap & insert all characters of data[]
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new Node(data[i], freq[i]));
    }

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes frequencies. 
        // Make the two extracted nodes as left and right children of this new node. 
        // Add this node to the min heap '$' is a special value for internal nodes, not used
        top = new Node('$', left->freq + right->freq, left, right);

        minHeap.push(top);
    }

    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "");
}

// Driver program to test above functions
int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);

    return 0;
}
