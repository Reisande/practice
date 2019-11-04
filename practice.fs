( expressions are commented out with the backslash )

5 4 + .

( every value is pushed onto the stack. Whenever an operation is put onto the stack
  The compiler either decides to ignore it, like with parens, or does the operation
  and pushes the return value/s onto the stack )

( swap reverses the top two values on the stack )

5 4 swap - . cr \ becomes - 1

( dup duplicates the top value on the stack )

5 dup * . cr

( over duplicates the second to last element on the stack )

4 5 over * . .  cr

( drop discards numbers )

4 3 drop . cr

( rot takes the third value from the top and pushes it on top of the stack )
1 2 3 rot rot . . . cr \ becomes 2 1 3

( functions are called words in forth, and take their arguments from the stack
  and push the return values on to the stack )

: *. * . cr ;

3 8 *.

( since forth is concatenative, the results of calls to functions are implicitly
  passed as arguments to the next function, kind of like piping in ocaml/f# )

( in forth, everything either is or will be a word )

( string contents can be displayed through .( ) 

.( Hello World! ) cr

( variables are defined in the same way as words, and actually are words )

variable x 

( values are assigned by treating them as an operation which pops a value
  off the stack and takes that value, like so )

5 x !

( and the value is displayed by pushing the variable onto the stack again
  and using the '@' key, which pushes the stored value onto the stack )

x @ . cr

( an existing primitive is '?', which is syntactic sugar for "@ ." )

( forth has the following built in variables: TODO: fill in
- base: ?
- >in )

( a cell is a space which the number takes up, basically just the stack node,
  but takes care of alignment for you )

( constants can be defined by using the 'constant' keyword )

6 constant six

.( six is stored as: ) six . cr 

( defines star as the two operations 42 and emit )
: star 42 emit cr ;

star 

( here are the following built in constants: TODO: fill in
- bl: ?
- true: obv
- pad: ?
- false: obv
- tib: ? )

( booleans also exist. Like everything else, they are put onto the stack )

variable var
4 var !
var @ 5 > . cr
var @ 2 > . cr
var @ 5 < . cr

( like C, false is a 0, true is a non zero )

\ loops:

\ The following loop is equivalent to the C code:
\ unsigned int i;
\ for(i = 0; i < 11; i ++) {
\   prinf("%d", i);
\ }

: test_loop
	11 1 do i . loop
	cr
;

( In this case, the 11 is the limit, the 1 is the initial value, and the increment
  occurs in 'loop' )

test_loop

( The same general construct can be repeated with '?do'. '?do' to 'do' is the same
  as 'do while' to 'while' )

: test_?loop
	0 0 ?do i . loop
	.( ran ? loop )
;

cr

( the increment can be changed by using either +loop or -loop )

: test_loop_reverse
	1 11 do i . 2 -loop
	cr
;

test_loop_reverse

( This loop decrements by 2 each iteration )

( The following loop prints out the values from -1 to -10 )

: test_loop_negative
	11 1
	do i -1 * . loop
	cr
;

test_loop_negative

( while loops have the general structure : begin <cond> while <body> repeat )

: fib 0 1
	begin
		dup >r rot dup r> >
	while
			rot rot dup rot + dup .
	repeat
	drop drop drop
;

20 fib
cr


( repeat until exists, it is literally just do while )

( infinite loops can be made by writing begin <body> again )

( .r allows you to right justify columns )

: test_loop_right_justified
	12000 1 do i 4 .r cr i +loop
	cr
;

test_loop_right_justified 


