#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct entry
{
    char isim[50];
    char soyisim[50];
    char telefon[50];
    struct entry *next;
};

struct entry *head = NULL;
struct entry *curr = NULL;

struct entry *create_entry(int val)
{
    struct entry *ptr = (struct entry *)malloc(sizeof(struct entry));
    if (NULL == ptr)
    {
        printf("\n entry creation failed \n");
        return NULL;
    }
    ptr->val = val;
    ptr->next = NULL;
    head = curr = ptr;
    return ptr;
}

struct entry *add_to_list(int val, bool add_to_end)
{
    if (NULL == head)
    {
        return (create_entry(val));
    }
    if (add_to_end)
        printf("\n Adding entry to end of list with value [%d]\n", val);
    else
        printf("\n Adding entry to beginning of list with value [%d]\n", val);
    struct entry *ptr = (struct entry *)malloc(sizeof(struct entry));
    if (NULL == ptr)
    {
        printf("\n entry creation failed \n");
        return NULL;
    }
    ptr->val = val;
    ptr->next = NULL;
    if (add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}

struct entry *search_in_list(int val, struct entry **prev)
{
    struct entry *ptr = head;
    struct entry *tmp = NULL;
    bool found = false;
    printf("\n Searching the list for value [%d] \n", val);
    while (ptr != NULL)
    {
        if (ptr->val == val)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }
    if (true == found)
    {
        if (prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

int delete_from_list(int val)
{
    struct entry *prev = NULL;
    struct entry *del = NULL;
    printf("\n Deleting value [%d] from list\n", val);
    del = search_in_list(val, &prev);
    if (del == NULL)
    {
        return -1;
    }
    else
    {
        if (prev != NULL)
            prev->next = del->next;
    }
    if (del == curr)
    {
        curr = prev;
    }
    else if (del == head)
    {
        head = del->next;
    }
    free(del);
    del = NULL;

    return 0;
}
void print_list(void)
{
    struct entry *ptr = head;
    printf("\n -------Printing list Start------- \n");
    while (ptr != NULL)
    {
        printf("\n [%d] \n", ptr->val);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");

    return;
}



void delete_something(const char *phone_number) {
    struct entry *current = head;
    struct entry *prev = NULL;
    int deleted_count = 0;

    while (current != NULL) {
        if (strcmp(current->phone, phone_number) == 0) {
            if (prev == NULL) { // Başta bulunan eleman siliniyor
                head = current->next;
            } else {
                prev->next = current->next;
            }
            struct entry *temp = current;
            current = current->next;
            free(temp); // Belleği serbest bırak.
            deleted_count++;
        } else {
            prev = current;
            current = current->next;
        }
    }

    if (deleted_count > 0) {
        printf("%d kayıt başarıyla silindi.\n", deleted_count);
    } else {
        printf("Bu telefon numarasına sahip kayıt bulunamadı.\n");
    }
}