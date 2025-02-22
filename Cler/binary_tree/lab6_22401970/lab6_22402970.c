#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} node;

node *createNode(int value)
{
    node *new = malloc(sizeof(node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    return new;
}

node *insert(node *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->value)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = insert(root->right, value);
    }

    return root;
}

node *search(node *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (key == root->value)
    {
        return root;
    }
    if (key > root->value)
    {
        return search(root->right, key);
    }
    if (key < root->value)
    {
        return search(root->left, key);
    }
}

void preorder(node *root)
{
    if(root==NULL){
        return;
    }
    printf("");
    preorder(root->left);
    preorder(root->right);
}

void postorder(node *root)
{
    if(root==NULL){
        return;
    }
    preorder(root->left);
    preorder(root->right);
    printf("");
}

void data(int n, int *array, int scenario)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = i + 1;
    }
    if (scenario == 1)
    {
        return;
    }
    int tmp;
    if (scenario == 2)
    {
        for (int i = 0; i < n; i++)
        {
            tmp = array[i];
            array[i] = array[n - i - 1];
            array[n - i - 1] = tmp;
        }
    }
    if (scenario == 3)
    {
        for (int i = n / 2; i < n; i++)
        {
            tmp = array[i];
            array[i] = array[n - (i - n / 2) - 1];
            array[n - (i - n / 2) - 1] = tmp;
        }
    }
    if (scenario == 4)
    {
        for (int i = n / 2; i < n - 1; i++) {
            int temp = array[i];
            array[i] = array[n - i + (n / 2) - 2];
            array[n - i + (n / 2) - 2] = temp;
        }
    }
}
    void measure(int n, int scenario){
        int array[n];
        node* new=NULL;
        data(n,array,scenario);
        clock_t start=clock();
        for(int i=0; i<n; i++){
            new=insert(new,array[i]);
        }    
        clock_t finish=clock();
        printf("%d elemanlı dizi %d. senaryo ekleme süresi: %f\n", n, scenario, (double)(finish-start)/CLOCKS_PER_SEC);


        start=clock();
        for(int i=0; i<n; i++){
            new=search(new,array[i]);
        }    
        finish=clock();
        printf("%d elemanlı dizi %d. senaryo arama süresi: %f\n", n, scenario, (double)(finish-start)/CLOCKS_PER_SEC);


        start=clock();
        preorder(new); 
        finish=clock();
        printf("%d elemanlı dizi %d. senaryo preorder süresi: %f\n", n,scenario, (double)(finish-start)/CLOCKS_PER_SEC);


        start=clock();
        postorder(new);   
        finish=clock();
        printf("%d elemanlı dizi %d. senaryo postorder süresi: %f\n\n", n,scenario, (double)(finish-start)/CLOCKS_PER_SEC);

    }

int main()
{   
    srand(time(0));
    int n_array[7]={10,50,100,250,500,1000,5000};
    for(int i=0; i<7; i++){
        for(int k=1;k<5;k++){
            measure(n_array[i],k);
        }
    }
    
}
