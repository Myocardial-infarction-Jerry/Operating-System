do
{
    flag[i] = TRUE;
    while (flag[j])
    {
        if (turn == j)
        {
            flag[i] = false;
            while (turn == j)
                ; // do nothing
            flag[i] = TRUE;
        }
    }

    // critical section
    turn = j;
    flag[i] = FALSE;
    // remainder section
} while (TRUE);