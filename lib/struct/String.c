#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "String.h"
#include "String/VecString.h"

// Size of a small word that we want to keep on the stack to avoid multiple alloc/realloc calls.
// Increasing this will reduce malloc overhead, improve cache hits, but increase memory wastage.
#define CSTRING_SMALL 32
#define get_text(_input) (!(_input)->alloc_len ? (_input)->static_text : (_input)->text)

struct cstring
{
    size_t length;
    char* text;
    size_t alloc_len;
    char static_text[CSTRING_SMALL];
};


cstring* string_empty()
{
    cstring* s = malloc(sizeof(cstring));
    s->length = 0;
    s->alloc_len = 0;
    s->text = NULL;
    return s;
}


size_t string_length(cstring* str)
{
    return str->length;
}


cstring* string_append_c(cstring* input, char character)
{
    size_t new_size = input->length + 2;
    char* string;
    if (input->alloc_len == 0) {
        if (new_size <= CSTRING_SMALL) {
            string = input->static_text;
        } else {
            string = malloc(sizeof(char) * new_size);
            memcpy(string, input->static_text, input->length);
            input->alloc_len = new_size;
            input->text = string;
        }
    } else {
        string = realloc(get_text(input), sizeof(char) * new_size);
        input->alloc_len = new_size;
        input->text = string;
    }
    string[input->length] = character;
    string[input->length + 1] = 0;
    input->length += 1;
    return input;
}


cstring* string_append_ca(cstring* input, char* characters)
{
    size_t increase_by = strlen(characters) + 1;
    size_t new_size = strlen(get_text(input)) + increase_by;
    char* new_cstring = NULL;

    if (input->alloc_len == 0) {
        if (new_size <= CSTRING_SMALL) {
            new_cstring = input->static_text;
        } else {
            new_cstring = malloc(sizeof(char) * new_size);
            strcpy(new_cstring, input->static_text);
            input->alloc_len = new_size;
            input->text = new_cstring;
        }
    } else {
        new_cstring = realloc(input->text, sizeof(char) * new_size);
        input->alloc_len = new_size;
        input->text = new_cstring;
    }
    memcpy(&new_cstring[input->length], characters, increase_by);

    input->length += increase_by - 1;
    return input;
}


cstring* string_append(cstring* s1, cstring* s2)
{
    return string_append_ca(s1, get_text(s2));
}


cstring* string_new(char* characters)
{
    return string_append_ca(string_empty(), characters);
}


cstring* string_copy(cstring* initial)
{
    return string_new(get_text(initial));
}


bool string_equals(cstring* s1, cstring* s2)
{
    return !strcmp(get_text(s1), get_text(s2));
}


bool string_equals_ca(cstring* s1, char* s2)
{
    return !strcmp(get_text(s1), s2);
}


size_t string_free(cstring* string)
{
    if (string->alloc_len != 0) {
        free(string->text);
    }
    return string->length;
}


char* string_to_text(cstring* s)
{
    return get_text(s);
}


cstring* string_substr(cstring* input, size_t start, size_t end)
{
    if (start > input->length - 1 || end > input->length - 1) {
        return input;
    }

    if (end < start) {
        size_t tmp = end;
        end = start;
        start = tmp;
    }

    cstring* output = string_empty();
    for (size_t i = start; i <= end; i += 1) {
        output = string_append_c(output, get_text(input)[i]);
    }
    string_free(input);
    return output;
}


cstring* string_ltrim(cstring* input)
{
    size_t start_index = 0;
    for (; start_index < input->length; start_index += 1) {
        char c = get_text(input)[start_index];
        if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
            continue;
        }
        break;
    }

    return string_substr(input, start_index, input->length - 1);
}


cstring* string_rtrim(cstring* input)
{
    size_t end_index = input->length - 1;
    for (; end_index >= 0; end_index -= 1) {
        char c = get_text(input)[end_index];
        if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
            continue;
        }
        break;
    }

    return string_substr(input, 0, end_index);
}


cstring* string_trim(cstring* input)
{
    return string_rtrim(string_ltrim(input));
}


cstring* string_replace(cstring* input, char character, char with)
{
    cstring* new_string = string_empty();
    for (size_t i = 0; i < input->length; i++) {
        char on = get_text(input)[i];
        if (on == character) {
            new_string = string_append_c(new_string, with);
        } else {
            new_string = string_append_c(new_string, on);
        }
    }
    string_free(input);

    return new_string;
}


struct VecString* string_split(cstring* input, char separator)
{
    cstring* new = string_copy(input);
    struct VecString* array = VecString.empty();
    cstring* string = string_empty();
    for (size_t i = 0; i < new->length; i += 1) {
        char on = get_text(new)[i];
        if (on == separator && string->length > 0) {
            VecString.add(array, string);
            string = string_empty();
        } else {
            string = string_append_c(string, on);
        }
    }

    if (string->length > 0) {
        VecString.add(array, string);
    }
    string_free(string);

    return array;
}


cstring* string_join(struct VecString* array, char separator)
{
    cstring* output = string_empty();
    size_t size = VecString.size(array);
    for (size_t i = 0; i < size; i += 1) {
        output = string_append(output, VecString.get(array, i));
        if (i != size - 1) {
            output = string_append_c(output, separator);
        }
    }

    return output;
}


const struct StringLibrary String = {
    .new = string_new,
    .copy = string_copy,
    .empty = string_empty,
    .free = string_free,
    .length = string_length,
    .equals = string_equals,
    .equalsArray = string_equals_ca,
    .append = string_append,
    .appendChar = string_append_c,
    .appendArray = string_append_ca,
    .text = string_to_text,
    .trim = string_trim,
    .ltrim = string_ltrim,
    .rtrim = string_rtrim,
    .replace = string_replace,
    .split = string_split,
    .join = string_join,
};
