#include <check.h>

#include <ch_list.h>


START_TEST(test_ch_list_init)
{
    ch_list_t list, list2;
    int data = 3;
    ch_list_init_empty(&list);
    ck_assert(list.head == NULL);
    ck_assert(list.tail == NULL);
    ch_list_free(&list);

    ch_list_init(&list2, &data);
    ck_assert(list2.head == list2.tail);
    ck_assert(list2.head->prev == NULL);
    ck_assert(list2.head->next == NULL);
    ck_assert(list2.head->data == &data);
    ch_list_free(&list2);
}
END_TEST


START_TEST(test_ch_list_append)
{
    ch_list_t list;
    int data1 = 1;
    int data2 = 2;

    ch_list_init(&list, &data1);
    ch_list_append(&list, &data2);
    ch_list_append(&list, &data1);

    ck_assert(list.head->data == &data1);
    ck_assert(list.head->next->data == &data2);
    ck_assert(list.head->next->next->data == &data1);

    ck_assert(list.tail->data == &data1);
    ck_assert(list.tail->prev->data == &data2);
    ck_assert(list.tail->prev->prev->data == &data1);

    ck_assert(list.head == list.tail->prev->prev);
    ck_assert(list.head->next == list.tail->prev);
    ck_assert(list.head->next->next == list.tail);

    ch_list_free(&list);
}
END_TEST


int main(int argc, const char *argv[])
{
    Suite *s = suite_create("core");

    TCase *ch_list_test_case = tcase_create("ch_list");
    tcase_add_test(ch_list_test_case, test_ch_list_init);
    tcase_add_test(ch_list_test_case, test_ch_list_append);

    /* Add test cases here */
    suite_add_tcase(s, ch_list_test_case);

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    srunner_free(sr);
    return 0;
}