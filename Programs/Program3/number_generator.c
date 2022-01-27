#include <stdio.h>
#include <stdlib.h>

const unsigned int MAX = 2000000001;

int main(void)
{
    for (unsigned int i = 0; i < 10; ++i)
    {
        printf("%u\n", (2 * rand() * rand()) % MAX);
    }
    return 0;
}
