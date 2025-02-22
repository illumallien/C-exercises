#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
} node;

node* createNode(int value){
    node* new=malloc(sizeof(node*));
    new->value=value;
    new->left=NULL;
    new->right=NULL;
    return new;
}

struct Node* insert(node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    
    return root;
}

struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// BST'den eleman silme
node* delete(node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->value) {
        root->left = delete(root->left, value);
    } else if (value > root->value) {
        root->right = delete(root->right, value);
    } else {
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }

        node* temp = findMin(root->right);
        root->value = temp->value;
        root->right = delete(root->right, temp->value);
    }

    return root;
}

void printdegrees(node* root){
    if(root==NULL) return;
    int degree=0;
    if(root->right) degree++;
    if(root->left) degree++;
    printf("\n%d degerli node'un derecesi: %d\n", root->value, degree);
    printdegrees(root->left);
    printdegrees(root->right);
}

void printDepths(node* root, int depth){
    if (!root) return;
    printf("\n%d degerli nodeun derinliği: %d\n", root->value, depth);
    printDepths(root->right, depth+1);
    printDepths(root->left, depth+1);
}

int findDepth(node* root, int value, int depth) {
    if (root == NULL) {
        return -1;
    }
    
    if (root->value == value) {
        return depth;
    } else if (value < root->value) {
        return findDepth(root->left, value, depth + 1);
    } else {
        return findDepth(root->right, value, depth + 1);
    }
}

int findPathLength(node* root, int node1, int node2) {
    if (root == NULL) {
        return -1;
    }

    if (root->value > node1 && root->value > node2) {
        return findPathLength(root->left, node1, node2);
    }
    if (root->value < node1 && root->value < node2) {
        return findPathLength(root->right, node1, node2);
    }

    int pathLength1 = findDepth(root, node1, 0);
    int pathLength2 = findDepth(root, node2, 0);
    
    return pathLength1 + pathLength2;
}

int isEqual(node* root1, node* root2) {
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }
    
    if (root1 == NULL || root2 == NULL) {
        return 0;
    }
    
    return (root1->value == root2->value &&
            isEqual(root1->left, root2->left) &&
            isEqual(root1->right, root2->right));
}

int main(){
    node* bst1=createNode(5);
    insert(bst1,7);
    insert(bst1,3);
    insert(bst1,2);
    insert(bst1,4);

    node* bst2=createNode(5);
    insert(bst2,3);
    insert(bst2,7);
    insert(bst2,4);
    insert(bst2,2);

    node* bst3=createNode(5);
    insert(bst3,7);
    insert(bst3,2);
    insert(bst3,3);
    insert(bst3,4);

    node* bst4=createNode(5);
    insert(bst4,3);
    insert(bst4,7);
    insert(bst4,6);
    insert(bst4,4);
    insert(bst4,2);


    printf("\nbst3 agacinin node dereceleri\n");
    printdegrees(bst3);

    printf("\n7'yi silmeden önce bst4 agacinin node derinlikleri\n");
    printDepths(bst4,0);
    delete(bst4,7);
    printf("\n7'yi sildikten sonra bst4 agacinin node derinlikleri\n");
    printDepths(bst4,0);


    printf("\nbst3 agacinda 2-7 nodları arasındaki path\n");
    printf("%d",findPathLength(bst3,2,7));
    printf("\nbst3 agacinda 2-4 nodları arasındaki path\n");
    printf("%d",findPathLength(bst3,2,4));

    if(isEqual(bst1,bst2)){
        printf("\nbst1 ve bst2 esit\n");
    }
    else{printf("\nbst1 ve bst2 esit degil.\n");}

        if(isEqual(bst1,bst3)){
        printf("\nbst1 ve bst3 esit\n");
    }
    else{printf("\nbst1 ve bst3 esit degil.\n");}

        if(isEqual(bst1,bst4)){
        printf("\nbst1 ve bst4 esit\n");
    }
    else{printf("\nbst1 ve bst4 esit degil.\n");}




}

