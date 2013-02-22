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
