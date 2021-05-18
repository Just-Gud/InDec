function main()
{
    int f;
    f = 0;
    
    int ff;
    ff = 1;

    int ff_senas;
    ff_senas = ff;

    int i;
    i = 0;

    while (i < 41)
    {
        ff = ff + f;
        f = ff_senas;
        ff_senas = ff;

        i = i + 1;
    }
    print(ff);
}