#include <stdio.h>

int main(void)
{
  for(int i = 0; i < 2000000000; ++i)
  {
    int n;
    if(1 != scanf("%d", &n) || i != n)
    {
      fprintf(stderr,"bad!\n");
      return 1;
    }
  }
  return 0;
}
