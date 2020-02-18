#define LOG_LEVELx LOG_INFO
#include "myutil.h"

#include <string.h>

typedef struct _DbIntList
{
    DbList super;
    int i;
} IntDbList, *IntDbListRef;

static void initNode(IntDbListRef il, size_t size)
{
    int i;
    memset(il, size * sizeof(IntDbList), 0);
    for (i = 0; i < size; i++)
    {
        il[i].i = i;
    }
}

static void initList(IntDbListRef il, size_t size)
{
    int i;
    for (i = 0; i < size; i++)
        il[i].i = i;

    DbListIter it;
    DbListIter_init(&it, NULL);

    for (i = 0; i < size; i++)
        DbListIter_insert(&it, &il[i].super, NULL);
}

static void printList(IntDbListRef head)
{
    DbListIter it = DbListIter_new(&head->super);
    LOGI("--------");
    while(DbListIter_next(&it))
        LOGI("%d", DbListIter_curObj(it, IntDbList)->i);
}

static void verifyList(IntDbListRef head)
{
    printList(head);
    
    DbListIter it = DbListIter_new(&head->super);
    DbListRef headList = DbListIter_head(&it);
    EXPECT_EQ(headList, &head->super);
    
    int i = 0;

    IntDbListRef current;
    while(DbListIter_next(&it))
    {
        current = DbListIter_curObj(it, IntDbList);
        EXPECT_EQ(current->i, i);
        i++;
    }
    
    DbListIter_init(&it, &head->super);
    i = -1;
    while(DbListIter_prev(&it))
    {
        current = DbListIter_curObj(it, IntDbList);
        if (i != -1)
            EXPECT_EQ(current->i, i);
        i = current->i - 1;
    }
    
    EXPECT_EQ(i, -1);
}

#define TEST_LIST_BATCH0 17
#define TEST_LIST_BATCH1 12

TEST_CASE(travel)
{
    IntDbList il[TEST_LIST_BATCH1];

    initList(il, TEST_LIST_BATCH1);
    verifyList(il);
}

TEST_CASE(insert)
{
    int i;
    DbListRef head, current;
    DbListIter it;
    IntDbList il[TEST_LIST_BATCH1];  
    
    LOGI("test insert tail");
    initNode(il, TEST_LIST_BATCH1);  
    DbListIter_init(&it, NULL);
    for (i = 0; i < TEST_LIST_BATCH1; i++)
    {
        current = DbListIter_insert(&it, &il[i].super, NULL);
        EXPECT_EQ(current, &il[i].super);
    }
    verifyList(il);
    
    LOGI("test insert head");
    initNode(il, TEST_LIST_BATCH1);
    DbListIter_init(&it, NULL);
    for (i = TEST_LIST_BATCH1 - 1; i >= 0; i--)
    {
        current = DbListIter_insert(&it, &il[i].super, &head);
        EXPECT_EQ(current, &il[i].super);
    }
    verifyList(il);
    
    LOGI("test insert middle");
    initNode(il, TEST_LIST_BATCH1);
    DbListIter_init(&it, NULL);
    DbListIter_insert(&it, &il[0].super, NULL);
    DbListIter_insert(&it, &il[TEST_LIST_BATCH1 - 1].super, NULL);
    DbListIter_next(&it);
    for (i = 1; i < TEST_LIST_BATCH1 - 1; i++)
    {
        current = DbListIter_insert(&it, &il[i].super, &head);
        EXPECT_EQ(current, &il[i].super);
        DbListIter_next(&it);
    }
    verifyList(il);
}

TEST_CASE(remove_all)
{
    IntDbList il[TEST_LIST_BATCH1];
    DbListRef head = &il[0].super, current;
    DbListIter it;
    int i;
    
    initList(il, TEST_LIST_BATCH1);
    DbListIter_init(&it, head);
    
    i = 0;
    while(DbListIter_hasNext(&it))
    {
        current = DbListIter_remove(&it, &head);
        EXPECT_EQ(current, &il[i++].super);
    }
    
    /* remove last */
    current = DbListIter_remove(&it, &head);
    EXPECT_EQ(current, &il[i++].super);
    current = DbListIter_remove(&it, &head);
    EXPECT_NULL(current);
    
    EXPECT_NULL(head);
    head = DbListIter_head(&it);
    EXPECT_NULL(head);
    current = DbListIter_current(&it);
    EXPECT_NULL(current);
}

TEST_CASE(remove_middle)
{
    IntDbList il[TEST_LIST_BATCH0];
    DbListRef head = &il[0].super, current;
    DbListIter it;
    int i;
    
    initList(il, TEST_LIST_BATCH0);
    DbListIter_init(&it, head);
    
    for (i = 0; i < TEST_LIST_BATCH0 / 4; i++)
    {
        DbListIter_next(&it);
    }
    
    for (i = TEST_LIST_BATCH0 / 4 - 1; i < TEST_LIST_BATCH0 / 2; i++)
    {
        current = DbListIter_remove(&it, &head);
        EXPECT_EQ(current, &il[i].super);
        EXPECT_EQ(head, &il[0].super);
    }
    
    for (i = TEST_LIST_BATCH0 / 4 - 1; i < TEST_LIST_BATCH0 / 2; i++)
    {
        current = DbListIter_insert(&it, &il[i].super, &head);
        DbListIter_next(&it);
    }
    
    EXPECT_EQ(head, &il[0].super);
    verifyList(il);
}

TEST_SUITE(double_list)
{
    TEST_RUN_CASE(travel);
    TEST_RUN_CASE(insert);
    TEST_RUN_CASE(remove_middle);
    TEST_RUN_CASE(remove_all);
}
