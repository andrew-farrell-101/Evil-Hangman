#include <stdio.h>
#include "bit_flags.h"
#include "status.h"

int main(int argc, char *argv[])
{
	BIT_FLAGS hBits = bit_flags_init_number_of_bits(10);
	printf("The capacity is %d\n", bit_flags_get_capacity(hBits));
	printf("The size is %d\n", bit_flags_get_size(hBits));
	bit_flags_set_flag(hBits, 32);
	printf("Pos 32 is set to %d\n", bit_flags_check_flag(hBits, 32));
	printf("The capacity is %d\n", bit_flags_get_capacity(hBits));
	printf("The size is %d\n", bit_flags_get_size(hBits));
	bit_flags_set_flag(hBits, 200);
	printf("Pos 200 is set to %d\n", bit_flags_check_flag(hBits, 200));
	printf("The capacity is %d\n", bit_flags_get_capacity(hBits));
	printf("The size is %d\n", bit_flags_get_size(hBits));
	bit_flags_unset_flag(hBits, 80);
	printf("Pos 80 is set to %d\n", bit_flags_check_flag(hBits, 80));
	bit_flags_unset_flag(hBits, 200);
	printf("Pos 200 is set to %d\n", bit_flags_check_flag(hBits, 200));
	bit_flags_unset_flag(hBits, 300);
	printf("The capacity is %d\n", bit_flags_get_capacity(hBits));
	printf("The size is %d\n", bit_flags_get_size(hBits));
	printf("Pos 80 is set to %d\n", bit_flags_check_flag(hBits, 80));
	bit_flags_unset_flag(hBits, 32);
	printf("Pos 32 is set to %d\n", bit_flags_check_flag(hBits, 32));
	bit_flags_destroy(&hBits);

	return 0;
}