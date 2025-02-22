#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 9

struct Node{
    int no;
    struct Edge* link_head;
};

struct Edge{
    int dest;
    struct Edge* next;
};
struct Node* graph[MAX_NODES];

void initialize(){
    for(int i=0; i<MAX_NODES;i++){
        graph[i]=malloc(sizeof(struct Node));
        graph[i]->no=i;
        graph[i]->link_head=NULL;

    }


}

void link(int dest,int src){
    dest--;
    src--;
    struct Edge* tmp=graph[src]->link_head;
    graph[src]->link_head=malloc(sizeof(struct Edge));
    graph[src]->link_head->next=tmp;
    graph[src]->link_head->dest=dest;

    if(dest!=src){
    struct Edge* tmp=graph[dest]->link_head;
    graph[dest]->link_head=malloc(sizeof(struct Edge));
    graph[dest]->link_head->next=tmp;
    graph[dest]->link_head->dest=src;

    }


}

void print_graph(){
    for(int i=0; i<MAX_NODES; i++){
        printf("\n%d. node baglantilari:\n",i+1);
        struct Edge* head=graph[i]->link_head;
        while(head){
            printf("%d\n",head->dest+1);
            head=head->next;
        }
    }
}
int gone[MAX_NODES] = {0}; 

void DFS(int begin) {
    begin--;
    printf("%d ", begin + 1); 
    gone[begin] = 1; 

    struct Edge* head = graph[begin]->link_head;
    while (head) { 
        if (!gone[head->dest]) { 
            DFS(head->dest+1);
        }
        head = head->next; 
    }
}


void BFS(int start) {
    int visited[MAX_NODES] = {0}; 
    int queue[MAX_NODES];         
    int front = 0, rear = 0;     

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current+1); 
        struct Edge* head = graph[current]->link_head;
        while (head) {
            int neighbor = head->dest; 
            if (!visited[neighbor]) {  
                queue[rear++] = neighbor; 
                visited[neighbor] = 1;    
            }
            head = head->next; 
        }
    }
}
void welsh_powell() {
    int degree[MAX_NODES] = {0}; 
    int color[MAX_NODES] = {0};  
    int used[MAX_NODES] = {0};   

    for (int i = 0; i < MAX_NODES; i++) {
        struct Edge* head = graph[i]->link_head;
        while (head) {
            degree[i]++;
            head = head->next;
        }
    }


    int order[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++) order[i] = i;

    for (int i = 0; i < MAX_NODES - 1; i++) {
        for (int j = i + 1; j < MAX_NODES; j++) {
            if (degree[order[j]] > degree[order[i]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    for (int i = 0; i < MAX_NODES; i++) {
        int current = order[i];

        struct Edge* head = graph[current]->link_head;
        while (head) {
            int neighbor = head->dest;
            if (color[neighbor] > 0) {
                used[color[neighbor]] = 1;
            }
            head = head->next;
        }
        int c;
        for (c = 1; c <= MAX_NODES; c++) {
            if (!used[c]) break;
        }
        color[current] = c;
        head = graph[current]->link_head;
        while (head) {
            int neighbor = head->dest;
            if (color[neighbor] > 0) {
                used[color[neighbor]] = 0;
            }
            head = head->next;
        }
    }
    printf("\nNode Colors:\n");
    for (int i = 0; i < MAX_NODES; i++) {
        printf("Node %d -> Color %d\n", i + 1, color[i]);
    }
}





int main(){
    initialize();
    link(1,3);
    link(2,3);
    link(4,3);
    link(5,8);
    link(5,6);
    link(5,7);
    link(9,7);
    //print_graph();
    printf("DFS:");
    DFS(1);
    DFS(6);
    link(5,2);
    printf("\nBFS:");
    BFS(3);
    welsh_powell();

    


    return 0;
}