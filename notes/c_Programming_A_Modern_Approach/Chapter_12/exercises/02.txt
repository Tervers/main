/*
   Suppose that high, low, and middle are all pointer variables of the same
       type, and that low and high point to elements of an array. Why is the
       following statement illegal, and how could it be fixed?

   middle = (low + high) / 2;
*/

You cannot add one pointer to another, but you can subtract one pointer from
    another. You can also add and subtract integers with pointers. To fix the
    statement:

    middle = (((high - low) / 2) + low);
