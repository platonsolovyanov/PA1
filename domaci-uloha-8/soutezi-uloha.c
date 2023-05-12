#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
    struct TItem *m_Next;
    char *m_Name;
    char m_Secret[24];
} TITEM;

int cmpName(const TITEM *a,
            const TITEM *b)
{
    return strcmp(a->m_Name, b->m_Name);
}

int cmpNameInsensitive(const TITEM *a,
                       const TITEM *b)
{
    return strcasecmp(a->m_Name, b->m_Name);
}

int cmpNameLen(const TITEM *a,
               const TITEM *b)
{
    size_t la = strlen(a->m_Name), lb = strlen(b->m_Name);
    return (lb < la) - (la < lb);
}

#endif /* __PROGTEST__ */

size_t leng(TITEM* root)
{
    int c = 0;
    while (root != NULL)
    {
        root = root->m_Next;
        c++;
    }
    return c;
}

void mergeByIt(TITEM** s1, TITEM** e1,
               TITEM** s2, TITEM** e2,
               int asc, int (*cmpFn)(const TITEM *, const TITEM *))
{
    TITEM* temp = NULL;
    short int priority = 0;
    if ((cmpFn(*s1, *s2) > 0 && asc) || (cmpFn(*s1, *s2) < 0 && !asc)) {
        TITEM* temp = *s1;
        *s1 = *s2;
        *s2 = temp;
        temp = *e1;
        *e1 = *e2;
        *e2 = temp;
        priority = 1;
    }

    TITEM* as = *s1, *ae = *e1, *bs = *s2, *ben = (*e2)->m_Next;
    while (as != ae && bs != ben) {
        int r = cmpFn(as->m_Next, bs);
        if ((asc && (r > 0 || (r == 0 && priority))) || (!asc && (r < 0 || (r == 0 && priority))) ) {
            temp = bs->m_Next;
            bs->m_Next = as->m_Next;
            as->m_Next = bs;
            bs = temp;
        }
        as = as->m_Next;
    }
    if (as == ae)
        as->m_Next = bs;
    else
        *e2 = *e1;
}

TITEM *newItem(const char *name,
               TITEM *next)
{
    TITEM *n = (TITEM *) malloc(sizeof(TITEM));
    n->m_Next = next;
    size_t l = strlen(name);
    n->m_Name = (char *) malloc(l + 1);
    memcpy(n->m_Name, name, l + 1);

    return n;
}

TITEM *sortListCmp(TITEM *l,
                   int ascending,
                   int            (*cmpFn)(const TITEM *, const TITEM *))
{
    if (!l || !l->m_Next) return l;

    TITEM* s1 = NULL, *e1 = NULL, *s2 = NULL, *e2 = NULL, *pre = NULL;
    size_t len = leng(l);

    for (size_t g = 1; g < len; g = g*2)
    {
        s1 = l;
        while (s1) {
            short int F = 0;
            if (s1 == l)
                F = 1;

            size_t c = g;
            e1 = s1;
            while (--c && e1->m_Next) e1 = e1->m_Next;

            s2 = e1->m_Next;
            if (!s2)
                break;
            c = g;
            e2 = s2;
            while (--c && e2->m_Next) e2 = e2->m_Next;

            TITEM *temp = e2->m_Next;
            mergeByIt(&s1, &e1, &s2, &e2, ascending, cmpFn);

            if (F) l = s1;
            else pre->m_Next = s1;

            pre = e2;
            s1 = temp;
        }
        pre->m_Next = s1;
    }

    return l;
}

void freeList(TITEM *root)
{
    TITEM *temp;
    while (root)
    {
        temp = root->m_Next;
        free(root->m_Name);
        free(root);
        root = temp;
    }

    return;
}

/*void printList(TITEM* src)
{
    printf("Printing list:\n");
    while (src)
    {
        printf("Node: %x, next %x, text: %s\n", src, src->m_Next, src->m_Name);
        src = src->m_Next;
    }
    printf("\n");

    return;
}*/

#ifndef __PROGTEST__

int main(int argc, char *argv[])
{
    TITEM *l;
    char tmp[50];

    assert (sizeof(TITEM) == sizeof(TITEM *) + sizeof(char *) + 24 * sizeof(char));
    l = NULL;
    l = newItem("BI-PA1", l);
    l = newItem("BIE-PA2", l);
    l = newItem("NI-PAR", l);
    l = newItem("lin", l);
    l = newItem("AG1", l);
    assert (l
            && !strcmp(l->m_Name, "AG1"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    //printList(l);
    l = sortListCmp(l, 1, cmpName);
    //printList(l);
    assert (l
            && !strcmp(l->m_Name, "AG1"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortListCmp(l, 1, cmpNameInsensitive);
    assert (l
            && !strcmp(l->m_Name, "AG1"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    //printList(l);
    l = sortListCmp(l, 1, cmpNameLen);
    //printList(l);
    assert (l
            && !strcmp(l->m_Name, "AG1"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = newItem("AAG.3", l);
    assert (l
            && !strcmp(l->m_Name, "AAG.3"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "AG1"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    //printList(l);
    l = sortListCmp(l, 0, cmpNameLen);
    //printList(l);
    assert (l
            && !strcmp(l->m_Name, "BIE-PA2"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    freeList(l);
    l = NULL;
    strncpy(tmp, "BI-PA1", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "BIE-PA2", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "NI-PAR", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "lin", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "AG1", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    assert (l
            && !strcmp(l->m_Name, "AG1"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortListCmp(l, 1, cmpName);
    assert (l
            && !strcmp(l->m_Name, "AG1"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortListCmp(l, 1, cmpNameInsensitive);
    assert (l
            && !strcmp(l->m_Name, "AG1"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortListCmp(l, 1, cmpNameLen);
    assert (l
            && !strcmp(l->m_Name, "AG1"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    strncpy(tmp, "AAG.3", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    assert (l
            && !strcmp(l->m_Name, "AAG.3"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "AG1"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortListCmp(l, 0, cmpNameLen);
    assert (l
            && !strcmp(l->m_Name, "BIE-PA2"));
    assert (l->m_Next
            && !strcmp(l->m_Next->m_Name, "BI-PA1"));
    assert (l->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
    assert (l->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
    assert (l->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next
            && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
    assert (l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    freeList(l);
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */