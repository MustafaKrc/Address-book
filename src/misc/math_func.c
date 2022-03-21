int digitCount(int number)
{
    /*
        Simple implementation of log10 in math library (defined here to prevent huge math library import)
    */
    int digit = 0;
    while (number > 0)
    {
        number /= 10;
        digit++;
    }
    return digit;
}