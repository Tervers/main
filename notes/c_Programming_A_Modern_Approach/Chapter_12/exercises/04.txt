/*
   Rewrite the make_empty, is_empty, and is_full functions of Section 10.2 to
       use the pointer variable top_ptr instead of the integer variable top.
*/

void make_empty(void)
{
    top_ptr = &contents[0];
}

void is_empty(void)
{
    return top_ptr == &contents[0];
}

void is_full(void)
{
    return top_ptr == contents[STACK_SIZE];
}
