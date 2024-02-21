#include "StrList.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// #define DEBUG

typedef struct _node
{
    char *data;
    struct _node *next;
} Node;

struct _StrList
{
    Node *_head;
    int _size;
};

Node *Node_alocc(const char *data, Node *next)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = (char *)malloc(strlen(data) * sizeof(char));
    strcpy(n->data, data);
    n->next = next;
    return n;
}

void node_free(Node *node)
{
    free(node->data);
    free(node);
}

StrList *StrList_alloc()
{
    StrList *l = (StrList *)malloc(sizeof(StrList));
    if (l != NULL)
    {
        l->_head = NULL;
        l->_size = 0;
    }
    return l;
}

void StrList_free(StrList *StrList)
{
    if (StrList != NULL)
    {
        Node *p1 = StrList->_head;
        Node *p2 = NULL;
        while (p1 != NULL)
        {
#ifdef DEBUG
            printf("\ndeleting %s", p1->data);
#endif
            p2 = p1;
            p1 = p1->next;
#ifdef DEBUG
            printf("\ngetting next");
#endif
            node_free(p2);
            // printf("\n next deleting %s\n",p1->data);
        }
        StrList->_head = NULL;
        StrList->_size = 0;
        // free(StrList);
    }
}

size_t StrList_size(const StrList *StrList)
{
    if (StrList != NULL)
    {
        return StrList->_size;
    }
    return 0;
}

void StrList_insertLast(StrList *StrList, const char *data)
{
    if (StrList != NULL && data != NULL)
    {
        Node *curr = StrList->_head;
        Node *n = Node_alocc(data, NULL);
#ifdef DEBUG
        printf("data recived: %s\n", n->data);
#endif
        if (StrList->_head)
        {
            while (curr->next != NULL)
            {
                curr = curr->next;
            }
            // Node *n = Node_alocc(data, NULL);
            curr->next = n;
        }
        else
        {
            // Node *n = Node_alocc(data,NULL);
            StrList->_head = n;
        }
        StrList->_size++;
    }
}

void StrList_insertAt(StrList *StrList, const char *data, int index)
{
#ifdef DEBUG
    printf("insert at %d, word = %s", index, data);
#endif
    if (index >= StrList->_size)
        return;
    Node *curr = StrList->_head;
    for (int i = 0; i < index - 1; i++)
    {
        curr = curr->next;
    }
    Node *n = Node_alocc(data, curr->next);
    curr->next = n;
#ifdef DEBUG
    printf("list after insert:\n");
    StrList_print(StrList);
#endif
}

char *StrList_firstData(const StrList *StrList)
{
    if (StrList != NULL && StrList->_head != NULL)
        return StrList->_head->data;
    else
        return NULL;
}

void StrList_print(const StrList *StrList)
{
    if (StrList != NULL && StrList->_head != NULL)
    {
        Node *curr = StrList->_head;
        printf("%s", curr->data);
        curr = curr->next;
        while (curr)
        {
            printf(" ");
            printf("%s", curr->data);
            curr = curr->next;
        }
    }else{
        printf("\n");
    }
}

void StrList_printAt(const StrList *Strlist, int index)
{
    int i = 0;
    Node *curr = Strlist->_head;
    while (i < index)
    {
        i++;
        curr = curr->next;
    }
    printf("%s", curr->data);
}

int StrList_printLen(const StrList *Strlist)
{
    Node *curr = Strlist->_head;
    int sum = 0;
    while (curr)
    {
        sum += strlen(curr->data);
        curr = curr->next;
    }
    return sum;
}

int StrList_count(StrList *StrList, const char *data)
{
    Node *curr = StrList->_head;
    int count = 0;
    while (curr)
    {
        if (strcmp(data, curr->data) == 0)
            count++;
        curr = curr->next;
    }
    return count;
}

void StrList_remove(StrList *StrList, const char *data)
{
    // handling case when head needs to be deleted
    Node *curr = StrList->_head;
    while (strcmp(curr->data, data) == 0)
    {
        StrList->_head = curr->next;
        node_free(curr);
        curr = StrList->_head;
    }

    //
    Node *prev = StrList->_head;
    while (prev && prev->next)
    {
        if (strcmp(prev->next->data, data) == 0)
        {
            curr = prev->next;
            prev->next = curr->next;
            node_free(curr);
        }
        prev = prev->next;
    }
}

void StrList_removeAt(StrList *StrList, int index)
{
    // handling case when head needs to be deleted
    if (index == 0)
    {
        Node *temp = StrList->_head;
        StrList->_head = StrList->_head->next;
        node_free(temp);
    }

    //
    Node *prev = StrList->_head;
    for (int i = 0; i < index - 1; i++)
    {
        prev = prev->next;
    }
    Node *curr = prev->next;
    prev->next = curr->next;
    curr->next = NULL;
    node_free(curr);
}

int StrList_isEqual(const StrList *StrList1, const StrList *StrList2)
{
    if (StrList1 && StrList2 && StrList1->_size == StrList2->_size)
    {
        Node *n1 = StrList1->_head;
        Node *n2 = StrList2->_head;
        while (n1 && n2)
        {
            // if found at least 1 unequal pair return false
            if (!strcmp(n1->data, n2->data))
                return 0;

            n1 = n1->next;
            n2 = n2->next;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

StrList *StrList_clone(const StrList *StrList)
{
    struct _StrList *clone = NULL;
    if (StrList)
    {
        clone = StrList_alloc();
        Node *curr = StrList->_head;
        while (curr)
        {
            StrList_insertLast(clone, curr->data);
            curr = curr->next;
        }
    }
    return clone;
}

void StrList_reverse(StrList *StrList)
{
    if (StrList != NULL && StrList->_head != NULL)
    {

        Node *prev = NULL;
        Node *curr = StrList->_head;
        if (curr->next != NULL)
        {
            Node *next = NULL;
            while (curr != NULL)
            {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            StrList->_head = prev;
        }
    }
}

void split(Node *head, Node **frontref, Node **lastref)
{
    Node *slow = head;
    Node *fast = slow->next;
    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }

    *frontref = head;
    *lastref = slow->next;
    slow->next = NULL;
}

Node *sorted_merge(Node *a, Node *b)
{
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    Node *result = NULL;

    if (strcmp(a->data, b->data) <= 0)
    {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b->next);
    }

    return result;
}

void merge_sort(Node **headref)
{

    Node *head = *headref;

    if (head == NULL || head->next == NULL)
        return;

    Node *a = head;
    Node *b = head;

    split(head, &a, &b);

    merge_sort(&a);
    merge_sort(&b);

    Node *sorted_head = sorted_merge(a, b);
    *headref = sorted_head;
}

void StrList_sort(StrList *StrList)
{
    if (StrList != NULL)
    {
        merge_sort(&(StrList->_head));
    }
}

int StrList_isSorted(StrList *StrList)
{
    if (StrList && StrList->_head)
    {
        Node *curr = StrList->_head;
        Node *next = StrList->_head->next;
        while (next)
        {
            int cmp = strcmp(curr->data, next->data);
            if (cmp > 0)
            {
                return 0;
            }
            curr = next;
            next = next->next;
        }
    }
    return 1;
}
