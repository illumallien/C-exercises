#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define HASH_SIZE 10

// Struct for storing student data
typedef struct {
    int id;
    char name[50];
    int score;
} Student;

// Node for Huffman tree
typedef struct Node {
    char data;
    int freq;
    struct Node *left, *right;
} Node;

// Struct for Min-Heap
typedef struct MinHeap {
    int size;
    int capacity;
    Node **array;
} MinHeap;

// Function prototypes
void radixSort(Student arr[], int n);
int hashFunction(int id);
void huffmanEncoding(Student students[], int n);
Node *createNode(char data, int freq);
MinHeap *createMinHeap(int capacity);
void minHeapify(MinHeap *minHeap, int idx);
Node *extractMin(MinHeap *minHeap);
void insertMinHeap(MinHeap *minHeap, Node *node);
MinHeap *buildMinHeap(char data[], int freq[], int size);
Node *buildHuffmanTree(char data[], int freq[], int size);
void printCodes(Node *root, int arr[], int top);

// Radix Sort function
void radixSort(Student arr[], int n) {
    int maxScore = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].score > maxScore) {
            maxScore = arr[i].score;
        }
    }

    int exp = 1;
    Student *output = (Student *)malloc(n * sizeof(Student));
    while (maxScore / exp > 0) {
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(arr[i].score / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i].score / exp) % 10] - 1] = arr[i];
            count[(arr[i].score / exp) % 10]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        exp *= 10;
    }

    free(output);
}

// Hash function
int hashFunction(int id) {
    return id % HASH_SIZE;
}

// Huffman encoding
Node *createNode(char data, int freq) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node **)malloc(minHeap->capacity * sizeof(Node *));
    return minHeap;
}

void minHeapify(MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        Node *temp = minHeap->array[smallest];
        minHeap->array[smallest] = minHeap->array[idx];
        minHeap->array[idx] = temp;
        minHeapify(minHeap, smallest);
    }
}

Node *extractMin(MinHeap *minHeap) {
    Node *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap *minHeap, Node *node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

MinHeap *buildMinHeap(char data[], int freq[], int size) {
    MinHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 2) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

Node *buildHuffmanTree(char data[], int freq[], int size) {
    Node *left, *right, *top;
    MinHeap *minHeap = buildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(Node *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

void huffmanEncoding(Student students[], int n) {
    int freq[256] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < strlen(students[i].name); j++) {
            freq[(unsigned char)students[i].name[j]]++;
        }
    }

    char uniqueChars[256];
    int charFreq[256];
    int uniqueCount = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            uniqueChars[uniqueCount] = i;
            charFreq[uniqueCount] = freq[i];
            uniqueCount++;
        }
    }

    Node *root = buildHuffmanTree(uniqueChars, charFreq, uniqueCount);
    int arr[MAX], top = 0;

    printf("\nHuffman Encoding:\n");
    printCodes(root, arr, top);
}

int main() {
    FILE *file = fopen("veri.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    Student students[MAX];
    int n = 0;

    while (fscanf(file, "%d %s %d", &students[n].id, students[n].name, &students[n].score) != EOF) {
        n++;
    }

    fclose(file);

    // Radix Sort
    printf("\nRadix Sort Result:\n");
    radixSort(students, n);
    for (int i = 0; i < n; i++) {
        printf("%d %s %d\n", students[i].id, students[i].name, students[i].score);
    }

    // Hash Table
    printf("\nHash Table:\n");
    Student *hashTable[HASH_SIZE][MAX] = {NULL};
    int hashCount[HASH_SIZE] = {0};

    for (int i = 0; i < n; i++) {
        int index = hashFunction(students[i].id);
        hashTable[index][hashCount[index]++] = &students[i];
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Index %d: ", i);
        for (int j = 0; j < hashCount[i]; j++) {
            printf("%d %s %d", hashTable[i][j]->id, hashTable[i][j]->name, hashTable[i][j]->score);
            if (j < hashCount[i] - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    }

    // Huffman Encoding
    huffmanEncoding(students, n);

    return 0;
}
