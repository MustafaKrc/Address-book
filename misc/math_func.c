int digitCount(int number)
{
    int digit = 0;
    while (number > 0)
    {
        number /= 10;
        digit++;
    }
    return digit;
}