#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// AVL düğüm yapısı
typedef struct AVLNode {
    char author;
    char isbn[14];
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

// BST düğüm yapısı
typedef struct BSTNode {
    char author;
    char isbn[14];
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// AVL ve BST düğüm yüksekliği
int height(AVLNode *N) {
    return (N == NULL) ? 0 : N->height;
}

// Maksimum değer bulma
int max(int a, int b) {
    return (a > b) ? a : b;
}

// AVL düğüm oluşturma
AVLNode* newAVLNode(char author, char *isbn) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->author = author;
    strcpy(node->isbn, isbn);
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// BST düğüm oluşturma
BSTNode* newBSTNode(char author, char *isbn) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->author = author;
    strcpy(node->isbn, isbn);
    node->left = node->right = NULL;
    return node;
}

// Sağ dönüş (AVL)
AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Sol dönüş (AVL)
AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Denge faktörü (AVL)
int getBalance(AVLNode *N) {
    return (N == NULL) ? 0 : height(N->left) - height(N->right);
}

// AVL ağacında minimum değeri bulma
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// BST ağacında minimum değeri bulma
BSTNode* BSTminValueNode(BSTNode* node) {
    BSTNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// AVL ekleme işlemi
AVLNode* insertAVL(AVLNode* node, char author, char *isbn) {
    if (node == NULL)
        return newAVLNode(author, isbn);

    if (author < node->author || (author == node->author && strcmp(isbn, node->isbn) < 0))
        node->left = insertAVL(node->left, author, isbn);
    else if (author > node->author || (author == node->author && strcmp(isbn, node->isbn) > 0))
        node->right = insertAVL(node->right, author, isbn);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Sol-Sol
    if (balance > 1 && author < node->left->author)
        return rightRotate(node);

    // Sağ-Sağ
    if (balance < -1 && author > node->right->author)
        return leftRotate(node);

    // Sol-Sağ
    if (balance > 1 && author > node->left->author) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Sağ-Sol
    if (balance < -1 && author < node->right->author) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// BST ekleme işlemi
BSTNode* insertBST(BSTNode* node, char author, char *isbn) {
    if (node == NULL)
        return newBSTNode(author, isbn);

    if (author < node->author || (author == node->author && strcmp(isbn, node->isbn) < 0))
        node->left = insertBST(node->left, author, isbn);
    else if (author > node->author || (author == node->author && strcmp(isbn, node->isbn) > 0))
        node->right = insertBST(node->right, author, isbn);

    return node;
}

// AVL silme işlemi
AVLNode* deleteAVL(AVLNode* root, char author, char *isbn) {
    if (root == NULL)
        return root;

    if (author < root->author || (author == root->author && strcmp(isbn, root->isbn) < 0))
        root->left = deleteAVL(root->left, author, isbn);
    else if (author > root->author || (author == root->author && strcmp(isbn, root->isbn) > 0))
        root->right = deleteAVL(root->right, author, isbn);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->author = temp->author;
            strcpy(root->isbn, temp->isbn);
            root->right = deleteAVL(root->right, temp->author, temp->isbn);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Sol-Sol
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Sol-Sağ
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Sağ-Sağ
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Sağ-Sol
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// BST silme işlemi
BSTNode* deleteBST(BSTNode* root, char author, char *isbn) {
    if (root == NULL)
        return root;

    if (author < root->author || (author == root->author && strcmp(isbn, root->isbn) < 0))
        root->left = deleteBST(root->left, author, isbn);
    else if (author > root->author || (author == root->author && strcmp(isbn, root->isbn) > 0))
        root->right = deleteBST(root->right, author, isbn);
    else {
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }

        BSTNode* temp = BSTminValueNode(root->right);
        root->author = temp->author;
        strcpy(root->isbn, temp->isbn);
        root->right = deleteBST(root->right, temp->author, temp->isbn);
    }

    return root;
}

// Post-order yazdırma (AVL)
void postOrderAVL(AVLNode *root) {
    if (root != NULL) {
        postOrderAVL(root->left);
        postOrderAVL(root->right);
        printf("(%c, %s) ", root->author, root->isbn);
    }
}

// Post-order yazdırma (BST)
void postOrderBST(BSTNode *root) {
    if (root != NULL) {
        postOrderBST(root->left);
        postOrderBST(root->right);
        printf("(%c, %s) ", root->author, root->isbn);
    }
}

// Test işlemleri için örnek fonksiyon
void testInsertionsAndDeletions() {
    AVLNode *avlRoot = NULL;
    BSTNode *bstRoot = NULL;
    char *isbns[] = {"2", "1", "3", "4", "7", "6", "5"};
    char authors[] = {'a', 'a', 'a', 'b', 'c', 'b', 'a'};

    for (int i = 0; i < 7; i++) {
        avlRoot = insertAVL(avlRoot, authors[i], isbns[i]);
        bstRoot = insertBST(bstRoot, authors[i], isbns[i]);
    }

    printf("AVL Agac (Post-order) Eklemeden Sonra: ");
    postOrderAVL(avlRoot);
    printf("\nBST Agac (Post-order) Eklemeden Sonra: ");
    postOrderBST(bstRoot);

    printf("\n\n(b, 4) dugumunu siliyoruz...\n");

    avlRoot = deleteAVL(avlRoot, 'b', "4");
    bstRoot = deleteBST(bstRoot, 'b', "4");

    printf("AVL Agac (Post-order) Silmeden Sonra: ");
    postOrderAVL(avlRoot);
    printf("\nBST Agac (Post-order) Silmeden Sonra: ");
    postOrderBST(bstRoot);
    printf("\n");
}

AVLNode* searchAVL(AVLNode* root, char author, char *isbn) {
    if (root == NULL || (root->author == author && strcmp(root->isbn, isbn) == 0))
        return root;

    if (author < root->author || (author == root->author && strcmp(isbn, root->isbn) < 0))
        return searchAVL(root->left, author, isbn);

    return searchAVL(root->right, author, isbn);
}

// BST'de arama fonksiyonu
BSTNode* searchBST(BSTNode* root, char author, char *isbn) {
    if (root == NULL || (root->author == author && strcmp(root->isbn, isbn) == 0))
        return root;

    if (author < root->author || (author == root->author && strcmp(isbn, root->isbn) < 0))
        return searchBST(root->left, author, isbn);

    return searchBST(root->right, author, isbn);
}














#define ISBN_SIZE 1000000 // Üretilmesi planlanan maksimum ISBN sayısı

// AVL ve BST fonksiyonları ile düğüm yapılarını yukarıdaki gibi ekleyin.

// Sıralı ISBN oluşturmak için sayaç
int isbnCounter = 1;

// Sıralı ISBN üretme
void generateSequentialISBN(char *isbn) {
    sprintf(isbn, "%013d", isbnCounter++); // 13 haneli sıralı ISBN oluştur
}

// 1. Büyük Veri Setleri Testi
void largeDataSetTest() {
    AVLNode *avlRoot = NULL;
    BSTNode *bstRoot = NULL;
    char isbn[14];
    int dataSize = 1000000; // 1 milyon kayıt
    /*
    // AVL ağacı için ekleme süresi
    clock_t avlStart = clock();
    for (int i = 0; i < dataSize; i++) {
        generateSequentialISBN(isbn);
        avlRoot = insertAVL(avlRoot, 'a' + (i % 26), isbn); // Sıralı yazar isimleri
    }
    clock_t avlEnd = clock();
    double avlTime = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC * 1000;
    printf("AVL ekleme süresi (1M kayıt): %.2f ms\n", avlTime);

    isbnCounter = 1;

    // BST ağacı için ekleme süresi
    clock_t bstStart = clock();
    for (int i = 0; i < dataSize; i++) {
        generateSequentialISBN(isbn);
        bstRoot = insertBST(bstRoot, 'a' + (i % 26), isbn);
    }
    clock_t bstEnd = clock();
    double bstTime = ((double)(bstEnd - bstStart)) / CLOCKS_PER_SEC * 1000;
    printf("BST ekleme süresi (1M kayıt): %.2f ms\n", bstTime);
    */

    // Belirli aralıklardaki ekleme süreleri
    int ranges[][2] = {{0, 10000}, {100000, 110000}, {990000, 1000000}};
    for (int r = 0; r < 3; r++) {
        int start = ranges[r][0];
        int end = ranges[r][1];

        clock_t avlStart = clock();
        for (int i = start; i < end; i++) {
            generateSequentialISBN(isbn);
            avlRoot = insertAVL(avlRoot, 'a', isbn);
        }
        clock_t avlEnd = clock();
        double avlTime = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC * 1000;
        printf("AVL ekleme süresi [%d, %d]: %.2f ms\n", start, end, avlTime);
        isbnCounter=1;
        clock_t bstStart = clock();
        for (int i = start; i < end; i++) {
            generateSequentialISBN(isbn);
            bstRoot = insertBST(bstRoot, 'a', isbn);
        }
        clock_t bstEnd = clock();
        double bstTime = ((double)(bstEnd - bstStart)) / CLOCKS_PER_SEC * 1000;
        printf("BST ekleme süresi [%d, %d]: %.2f ms\n", start, end, bstTime);
    }
}

// 2. Sık Veri Güncelleme Testi
void frequentUpdateTest() {
    int deletecount=1;
    AVLNode *avlRoot = NULL;
    BSTNode *bstRoot = NULL;
    char isbn[14];

    // 1000 başlangıç kaydı ekleme
    for (int i = 0; i < 1000; i++) {
        generateSequentialISBN(isbn);
        avlRoot = insertAVL(avlRoot, 'a' , isbn);
        bstRoot = insertBST(bstRoot, 'a' , isbn);
    }

    int updateCount = 10000; // 10,000 güncelleme
    clock_t avlStart = clock();
    for (int i = 0; i < updateCount; i++) {
        generateSequentialISBN(isbn);
        if (rand() % 3 < 2) { // %67 olasılıkla ekleme
            avlRoot = insertAVL(avlRoot, 'a', isbn);
        } else { // %33 olasılıkla silme
            avlRoot = deleteAVL(avlRoot, 'a', isbn);
        }
    }
    clock_t avlEnd = clock();
    double avlTime = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC * 1000;
    printf("AVL güncelleme süresi (10,000 operasyon): %.2f ms\n", avlTime);

    clock_t bstStart = clock();
    for (int i = 0; i < updateCount; i++) {
        generateSequentialISBN(isbn);
        if (rand() % 3 < 2) {
            bstRoot = insertBST(bstRoot, 'a' + (i % 26), isbn);
        } else {
            bstRoot = deleteBST(bstRoot, 'a' + (i % 26), isbn);
        }
    }
    clock_t bstEnd = clock();
    double bstTime = ((double)(bstEnd - bstStart)) / CLOCKS_PER_SEC * 1000;
    printf("BST güncelleme süresi (10,000 operasyon): %.2f ms\n", bstTime);
}
#define INITIAL_SIZE 100000
#define SEARCH_COUNT 5000
void frequentSearchTest() {
    AVLNode *avlRoot = NULL;
    BSTNode *bstRoot = NULL;
    char isbn[14];
    char isbnList[INITIAL_SIZE][14]; // Eklenen ISBN'leri saklamak için dizi

    // 100,000 başlangıç kaydı ekleme
    for (int i = 0; i < INITIAL_SIZE; i++) {
        generateSequentialISBN(isbn);
        avlRoot = insertAVL(avlRoot, 'a' + (i % 26), isbn);
        bstRoot = insertBST(bstRoot, 'a' + (i % 26), isbn);
        strcpy(isbnList[i], isbn); // Eklenen ISBN'i diziye kaydet
    }

    // 5,000 rastgele arama işlemi
    clock_t avlStart = clock();
    for (int i = 0; i < SEARCH_COUNT; i++) {
        int randomIndex = rand() % INITIAL_SIZE; // Rastgele bir indeks seç
        searchAVL(avlRoot, 'a' + (randomIndex % 26), isbnList[randomIndex]);
    }
    clock_t avlEnd = clock();
    double avlTime = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC * 1000;
    printf("AVL arama süresi (5,000 arama): %.2f ms\n", avlTime);

    clock_t bstStart = clock();
    for (int i = 0; i < SEARCH_COUNT; i++) {
        int randomIndex = rand() % INITIAL_SIZE; // Rastgele bir indeks seç
        searchBST(bstRoot, 'a' + (randomIndex % 26), isbnList[randomIndex]);
    }
    clock_t bstEnd = clock();
    double bstTime = ((double)(bstEnd - bstStart)) / CLOCKS_PER_SEC * 1000;
    printf("BST arama süresi (5,000 arama): %.2f ms\n", bstTime);
}





// Ana fonksiyon
int main() {
    testInsertionsAndDeletions();
    printf("Büyük Veri Seti Testi:\n");
    largeDataSetTest();

    printf("\nSık Veri Güncelleme Testi:\n");
    frequentUpdateTest();

    printf("\nSık Arama İhtiyacı Testi:\n");
    frequentSearchTest();
    return 0;
}
