#include <stdio.h>
int main()
{
    double a=3.14, b=-2.78;
    printf("%g%+g=%g\n",a,b,a+b);
    printf("%g-(%g)=%g\n",a,b,a-b);
    printf("%g*(%g)=%g\n",a,b,a*b);
    printf("%g/(%g)=%g\n",a,b,a/b);
    return 0;
}
