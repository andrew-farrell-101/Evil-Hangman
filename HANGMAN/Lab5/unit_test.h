#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_init_c_string_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_my_string_destroy_sets_string_to_null(char* buffer, int length);
Status test_my_string_at_end_of_c_string(char* buffer, int length);
Status test_get_size_of_3_letter_c_string(char* buffer, int length);
Status test_get_capcity_of_3_letter_c_string(char* buffer, int length);
Status test_get_size_after_pop_back_on_c_string(char* buffer, int length);
Status test_get_size_after_push_back_on_c_string(char* buffer, int length);
Status test_c_string_stays_null_terminated_after_push_back(char* buffer, int length);
Status test_init_empty_c_string(char* buffer, int length);
Status test_capacity_empty_c_string(char* buffer, int length);
Status test_size_empty_c_string(char* buffer, int length);
Status test_popping_empty_c_string_returns_failure(char* buffer, int length);
Status test_popping_empty_string_returns_failure(char* buffer, int length);
Status test_get_last_letter_after_pop_back_on_c_string(char* buffer, int length);
Status test_c_string_remains_null_terminated_after_pop_back(char* buffer, int length);
Status test_empty_string_returns_true_on_empty_c_string(char* buffer, int length);
Status test_empty_string_returns_false_on_non_empty_c_string(char* buffer, int length);
Status test_string_concat_maintains_null_terminator_on_resulting_string(char* buffer, int length);
Status test_string_concat_has_correct_result_size(char* buffer, int length); 
Status test_string_concat_creates_correct_string(char* buffer, int length);
Status test_string_returns_true_on_identical_strings(char* buffer, int length);
Status test_string_returns_false_on_different_strings(char* buffer, int length);
#endif
