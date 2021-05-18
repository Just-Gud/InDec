function main()
{
    int a;
    a = 5;
    print(a);
    
    string b;
    b = "abc";
    print(b);

    int c;
    c = 10;
    c = c + 4;
    c = c - 6;
    c = c * c;
    c = c / 2;
    print(c);

    int d;
    d = 0;
    while (d < 3)
    {
        if (d == 2)
        {
            print("Loop fin.");
        }
        else
        {
            print("Loop in progress");
        }
        d = d + 1;
    }

    -- gyvenimas yra
    int e;
    e = 99;
    if (e == 5)
    {
        print("e = 5");
    }
    if (e != 5)
    {
        print("e != 5");
    }
    if (e < 5)
    {
        print("e < 5");
    }
    if (e >= 5)
    {
        print("e >= 5");
    }
}