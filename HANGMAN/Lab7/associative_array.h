#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H
//Need to be able to add a key/value pair to the dictionry
#include "my_string.h"
typedef void* ASSOCIATIVE_ARRAY;

ASSOCIATIVE_ARRAY associaive_array_init_default(void);
void associate_array_insert_word(ASSOCIATIVE_ARRAY hA_array, MY_STRING hString_key, MY_STRING hString);
void destroy_associative_array(ASSOCIATIVE_ARRAY* phA_array, Bool partial);
void print_families(ASSOCIATIVE_ARRAY hA_array);
int set_best_family(ASSOCIATIVE_ARRAY hA_array, MY_STRING hCurrent_family);
int get_word_count_of_key(ASSOCIATIVE_ARRAY hA_array, MY_STRING hCurrent_family);
ITEM associative_array_key_data_at_index(ASSOCIATIVE_ARRAY hA_array, MY_STRING hKey, int index);
#endif
