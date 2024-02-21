#include "StrList.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// #define DEBUG 1

enum Command
{
    CREATE = 1,
    INSERT_AT = 2,
    PRINT = 3,
    SIZE_PRINT = 4,
    WORD_PRINT = 5,
    NUM_OF_CHARS = 6,
    WORD_NUMBER = 7,
    DELETE_WORD = 8,
    DELETE_AT_INDEX = 9,
    REVERSE_LIST = 10,
    CLEAR = 11,
    SORT = 12,
    CHECK_SORT = 13,
    EXIT = 0
};

int main()
{
    int curr;
    StrList *list = StrList_alloc();
    int res = 0;
    int firstprint = 1;
    // int scan = scanf("%d", &curr);
    while (scanf("%d", &curr))
    {
        switch (curr)
        {
        case CREATE:
        {
            StrList_free(list);
            int num = 0;
            scanf("%d", &num);
            char word[20];
            while (num > 0)
            {
                if (scanf("%s", word) >= 0)
                {
#ifdef DEBUG
                    printf("%s\n", word);
#endif
                    StrList_insertLast(list, word);
                    num--;
                }
                else
                {
                    break;
                }
            }
#ifdef DEBUG
            StrList_print(list);
#endif
        }
        break;
        case INSERT_AT:
        {
            int index = -1;
            scanf("%d", &index);
            if (index >= 0)
            {
                char word[30];
                scanf("%s", word);
                if (strlen(word) > 0)
                {
                    StrList_insertAt(list, word, index);
                }
            }
        }

        break;
        case PRINT:
            if (firstprint == 0)
                printf("\n");
            else
                firstprint = 0;

            StrList_print(list);
            break;
        case SIZE_PRINT:
            if (firstprint == 0)
                printf("\n");
            else
                firstprint = 0;

            res = StrList_size(list);
            printf("%d", res);
            break;
        case WORD_PRINT:

        {
            if (firstprint == 0)
                printf("\n");
            else
                firstprint = 0;
            ;

            int index = -1;
            res = scanf("%d", &index);
            if (res >= 0 && index >= 0)
            {
                StrList_printAt(list, index);
            }
        }
        break;
        case NUM_OF_CHARS:
            if (firstprint == 0)
                printf("\n");
            else
                firstprint = 0;
            res = StrList_printLen(list);
            printf("%d", res);
            break;
        case WORD_NUMBER:
        {
            if (firstprint == 0)
                printf("\n");
            else
                firstprint = 0;

            char word[30];
            scanf("%s", word);
            if (strlen(word) > 0)
            {
                res = StrList_count(list, word);
                printf("%d", res);
            }
        }
        break;
        case DELETE_WORD:
        {
            char word[30];
            res = scanf("%s", word);
            if (strlen(word) > 0)
            {
                StrList_remove(list, word);
            }
        }
        break;
        case DELETE_AT_INDEX:

        {
            int index = -1;
            scanf("%d", &index);
            if (index >= 0)
            {
                StrList_removeAt(list, index);
            }
        }
        break;
        case REVERSE_LIST:
            StrList_reverse(list);
            break;
        case CLEAR:
            StrList_free(list);
            break;
        case SORT:
            StrList_sort(list);
            break;
        case CHECK_SORT:

            if (firstprint == 0)
                printf("\n");
            else
                firstprint = 0;
            ;

            res = StrList_isSorted(list);
            if (res == 0)
                printf("false");
            else
                printf("true");
            break;
        case EXIT:
            return 0;
            break;
        default:
            break;
        }
    }

    return 0;
}