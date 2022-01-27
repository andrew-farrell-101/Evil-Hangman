#include "unit_test.h"
#include <stdlib.h>
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (hString == NULL)
	{
		strncpy(buffer, "test_init_default_returns_nonNULL\n"
			"my_string_init_default returns NULL", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if (my_string_get_size(hString) != 0)
	{
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
			"Did not receive 0 from get_size after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
			, length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

Status test_get_capacity_on_init_default_returns_7(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if (my_string_get_capacity(hString) != 7)
	{
		status = FAILURE;
		printf("Expected a capacity of 7 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
			"Did not receive 7 from get_capacity after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
			, length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

Status test_init_c_string_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("ipsum lorem");
	if (hString == NULL)
	{
		strncpy(buffer, "test_init_c_string_returns_nonNULL\n"
			"init_c_string returns null", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_init_c_string_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_my_string_destroy_sets_string_to_null(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("ipsum lorem");
	my_string_destroy((Item*)&hString);
	if (hString != NULL)
	{
		strncpy(buffer, "test_my_string_destroy_sets_string_to_null\n"
			"String object not set to null", length);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "\ttest_my_string_destroy_sets_string_to_null\n", length);
		return SUCCESS;
	}
}


Status test_my_string_at_end_of_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("ipsum lorem");
	if (my_string_at( hString, (my_string_get_size(hString) - 1))[0] != 'm')
	{
		strncpy(buffer, "test_my_string_at_end_of_c_string\n"
			"my_string_at returns wrong letter with end of string", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_my_string_at_end_of_c_string\n", length);
		return SUCCESS;
	}

}
Status test_get_size_of_3_letter_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("The");
	if (my_string_get_size(hString) != 3)
	{
		strncpy(buffer, "test_get_size_of_3_letter_c_string\n"
			"Incorrect size", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_get_size_of_3_letter_c_string\n", length);
		return SUCCESS;
	}
}

Status test_get_capcity_of_3_letter_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("The");
	if (my_string_get_capacity(hString) != 4)
	{
		
		strncpy(buffer, "test_get_capcity_of_3_letter_c_string\n"
			"Incorrect capacity", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_get_capcity_of_3_letter_c_string\n", length);
		return SUCCESS;
	}
}

Status test_get_size_after_pop_back_on_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("The");
	my_string_pop_back(hString);
	if (my_string_get_size(hString) != 2)
	{
		strncpy(buffer, "test_get_size_after_pop_back_on_c_string\n"
			"Incorrect size", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_get_size_after_pop_back_on_c_string", length);
		return SUCCESS;
	}
}

Status test_get_size_after_push_back_on_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("The");
	my_string_push_back(hString,'X');
	if (my_string_get_size(hString) != 4)
	{
		strncpy(buffer, "test_get_size_after_push_back_on_c_string\n"
			"Incorrect size", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_get_size_after_push_back_on_c_string", length);
		return SUCCESS;
	}
}

Status test_c_string_stays_null_terminated_after_push_back(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("Th");
	my_string_push_back(hString, 'e');
	if (my_string_at(hString, my_string_get_size(hString))[0] != '\0')
	{
		strncpy(buffer, "test_c_string_stays_null_terminated_after_push_back\n"
			"C string not null terminated after push back operation", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_c_string_stays_null_terminated_after_push_back", length);
		return SUCCESS;
	}
}

Status test_init_empty_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("");
	if (!hString)
	{
		strncpy(buffer, "test_init_empty_c_string"
			"Could not create empty C string", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_init_empty_c_string", length);
		return SUCCESS;
	}
}

Status test_capacity_empty_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("");
	if (my_string_get_capacity(hString) != 1)
	{
		strncpy(buffer, "test_capacity_empty_c_string"
			"Incorrect capacity", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_capacity_empty_c_string", length);
		return SUCCESS;
	}
}

Status test_size_empty_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("");
	if (my_string_get_size(hString) != 0)
	{
		strncpy(buffer, "test_size_empty_c_string\n"
			"Incorrect size", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_size_empty_c_string", length);
		return SUCCESS;
	}
}

Status test_popping_empty_c_string_returns_failure(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("");
	if (my_string_pop_back(hString))
	{
		strncpy(buffer, "popping_empty_c_string_returns_failure\n"
			"pop operation failed to return failure", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\tpopping_empty_c_string_returns_failure", length);
		return SUCCESS;
	}
}

Status test_popping_empty_string_returns_failure(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (my_string_pop_back(hString))
	{
		strncpy(buffer, "popping_empty_string_returns_failure\n"
			"pop operation failed to return failure", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\tpopping_empty_string_returns_failure", length);
		return SUCCESS;
	}
}
Status test_get_last_letter_after_pop_back_on_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("The");
	my_string_pop_back(hString);
	if (my_string_at(hString, my_string_get_size(hString)-1)[0] != 'h')
	{
		strncpy(buffer, "test_get_last_letter_after_pop_back_on_c_string\n"
			"Letter at string[string size - 1] is not the correct letter. ", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_get_last_letter_after_pop_back_on_c_string", length);
		return SUCCESS;
	}
}
Status test_c_string_remains_null_terminated_after_pop_back(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("The");
	my_string_pop_back(hString);
	if (my_string_at(hString, my_string_get_size(hString))[0] != '\0')
	{
		strncpy(buffer, "test_c_string_remains_null_terminated_after_pop_back\n"
			"C string is not correctly terminated after pop back", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_c_string_remains_null_terminated_after_pop_back", length);
		return SUCCESS;
	}
}
////////////////////////////////////////////////
Status test_empty_string_returns_true_on_empty_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("");
	if (!my_string_empty(hString))
	{
		strncpy(buffer, "test_empty_string_returns_true_on_empty_c_string\n"
			"detecting non-empty c string", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_empty_string_returns_true_on_empty_c_string", length);
		return SUCCESS;
	}
}

Status test_empty_string_returns_false_on_non_empty_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("The");
	if (my_string_empty(hString))
	{
		strncpy(buffer, "test_empty_string_returns_false_on_non_empty_c_string\n"
			"detecting empty c string", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "\ttest_empty_string_returns_false_on_non_empty_c_string", length);
		return SUCCESS;
	}
}

Status test_string_concat_maintains_null_terminator_on_resulting_string(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	hString1 = my_string_init_c_string("The");
	MY_STRING hString2 = NULL;
	hString2 = my_string_init_c_string("ehT");
	my_string_concat(hString1, hString2);
	if (my_string_at(hString1, my_string_get_size(hString1))[0] != '\0')
	{
		strncpy(buffer, "test_string_concat_maintains_null_terminator_on_resulting_string\n"
			"Resulting string does not remain null terminated after concatonation", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString1);
		my_string_destroy((Item*)&hString2);
		strncpy(buffer, "\ttest_string_concat_maintains_null_terminator_on_resulting_string", length);
		return SUCCESS;
	}
}

Status test_string_concat_has_correct_result_size(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	hString1 = my_string_init_c_string("The");
	MY_STRING hString2 = NULL;
	hString2 = my_string_init_c_string("ehT");
	my_string_concat(hString1, hString2);
	if (my_string_get_size(hString1) != 6)
	{
		strncpy(buffer, "test_string_concat_has_correct_result_size\n"
			"Resulting string size is incorrect", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString1);
		my_string_destroy((Item*)&hString2);
		strncpy(buffer, "\ttest_string_concat_has_correct_result_size", length);
		return SUCCESS;
	}
}

Status test_string_concat_creates_correct_string(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	hString1 = my_string_init_c_string("The");
	MY_STRING hString2 = NULL;
	hString2 = my_string_init_c_string("ehT");
	MY_STRING hString3 = NULL;
	hString3 = my_string_init_c_string("TheehT");
	my_string_concat(hString1, hString2);
	if (my_string_compare(hString1, hString3))
	{
		strncpy(buffer, "test_string_concat_creates_correct_string\n"
			"Concat does not produce expected output", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString1);
		my_string_destroy((Item*)&hString2);
		my_string_destroy((Item*)&hString3);
		strncpy(buffer, "\ttest_string_concat_creates_correct_string", length);
		return SUCCESS;
	}
}

Status test_string_returns_true_on_identical_strings(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	hString1 = my_string_init_c_string("The");
	MY_STRING hString2 = NULL;
	hString2 = my_string_init_c_string("The");
	if (my_string_compare(hString1,hString2))
	{
		strncpy(buffer, "test_string_returns_true_on_identical_strings\n"
			"String compare does not return true on identical strings", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString1);
		my_string_destroy((Item*)&hString2);
		strncpy(buffer, "\ttest_string_returns_true_on_identical_strings", length);
		return SUCCESS;
	}
}

Status test_string_returns_false_on_different_strings(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	hString1 = my_string_init_c_string("");
	MY_STRING hString2 = NULL;
	hString2 = my_string_init_c_string("Oranges");
	if (!my_string_compare(hString1, hString2))
	{
		strncpy(buffer, "test_string_returns_true_on_identical_strings\n"
			"String compare does not return true on identical strings", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString1);
		my_string_destroy((Item*)&hString2);
		strncpy(buffer, "\ttest_string_returns_true_on_identical_strings", length);
		return SUCCESS;
	}
}

Status test_my_string_assignment_creates_deep_copy(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	hString2 = my_string_init_c_string("Oranges");
	my_string_assignment((Item*)&hString1, (Item)hString2);
	if (my_string_compare(hString1, hString2))
	{
		strncpy(buffer, "test_string_returns_true_on_identical_strings\n"
			"String compare does not return true on identical strings", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString1);
		my_string_destroy((Item*)&hString2);
		strncpy(buffer, "\ttest_string_returns_true_on_identical_strings", length);
		return SUCCESS;
	}
}

Status test_array_of_assertion_copies(char* buffer, int length)
{
	MY_STRING strings[100] = { NULL };
	strings[0] = my_string_init_c_string("COPY ME!");
	for (int i = 1; i < 100; i++)
	{
		my_string_assignment((Item*)&strings[i], (Item)strings[i - 1]);
		if (strings[i] == NULL)
		{
			return FAILURE;
		}

	}
        // 
	for (int i = 0; i < 100; i++)
	{
		my_string_insertion(strings[i], stdout);
		fprintf(stdout, "\n");
		//my_string_destroy(&strings[i]);
	}
	//
	printf("Memory leak enabled\n");
	return SUCCESS;
}
