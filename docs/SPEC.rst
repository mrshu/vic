ViC
===

Name
----

The name is derived from `ViCo` which was the name of this project previously.
Trouble is that there is another `very interesting project
<http://www.vicoapp.com/>`_ with this name so the decision has been made and 
the name was changed. 


Example
-------

    +> set x 10
    +> echo $x

    +> if '`> $x 5`' 'echo "it is higher, for sure"' 'echo "it is lower"'

This doesn't look good, does it? There is a reason why Scheme and/or Lisp 
uses brackets. It seems that ViC should too.

    +> if (> $x 5) (echo "it is higher for sure") (echo "it is lower")

Much better. 

Let us discuss the `if` function briefly. Everything between `(` and `)` or
brackets is marked as argument of this function. The first argument of this
function is the code that is first evaluated and based on the return value of
the evaluated code it evaluates the second (if the return value is true) or the
third (if the return value is false) argument.


Proposed `vic` builtin functions
--------------------------------

**set** - sets value to a variable. Can be used to set multiple values at
once. 

    +> set x 5 y 10
    +> echo $x $y
    5 10

**echo** - echoes its argumets

    +> echo "hi" there 

**if** - comparison operator. If the first argument is not 0 the second
argument is executed. Otherwise the third one is executed.
    
    +> set x 2
    +> if (< $x 4) (echo "it's smaller") (echo "it's higher")

**while** - a basic looping command

    +> set x 0
    +> while (< $x 4) (echo "smaller"; set x (+ $x 1))

Arduino related
~~~~~~~~~~~~~~~

**dr** - read from
