#include "associative_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "generic_vector.h"


void clear_keyboard_buffer(void);
void set_word_length(int* length);
void set_guess_count(int* guesses);
void set_running_total(Bool* running_total);
Bool win_check(MY_STRING current_key);
void set_play_again(Bool* play_again);


int main(int argc, char* argv[])
{
	
	Bool running_total;
	FILE* fp;
	int noc, length, guesses;
	
	GENERIC_VECTOR str_vector_arr[30];

	for (int i = 0; i < 30; i++)
	{
		str_vector_arr[i] = generic_vector_init_default(&my_string_assignment, &my_string_destroy);
	}
	
	fp = fopen("dictionary.txt", "r");
	if (fp == NULL)
	{
		exit(-1);
	}

	MY_STRING hString = my_string_init_default();
	while (my_string_extraction(hString, fp))
	{
			generic_vector_push_back(str_vector_arr[my_string_get_size(hString) - 1], (ITEM)hString);
	}
	
	my_string_destroy(&hString);
	

	
	fclose(fp);

	Bool play_again = TRUE;
	GENERIC_VECTOR Working_list;//
	MY_STRING hGuessed;
	MY_STRING hCurrent_family;
	MY_STRING hNext_family;
	ASSOCIATIVE_ARRAY hA_array;
	
    while(play_again)
	{
		char letter, enter_check;
		set_word_length(&length);
		set_guess_count(&guesses);
		set_running_total(&running_total);
		Working_list = generic_vector_init_default(&my_string_assignment, &my_string_destroy);

		for (int i = 0; i < generic_vector_get_size(str_vector_arr[length - 1]); i++)
		{
			generic_vector_push_back(Working_list, generic_vector_at(str_vector_arr[length - 1], i));
		}
		hCurrent_family = my_string_init_default_family(length);
		hGuessed = my_string_init_default();
		hNext_family = my_string_init_c_string("");
		my_string_assignment((ITEM*)&hNext_family, (ITEM)hCurrent_family);
		hA_array = associaive_array_init_default();


		while (guesses > 0)
		{
			printf("You have %d guesses left.\n", guesses);
			printf("You have previously guessed the following letters:\n");
			output_previous_guesses(hGuessed);
			printf("Please enter your guess: ");
			noc = scanf("%c%c", &letter, &enter_check);
			while (noc != 2 || !isalpha(letter) || enter_check != '\n')
			{
				clear_keyboard_buffer();
				printf("Please enter your next guess: ");
				noc = scanf("%c%c", &letter, &enter_check);
			}
			my_string_push_back(hGuessed, letter);
		
			for (int i = generic_vector_get_size(Working_list); i > 0; i--)
			{
				get_word_key_value(hCurrent_family, hNext_family, generic_vector_at(Working_list, i - 1), letter);
				associate_array_insert_word(hA_array, hNext_family, (MY_STRING)generic_vector_at(Working_list, i - 1));
				generic_vector_pop_back(Working_list);
				
			}
		

			if (running_total)
			{
				printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\n");
				print_families(hA_array);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}

			if (set_best_family(hA_array, hCurrent_family) == 0)
			{
				printf("\n");
				printf("I'm sorry, there were no %c's in the word;)\n", letter);
				guesses--;
			}

			printf("Word: ");
			my_string_insertion(hCurrent_family, stdout);
			printf("\n");


			if (running_total)
			{
				printf("The computer has %d possibilities remaining.\n", get_word_count_of_key(hA_array, hCurrent_family));
			}

			for (int i = 0; i < get_word_count_of_key(hA_array, hCurrent_family); i++)
			{
				generic_vector_push_back(Working_list , associative_array_key_data_at_index(hA_array, hCurrent_family, i));
			}
			printf("\n");
			
			if (guesses == 0)
			{
				printf("You lose. The word was\n");
				my_string_insertion((MY_STRING)associative_array_key_data_at_index(hA_array, hCurrent_family, 0), stdout);
				printf("\n");
			}
			if (win_check(hCurrent_family))
			{
				printf("Congrats on beating the cheating hangman!\n");
				break;
			}
			destroy_associative_array(&hA_array, TRUE);


		}
		generic_vector_destroy(&Working_list);
		my_string_destroy(&hGuessed);
		my_string_destroy(&hCurrent_family);
		my_string_destroy(&hNext_family);
		destroy_associative_array(&hA_array, FALSE);
		length = 0;
		running_total = FALSE;
		guesses = 0;
		set_play_again(&play_again);
	}
	for (int i = 0; i < 30; i++)
	{
		generic_vector_destroy(&str_vector_arr[i]);
	}
	return 0;
}

void set_word_length(int *length)
{
	int noc;
	printf("Please enter a word length between 2 and 29 (inclusive): ");
	noc = scanf("%d", length);
	clear_keyboard_buffer();
	while (noc != 1 || *length > 29 || *length < 2)
	{
		printf("Please enter a word length between 2 and 29 (inclusive): ");
		noc = scanf("%d", length);
		clear_keyboard_buffer();
	}
}

void set_guess_count(int* guesses)
{
	int noc;
	printf("Please enter a positive amount of guesses: ");
	noc = scanf("%d", guesses);
	clear_keyboard_buffer();
	while (noc != 1 || *guesses <= 0)
	{
		printf("Please enter a positive amount of guesses: ");
		noc = scanf("%d", guesses);
		clear_keyboard_buffer();
	}
}

void set_play_again(Bool* play_again)
{
	int noc;
	char letter;
	printf("Would you like to play again? [Y/N] :  ");
	noc = scanf("%c", &letter);
	clear_keyboard_buffer();
	while (noc != 1 || (letter != 'Y' && letter != 'N'))
	{
		printf("Would you like to play again? [Y/N] :  ");
		noc = scanf("%c", &letter);
		clear_keyboard_buffer();
	}
	*play_again = (letter == 'Y') ? TRUE : FALSE;
}

void set_running_total(Bool* running_total)
{
	int noc;
	char letter;
	printf("Would you like a running total of words remaining in the word list? [Y/N] :  ");
	noc = scanf("%c", &letter);
	clear_keyboard_buffer();
	while (noc != 1 || (letter != 'Y' && letter != 'N'))
	{
		printf("Would you like a running total of words remaining in the word list? [Y/N] :  ");
		noc = scanf("%c", &letter);
		clear_keyboard_buffer();
	}
	*running_total = (letter == 'Y') ? TRUE : FALSE;
}

void clear_keyboard_buffer(void)
{
	char c;
	int noc;
	noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
	{
		noc = scanf("%c", &c);
	}

}

Bool win_check(MY_STRING current_key)
{
	for (int i = 0; i < my_string_get_size(current_key); i++)
	{
		if (my_string_at(current_key, i)[0] == '-')
			return FALSE;
	}
	return TRUE;
}
