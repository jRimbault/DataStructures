
#include "minunit.h"
#include "struct/List.h"


struct List* initTestingList()
{
    struct List* list = List.new();
    for (int i = 0; i < 5; i += 1) {
        List.add(list, Node.new("", i + 1));
    }
    return list;
}


static char* null_list()
{
    mu_assert("there should not be any list", List.length(NULL) == 0);
    return 0;
}


static char* init_empty_list()
{
    struct List* list = List.new();
    mu_assert("list length should be 0", List.length(list) == 0);
    List.free(list);
    return 0;
}


static char* adding_element()
{
    struct List* list = List.new();
    List.add(list, Node.new("", 1));
    mu_assert("list length should be 1", List.length(list) == 1);
    List.free(list);
    return 0;
}


static char* getting_list_length()
{
    struct List* list = initTestingList();
    mu_assert("list length should be 5", List.length(list) == 5);
    List.free(list);
    return 0;
}


static char* getting_one_particular_element()
{
    struct List* list = initTestingList();
    List.add(list, Node.new("jacques", 26));
    struct Node* nothing = List.get(list, "keyDoesNotExists");
    struct Node* jacques = List.get(list, "jacques");
    mu_assert("list length should be 6", List.length(list) == 6);
    mu_assert("node value should be 2", Node.value(nothing) == 0);
    mu_assert("node value should be 26", Node.value(jacques) == 26);
    List.free(list);
    return 0;
}


static char* iteration_over_list()
{
    struct List* list = initTestingList();
    size_t len = List.length(list);
    for (size_t i = 0; i < len; i += 1) {
        mu_assert("value should not be 1", Node.value(List.iter(list, i)) != 0);
    }
    List.free(list);
    return 0;
}


static char* list_should_contain()
{
    struct List* list = initTestingList();
    List.add(list, Node.new("jacques", 26));
    mu_assert("list length should be 6", List.length(list) == 6);
    mu_assert("list should contains key: 'jacques'", List.contains(list, "jacques"));
    List.free(list);
    return 0;
}


static char* removing_elements()
{
    struct List* list = List.new();
    List.add(list, Node.new("jacques", 26));
    List.add(list, Node.new("felix", 27));
    List.add(list, Node.new("naika", 28));
    List.add(list, Node.new("suzanne", 29));
    mu_assert("list length should be 4", List.length(list) == 4);
    mu_assert("key 'jacques' should be 26", Node.value(List.get(list, "jacques")) == 26);
    List.remove(list, "jacques");
    mu_assert("list length should be 3", List.length(list) == 3);
    mu_assert("list should not contain 'jacques'", List.contains(list, "jacques") == false);
    List.free(list);
    return 0;
}


static char* all_tests()
{
    mu_run_test(null_list);
    mu_run_test(init_empty_list);
    mu_run_test(adding_element);
    mu_run_test(getting_list_length);
    mu_run_test(getting_one_particular_element);
    mu_run_test(iteration_over_list);
    mu_run_test(list_should_contain);
    mu_run_test(removing_elements);
    return 0;
}


mu_run(all_tests)

