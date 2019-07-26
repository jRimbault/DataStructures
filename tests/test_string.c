
#include "minunit.h"
#include "struct/String.h"
#include "struct/String/VecString.h"


static char* string_is_empty()
{
    cstring* str = String.empty();
    mu_assert("length should be zero", String.length(str) == 0);
    return 0;
}


static char* strings_should_be_equals()
{
    cstring* s1 = String.new("thing");
    cstring* s2 = String.new("thing");
    mu_assert("strings should be equals", String.equals(s1, s2));
    return 0;
}


static char* strings_should_not_be_equals()
{
    cstring* s1 = String.new("thing1thing1thing1thing1thing1thing1thing1thing1");
    cstring* s2 = String.new("thing2");
    mu_assert("strings should not be equals", !String.equals(s1, s2));
    String.free(s1);
    return 0;
}


static char* strings_should_be_equal_after_being_trimmed()
{
    cstring* s1 = String.new("  to trim   ");
    cstring* s2 = String.new(" \tto trim\n");
    mu_assert("strings should not be equals before trimming", !String.equals(s1, s2));
    cstring* s1t = String.trim(s1);
    cstring* s2t = String.trim(s2);
    mu_assert("strings should be equals after trimming", String.equals(s1t, s2t));
    return 0;
}


static char* should_replace_one_char()
{
    cstring* old = String.new("a syringe");
    cstring* new = String.replace(
        String.replace(
            String.replace(
                old,
                'a', 'A'
            ),
            'y', 't'
        ),
        'e', '.'
    );
    mu_assert("strings should not be equals", !String.equals(new, old));
    mu_assert("strings should be equals", String.equals(new, String.new("A string.")));
    return 0;
}


static char* should_make_a_list_of_string()
{
    struct VecString* list = VecString.empty();
    cstring* word = String.new("word");
    VecString.add(list, String.copy(word));
    VecString.add(list, String.copy(word));
    size_t i = 0;
    for (; i < VecString.size(list); i += 1) {
        mu_assert("words should be equals", String.equals(VecString.get(list, i), word));
    }
    mu_assert("", i > 0);
    mu_assert("", i == VecString.size(list));
    return 0;
}


static char* should_split_a_string_into_a_list()
{
    cstring* sentence = String.new("This is my little sentence");
    struct VecString* words = String.split(sentence, ' ');
    mu_assert("should be 'This'", String.equals(VecString.get(words, 0), String.new("This")));
    mu_assert("should be 'is'", String.equals(VecString.get(words, 1), String.new("is")));
    mu_assert("should be 'my'", String.equals(VecString.get(words, 2), String.new("my")));
    mu_assert("should be 'little'", String.equals(VecString.get(words, 3), String.new("little")));
    mu_assert("should be 'sentence'", String.equals(VecString.get(words, 4), String.new("sentence")));
    return 0;
}


static char* should_join_a_list_into_a_string()
{
    cstring* sentence = String.new("This is my little sentence");
    struct VecString* words = String.split(sentence, ' ');
    cstring* new = String.join(words, '-');
    cstring* rep = String.replace(sentence, ' ', '-');
    mu_assert("should be equals", String.equals(new, rep));
    return 0;
}


static char* all_tests()
{
    mu_run_test(string_is_empty);
    mu_run_test(strings_should_be_equals);
    mu_run_test(strings_should_not_be_equals);
    mu_run_test(strings_should_be_equal_after_being_trimmed);
    mu_run_test(should_replace_one_char);
    mu_run_test(should_make_a_list_of_string);
    mu_run_test(should_split_a_string_into_a_list);
    mu_run_test(should_join_a_list_into_a_string);
    return 0;
}


mu_run(all_tests)

