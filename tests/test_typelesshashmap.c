
#include <stdbool.h>
#include "minunit.h"
#include "struct/TypeLessHashMap.h"


static char* init_hashmap()
{
    struct HashMap* hm = HashMap.new(5);
    mu_assert("capacity should be 5 (1)", HashMap.capacity(hm) == 5);
    mu_assert("size should be 0 (2)", HashMap.size(hm) == 0);
    hm = HashMap.free(hm); // in the general case, this return value can be ignored
    mu_assert("hashmap should be NULL (3)", hm == NULL);
    return 0;
}


static char* add_elements()
{
    struct HashMap* hm = HashMap.new(5);
    HashMap.put(hm, "Jacques", 26);
    HashMap.put(hm, "Naika", 26);
    HashMap.put(hm, "Antoine", 25);
    mu_assert("size should be 3 (1)", HashMap.size(hm) == 3);
    HashMap.put(hm, "Felix", 24);
    mu_assert("size should be 4 (2)", HashMap.size(hm) == 4);
    HashMap.remove(hm, "Felix");
    mu_assert("size should be 3 (3)", HashMap.size(hm) == 3);
    HashMap.free(hm);
    return 0;
}


static char* get_back_element()
{
    struct HashMap* hm = HashMap.new(5);
    HashMap.put(hm, "Jacques", 26);
    HashMap.put(hm, "Naika", 26);
    HashMap.put(hm, "Felix", 24);
    mu_assert("value should be 24 (1)", HashMap.get(hm, "Felix") == 24);
    mu_assert("value should be 0 (2)", HashMap.get(hm, "Aucun") == 0);
    HashMap.free(hm);
    return 0;
}


static char* hash_collision()
{
    struct HashMap* hm = HashMap.new(5);
    HashMap.put(hm, "Jacques", 1);
    HashMap.put(hm, "Jacques", 2);
    mu_assert("size should be 1 (1)", HashMap.size(hm) == 1);
    HashMap.put(hm, "Jacques", 3);
    mu_assert("size should be 1 (2)", HashMap.size(hm) == 1);
    HashMap.put(hm, "Jacques", 4);
    mu_assert("size should be 1 (3)", HashMap.size(hm) == 1);
    mu_assert("last value should win (4)", HashMap.get(hm, "Jacques") == 4);
    HashMap.free(hm);
    return 0;
}


static char* add_remove_and_hash_collision()
{
    static char* jacques = "Jacques";
    static char* felix = "Felix";
    struct HashMap* hm = HashMap.new(5);
    HashMap.put(hm, jacques, 1);
    HashMap.put(hm, felix, 2);
    mu_assert("size should be 2 (1)", HashMap.size(hm) == 2);
    mu_assert("value should be 1 (2)", HashMap.get(hm, jacques) == 1);
    HashMap.put(hm, jacques, 3);
    HashMap.put(hm, jacques, 3);
    mu_assert("size should be 2 (3)", HashMap.size(hm) == 2);
    mu_assert("value should be 3 (4)", HashMap.get(hm, jacques) == 3);
    HashMap.remove(hm, felix);
    HashMap.remove(hm, felix);
    mu_assert("size should be 1 (5)", HashMap.size(hm) == 1);
    mu_assert("key should not exist (6)", HashMap.get(hm, felix) == 0);
    HashMap.free(hm);
    return 0;
}


struct HashMap* makeBigList(size_t buckets)
{
    struct HashMap* hm = HashMap.new(buckets);
    const int size = 6;
    const int ages[] = {
        26,
        22,
        27,
        33,
        -3,
        40,
    };
    const char* names[] = {
        "Jacques",
        "Suzanne",
        "Naika",
        "Felix",
        "Antoine",
        "Paulin",
        "Quentin",
    };
    char* buffer = calloc(64, sizeof(char));
    for (int i = 0; i < size * 100; i += 1) {
        int index = i % size;
        sprintf(buffer, "%s%08x", names[index], i);
        HashMap.put(hm, buffer, ages[index] + i);
        buffer = realloc(buffer, 64);
    }
    free(buffer);
    return hm;
}


static char* build_big_list_in_small_map()
{
    struct HashMap* hm = makeBigList(10);
    mu_assert("list should contain 600 elements (2)", HashMap.size(hm) == 600);
    HashMap.free(hm);
    return 0;
}


static char* build_big_list_in_big_map()
{
    struct HashMap* hm = makeBigList(200);
    mu_assert("list should contain 600 elements (2)", HashMap.size(hm) == 600);
    HashMap.free(hm);
    return 0;
}


static char* iterate_over_map()
{
    struct HashMap* hm = makeBigList(200);
    size_t size = HashMap.size(hm);
    size_t count = 0;
    for (size_t i = 0; i < size; i += 1) {
        mu_assert("value cannot be 0", HashMap.iter(hm, i) != 0);
        count += 1;
    }
    mu_assert("there should 600 values", count == 600);
    HashMap.free(hm);
    return 0;
}


struct HashMap* defineDict(bool rule1, int rule2)
{
    struct HashMap* hm = HashMap.new(1024);
    HashMap.put(hm, "rule1", (void*) rule1);
    HashMap.put(hm, "rule2", (void*) rule2);
    return hm;
}


void* getBackRuleFrom(struct HashMap* hm, char* section, char* rule)
{
    return HashMap.get(HashMap.get(hm, section), rule);
}


static char* typeless_mush_of_dangerous_void()
{
    struct HashMap* hm = HashMap.new(1024);

    HashMap.put(hm, "section1", defineDict(true, 58));
    HashMap.put(hm, "section2", defineDict(false, -6));

    /** get back the rule1 of each section */
    bool res1 = getBackRuleFrom(hm, "section1", "rule1");
    mu_assert("should be true (1)", res1 == true);
    res1 = getBackRuleFrom(hm, "section2", "rule1");
    mu_assert("should be false (2)", res1 == false);

    /** get back the rule2 of each section */
    int res2 = getBackRuleFrom(hm, "section1", "rule2");
    mu_assert("should be 58 (3)", res2 == 58);
    res2 = getBackRuleFrom(hm, "section2", "rule2");
    mu_assert("should be -6 (4)", res2 == -6);

    HashMap.free(HashMap.get(hm, "section1"));
    HashMap.free(HashMap.get(hm, "section2"));
    HashMap.free(hm);
    return 0;
}


static char* tests()
{
    mu_run_test(init_hashmap);
    mu_run_test(add_elements);
    mu_run_test(get_back_element);
    mu_run_test(hash_collision);
    mu_run_test(add_remove_and_hash_collision);
    mu_run_test(build_big_list_in_small_map);
    mu_run_test(build_big_list_in_big_map);
    mu_run_test(iterate_over_map);
    mu_run_test(typeless_mush_of_dangerous_void);
    return 0;
}


mu_run(tests);

