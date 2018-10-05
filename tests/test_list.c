
#include "minunit.h"
#include "struct/List.h"


const int size = 5;

int values[] = {1, 2, 3, 4, 5};
char* key = "KEY";


static char* should_get_empty_list()
{
    struct Link* ll = List.new(values, size);
    ll = List.free(ll);
    mu_assert("list length != 0", List.length(ll) == 0);
    return 0;
}


static char* should_remove_in_the_middle()
{
    struct Link* ll = List.new(values, size);
    ll = List.freeAt(ll, 3);
    ll = List.freeAt(ll, 0);
    mu_assert("list length != 3 ", List.length(ll) == 3);
    List.free(ll);
    return 0;
}


static char* should_remove_last_element()
{
    struct Link* ll = List.new(values, size);
    ll = List.pop(ll);
    int length = List.length(ll);
    struct Link* last = List.getAt(ll, length - 1);
    mu_assert("list length isn't 4", length == 4);
    mu_assert("last element isn't 4", last->value == 4);
    List.free(ll);
    return 0;
}


static char* should_remove_first_element()
{
    struct Link* ll = List.new(values, size);
    ll = List.freeFirst(ll);
    mu_assert("list length isn't 4", List.length(ll) == 4);
    mu_assert("0th element isn't 2", List.getAt(ll, 0)->value == 2);
    List.free(ll);
    return 0;
}


static char* should_get_list_length()
{
    struct Link* ll = List.new(values, size);
    mu_assert("list length != 5", List.length(ll) == size);
    List.free(ll);
    return 0;
}


static char* should_insert_new_start()
{
    struct Link* ll = List.new(values, size);
    ll = List.insertFirst(ll, 0);
    mu_assert("list length != 6", List.length(ll) == 6);
    mu_assert("0th element isn't 0", List.getAt(ll, 0)->value == 0);
    List.free(ll);
    return 0;
}


static char* should_insert_last()
{
    struct Link* ll = List.new(values, size);
    ll = List.add(ll, key, 6);
    ll = List.add(ll, key, 6);
    mu_assert("list length != 7", List.length(ll) == 7);
    mu_assert("6th element isn't 6", List.getAt(ll, 5)->value == 6);
    List.free(ll);
    return 0;
}


static char* should_insert_in_the_middle()
{
    struct Link* ll = List.new(values, size);
    ll = List.insertAt(ll, 11, 3);
    mu_assert("list length != 6", List.length(ll) == 6);
    mu_assert("4th element isn't 11", List.getAt(ll, 3)->value == 11);
    List.free(ll);
    return 0;
}


static char* should_contain_4()
{
    struct Link* ll = List.new(values, size);
    mu_assert("list doesn't contain 4", List.contains(ll, 4));
    List.free(ll);
    return 0;
}


/**
 * If a test fails, its list won't be free-ed
 */
static char* all_tests()
{
    mu_run_test(should_remove_last_element);
    mu_run_test(should_remove_in_the_middle);
    mu_run_test(should_remove_first_element);
    mu_run_test(should_get_list_length);
    mu_run_test(should_insert_new_start);
    mu_run_test(should_insert_in_the_middle);
    mu_run_test(should_insert_last);
    mu_run_test(should_contain_4);
    mu_run_test(should_get_empty_list);
    return 0;
}


mu_run(all_tests)
