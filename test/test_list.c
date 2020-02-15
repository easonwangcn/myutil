#define LOG_LEVELx LOG_INFO
#include "myutil.h"

typedef struct _IntList
{
    List super;
    int i;
} IntList;

static void initList(IntList *il, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
        il[i].i = i;
    for (i = 0; i < size - 1; i++)
        il[i].super.next = &(il[i + 1].super);
    il[size - 1].super.next = NULL;
}

static void printList(List *head)
{
    ListIter it = ListIter_new(head);
    LOGI("--------");
    while(ListIter_next(&it))
        LOGI("%d", ((IntList *)(ListIter_current(&it)))->i);
}

static void verifyList(List *head)
{
    printList(head);
    
    ListIter it = ListIter_new(head);
    size_t i = 0;
    IntList *current;
    while(ListIter_next(&it))
    {
        current = (IntList *)(ListIter_current(&it));
        EXPECT_EQ(current->i, i);
        i++;
    }
}

#define TEST_LIST_BATCH0 13
#define TEST_LIST_BATCH1 312

TEST_CASE(travel)
{
    /* create list */
    IntList il[TEST_LIST_BATCH1];
    initList(il, TEST_LIST_BATCH1);

    /* test travel */
    verifyList(&il[0].super);
}

TEST_CASE(insert_head)
{
    /* create list */
    IntList il[TEST_LIST_BATCH0];
    initList(il, TEST_LIST_BATCH0);
    verifyList(&il[0].super);

    /* start from seconds half */
    List *node;
    List *head = &il[TEST_LIST_BATCH0 / 2].super;
    ListIter it;
    ListIter_init(&it, head);
    
    /* insert first half */
    int i;
    for (i = TEST_LIST_BATCH0 / 2 - 1; i >= 0; i--)
    {
        node = ListIter_insert(&it, &il[i].super, &head);
        EXPECT_EQ(node, &il[i].super);
    }
    
    /* verify */
    verifyList(head);
}

TEST_CASE(insert_middle)
{
    /* create list */
    IntList il[TEST_LIST_BATCH1];
    initList(il, TEST_LIST_BATCH1);
    verifyList(&il[0].super);

    /* start from seconds half */
    List *node;
    List *head = &il[TEST_LIST_BATCH1 / 2].super;
    
    /* insert first half */
    ListIter it;
    ListIter_init(&it, head);
    int i = 0;
    while(ListIter_next(&it) && i < (TEST_LIST_BATCH1 / 2))
    {
        node = ListIter_insert(&it, &il[i].super, &head);
        EXPECT_EQ(node, &il[i].super);
        i++;
    }
    
    /* verify */
    verifyList(head);
}

TEST_CASE(insert_tail)
{
    /* create list */
    IntList il[TEST_LIST_BATCH0];
    initList(il, TEST_LIST_BATCH0);
    verifyList(&il[0].super);

    /* cut seconds half */
    List *node;
    List *head = &il[0].super;
    il[TEST_LIST_BATCH0 / 2].super.next = NULL;
    
    /* insert first half */
    ListIter it;
    ListIter_init(&it, head);
    
    /* travel to end. */
    while(ListIter_next(&it));
    
    /* insert secon half */
    int i = TEST_LIST_BATCH0 / 2 + 1;
    while(ListIter_next(&it) && i < TEST_LIST_BATCH0)
    {
        node = ListIter_insert(&it, &il[i].super, &head);
        EXPECT_EQ(node, &il[i].super);
        i++;
    }
    
    /* verify */
    verifyList(head);
}

TEST_CASE(remove_head)
{
    /* create list */
    IntList il[TEST_LIST_BATCH0];
    initList(il, TEST_LIST_BATCH0);
    verifyList(&il[0].super);
    
    List *head = &il[0].super;
    List *node;
    
    /* insert first half */
    ListIter it;
    ListIter_init(&it, head);
    
    /* remove head */
    int i = 0;
    for (i = 0; i < TEST_LIST_BATCH0 / 2; i++)
    {
        node = ListIter_remove(&it, &head);
        EXPECT_EQ(node, &il[i].super);
        EXPECT_EQ(head, &il[i + 1].super);
    }
    
    /* insert back */
    for (i = 0; i < TEST_LIST_BATCH0 / 2; i++)
    {
        node = ListIter_insert(&it, &il[i].super, &head);
        EXPECT_EQ(node, &il[i].super);
        ListIter_next(&it);
    }
    
    /* verify */
    verifyList(head);
}

TEST_CASE(remove_middle)
{
    /* create list */
    IntList il[TEST_LIST_BATCH1];
    initList(il, TEST_LIST_BATCH1);
    verifyList(&il[0].super);
    
    List *head = &il[0].super;
    List *node;
    
    /* move to first */
    ListIter it;
    ListIter_init(&it, head);
    
    /* move to 1/4. */
    int i = 0;
    for (i = 0; i < TEST_LIST_BATCH1 / 4 + 1; i++)
        ListIter_next(&it);
    
    /* remove middle 1/4 */
    for (; i < TEST_LIST_BATCH1 / 2 + 1; i++)
    {
        node = ListIter_remove(&it, &head);
        EXPECT_EQ(node, &il[i - 1].super);
        EXPECT_EQ(head, &il[0].super);
    }
    
    /* insert back */
    for (i = TEST_LIST_BATCH1 / 4; i < TEST_LIST_BATCH1 / 2; i++)
    {
        node = ListIter_insert(&it, &il[i].super, &head);
        EXPECT_EQ(node, &il[i].super);
        ListIter_next(&it);
    }
    
    /* verify */
    verifyList(head);
}

TEST_CASE(remove_tail)
{
    /* create list */
    IntList il[TEST_LIST_BATCH0];
    initList(il, TEST_LIST_BATCH0);
    verifyList(&il[0].super);
    
    List *head = &il[0].super;
    List *node;
    
    /* move to first */
    ListIter it;
    ListIter_init(&it, head);
    
    /* move to 1/2. */
    int i = 0;
    for (i = 0; i < TEST_LIST_BATCH0 / 2 + 1; i++)
        ListIter_next(&it);
    
    /* remove last 1/2 */
    while(ListIter_remove(&it, &head) != NULL);
    /* check if last removed. */
    EXPECT_NULL(ListIter_remove(&it, &head));
    
    /* check head. */
    EXPECT_EQ(head, &il[0].super);
    
    /* insert back */
    for (i = TEST_LIST_BATCH0 / 2; i < TEST_LIST_BATCH0; i++)
    {
        node = ListIter_insert(&it, &il[i].super, &head);
        EXPECT_EQ(node, &il[i].super);
        ListIter_next(&it);
    }
    
    /* verify */
    verifyList(head);
}

TEST_CASE(remove_all)
{
    /* create list */
    IntList il[TEST_LIST_BATCH0];
    initList(il, TEST_LIST_BATCH0);
    verifyList(&il[0].super);
    
    List *head = &il[0].super;
    
    /* move to first */
    ListIter it;
    ListIter_init(&it, head);
    
    /* remove all */
    while(ListIter_remove(&it, &head) != NULL);
    
    /* check head. */
    EXPECT_EQ(head, NULL);
}

TEST_SUITE(list)
{
    TEST_RUN_CASE(travel);
    TEST_RUN_CASE(insert_head);
    TEST_RUN_CASE(insert_middle);
    TEST_RUN_CASE(insert_tail);
    TEST_RUN_CASE(remove_head);
    TEST_RUN_CASE(remove_middle);
    TEST_RUN_CASE(remove_tail);
    TEST_RUN_CASE(remove_all);
}
