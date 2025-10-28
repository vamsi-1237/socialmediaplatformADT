#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    if (data == 0) return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Build tree from level order traversal
Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == 0) return NULL;

    Node* nodes[n];

    for (int i = 0; i < n; i++) {
        nodes[i] = arr[i] ? createNode(arr[i]) : NULL;
    }

    for (int i = 0, j = 1; j < n; ++i) {
        if (!nodes[i]) continue;
        if (j < n) nodes[i]->left = nodes[j++];
        if (j < n) nodes[i]->right = nodes[j++];
    }

    return nodes[0];
}

int phones = 0;

// Return values:
// -1 → null
// 0 → needs phone
// 1 → covered
// 2 → has phone
int minPhones(Node* root) {
    if (!root) return -1;
    int left = minPhones(root->left);
    int right = minPhones(root->right);

    if (left == 0 || right == 0) {
        phones++;
        return 2;
    }
    if (left == 2 || right == 2) return 1;
    return 0;
}

// Generate first i primes
int* buildPrime(int i) {
    int *nums = (int*)malloc(sizeof(int) * i);
    int count = 0, N;

    if (i <= 6) N = 15;
    else N = ceil(i * (log(i) + log(log(i))));

    int *isPrime = (int*)malloc(sizeof(int) * (N + 1));
    for (int j = 0; j <= N; j++) isPrime[j] = 1;
    isPrime[0] = isPrime[1] = 0;

    for (int k = 2; k * k <= N; k++) {
        if (isPrime[k]) {
            for (int j = k * k; j <= N; j += k)
                isPrime[j] = 0;
        }
    }

    for (int j = 2; j <= N && count < i; j++) {
        if (isPrime[j])
            nums[count++] = j;
    }

    free(isPrime);
    return nums;
}

// Trie for XOR queries
typedef struct TrieNode {
    struct TrieNode* child[2];
    int count;
} TNode;

TNode* newNode() {
    TNode* node = (TNode*)malloc(sizeof(TNode));
    node->child[0] = node->child[1] = NULL;
    node->count = 0;
    return node;
}

void insert(TNode* root, int num) {
    for (int i = 20; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (!root->child[bit]) root->child[bit] = newNode();
        root = root->child[bit];
        root->count++;
    }
}

int query(TNode* root, int num, int k) {
    int res = 0;
    for (int i = 20; i >= 0; i--) {
        if (!root) break;
        int nbit = (num >> i) & 1;
        int kbit = (k >> i) & 1;

        if (kbit) {
            if (root->child[nbit])
                res += root->child[nbit]->count;
            root = root->child[1 - nbit];
        } else {
            root = root->child[nbit];
        }
    }
    return res;
}

long long countPairs(int arr[], int k, int n) {
    TNode* root = newNode();
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += query(root, arr[i], k);
        insert(root, arr[i]);
    }
    return res;
}

long long solve(int arr[], int L, int R, int n) {
    return countPairs(arr, R, n) - countPairs(arr, L - 1, n);
}

int main() {
    printf("Enter the size of level order traversal: ");
    int n;
    scanf("%d", &n);
    printf("\nEnter the level order traversal: ");
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    printf("\nEnter L and R values: ");
    int L, R;
    scanf("%d %d", &L, &R);

    Node* root = buildTree(arr, n);

    int res = minPhones(root);
    if (res == 0) phones++;
    printf("Minimum no of phones : %d\n", phones);
    printf("%d\n", phones);

    int *nums = buildPrime(phones);
    long long totalPairs = (1LL * phones * (phones - 1)) / 2;
    long long badPairs = solve(nums, L, R, phones);

    printf("Number of pairs: ");
    printf("%lld\n", totalPairs - badPairs);

    free(nums);
    return 0;
}

