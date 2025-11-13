/*** CHAPTER                         10                          EXERCISES ***/


1. The following program outline shows only function definitions and variable
    declarations.

    int a;

    void f(int b)
    {
        int c;
    }

    void g(void)
    {
        int d;
        {
            int e;
        }
    }

    int main(void)
    {
        int f;
    }

    For each of the following scopes, list all variable and parameter names
     visible in that scope:

    (a) The f function
    (b) The g function
    (c) The block in which e is declared
    (d) the main function

(a) parameter b. variables a, c.
(b) variables a, d, e  //e is only available within its block
(c) e is declared within the block after d is declared in the g function //I
        //misread the question. variable visible are e, d, a
(d) parameter b. variables a, f, c //just a, f


2. The following program outline shows only function definitions and variable
    declarations.

    int b, c;

    void f(void)
    {
        int b, d;
    }

    void g(int a)
    {
        int c;
        {
            int a, d;
        }
    }

    int main(void)
    {
        int c, d;
    }

    For each of the following scopes, list all variable and parameter names
     visible in that scope. If there's more than one variable or parameter with
     the same name, indicate which one is visible.

    (a) The f function
    (b) The g function
    (c) The block in which a and d are declared
    (d) The main function

(a) the b from f function has visibility, c, d
(b) parameter a has visibility throughout the g function, b, the c from the g
    function has visibility, d only has visibility within its block
(c) a, b, the c from function g has visibility, d
(d) b, c from main has visibility, d


3. 
