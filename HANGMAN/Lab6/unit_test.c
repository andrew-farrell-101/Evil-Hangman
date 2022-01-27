#include <stdio.h>
#include "unit_test.h"
int main(int argc, char* argv[])
{
	//This code makes me uncomfortable
	Status(*tests[])(char*, int) =
	{
  test_init_c_string_returns_nonNULL,
  test_get_size_on_init_default_returns_0,
  test_get_capacity_on_init_default_returns_7,
  test_init_default_returns_nonNULL,
  test_my_string_destroy_sets_string_to_null,
  test_my_string_at_end_of_c_string,
  test_get_size_of_3_letter_c_string,
  test_get_capcity_of_3_letter_c_string,
  test_get_size_after_pop_back_on_c_string,
  test_get_size_after_push_back_on_c_string,
  test_c_string_stays_null_terminated_after_push_back,
  test_init_empty_c_string,
  test_capacity_empty_c_string,
  test_size_empty_c_string,
  test_popping_empty_c_string_returns_failure,
  test_popping_empty_string_returns_failure,
  test_get_last_letter_after_pop_back_on_c_string,
  test_c_string_remains_null_terminated_after_pop_back,
  test_empty_string_returns_true_on_empty_c_string,
  test_empty_string_returns_false_on_non_empty_c_string,
  test_string_concat_maintains_null_terminator_on_resulting_string,
  test_string_concat_has_correct_result_size,
  test_string_concat_creates_correct_string,
  test_string_returns_true_on_identical_strings,
  test_string_returns_false_on_different_strings,
  test_my_string_assignment_creates_deep_copy,
  test_array_of_assertion_copies
	};
	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[500];
	int success_count = 0;
	int failure_count = 0;
	for (i = 0; i < number_of_functions; i++)
	{
		if (tests[i](buffer, 500) == FAILURE)
		{
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else
		{
			// printf("PASS: Test %d passed\n", i);
			// printf("\t%s\n", buffer);
			success_count++;
		}
	}
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count,
		number_of_functions, failure_count, number_of_functions);
	return 0;
}
