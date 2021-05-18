function main()
{
    int f;
    f = 0;
    
    int ff;
    ff = 1;

    int ff_senas;
    ff_senas = ff;

    int gylis;
    gylis = 15;

    fib(f, ff, ff_senas, gylis);
}

function fib(int f, int ff, int ff_senas, int gylis)
{
    ff = ff + f;
    f = ff_senas;
    ff_senas = ff;

    if (gylis == 0)
    {
		print("Fibo");
        print(ff);
    }
    else
    {
        gylis = gylis - 1;
        fib(f, ff, ff_senas, gylis);
    }
}