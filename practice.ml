(* The problem with mutability is that it breaks referential transparency 

   referential transparency is the act of propagating a value for an expression,
   Which is not always possible in imperative languages due to side-effects

   This is also a problem because machines do not have one, unified state,
   they are comprised of multiple, not necessarily unrelated states

   Immutability frees the programmer from having to concern about the 
   mutability of state, and allows for referential transparency, which makes
   computations considerably faster

   There is two types of equality testing, physical (==, !=)
   and structural (=, <>). physical should be used for comparison of 
   values with the same reference/associated state, structural should
   be used for testing value

   always put an else statement in if statements

   definitions are not expressions. definitions bind values to names, and 
   values are expressions(evaluated or not)

   functions are defined as:
            [let f x = ...] for non recursive functions
            [let rec f x = ...] for recursive functions
   e.g. tail recursive factorial functions:
*)

(* requires n >= 0 *)
(* returns n! *)

let rec fact curr last =
  if (curr = 0) then (last) else (fact (curr - 1) (last * curr));;

(fact 5 1)

(* mutually recursive functions can be defined with the [and] keyword *)

let rec odd (n : int) : bool =
  n <> 0 && even (n - 1)

and even (n : int) : bool =
  n = 0 || odd (n - 1);;

(*There is no dynamic semantics of function definitions, only definition.
  - The only dynamic semantics associated with a function is at runtime
    evaluation.
  - Static semantics, if the types of arguments are sound, and the expr
    which forms the body of the function has type [u], then the type
    of the function is [t1 -> t2 -> ... -> tn -> u]
  - for recursive functions, if we assume that the function has a specific
    identifier, and the identifier is associated with a specific type, then 
    the static analyzer checks to see if the body of the function is well 
    typed under that type we have assumed, due to the fact that the function
    we are defining is part of the function. We check the type of the function
    by using the type we have assumed the function has.
    (How does this type checking work?)

  lambdas can be defined using the [fun] primitive
*)

let inc x = x + 1;; (* is the same as*)
let inc_1 = fun x  -> (x + 1);;

(* also, pretty interesting, a lambda is a value, which makes sense

   When 'a is used, it represents an unknown type, generally read as 
   alpha

   polymorphic functions can be defined by not explicitly stating 
   type, or using values which are associated with a type

   You can label arguments just by writing [~name1, ~name2...]
   e.g.:
*)

let foo ~arg1:arg1 ~arg2:arg2 = arg1 + arg2;; (* which is equivalent to *)

let foo1 ~arg1 ~arg2 = arg1 + arg2;;

(* Also, it is possible to have optional arguments with default values
*)

let foo2 ?name:(arg1 = 10) arg2 = arg1 + arg2;;

(* We can also partially define functions in the following manner
*)

let addx x = fun y -> x + y;;

(* Which has the type [int -> (int -> int)]

   Which is basically just an uncurried function. We can then apply it to a single
   argument

   Really, add is just a function which takes an integer argument and returns 
   a function which returns an integer argument. Really this is semantically
   equivalent to .\(x.(.\y.(x + y))) which is basically the same as .\(x y).(x + y)

   Every ocaml function, under the hood, really just takes one argument, the 
   functions are just curried together

   function definition is right associative, and application is left associative
   x -> (y -> z) and ((x y) z)

   We can define out own infix operators by using ( op ), e.g.
*)

let (^^) x y = max x y;;

(*therefore, x ^^ y = max x y 

  let can be divided into two  forms, a definition and an expression   
*)

let x = 42;; (* is a definition *)
(let x = 42 in x) + 1;; (* is an expression equivalent to 42 + 1, as is *)
let x = 42 in (x + 1);;

(* At the top level, let definitions are like let expressions which have
   not been provided a body to substitute the variable in
*)

let x = 5 in x + 1;;

(* in the previous statement, x is an identifier, 5 is the binding expression
   and x + 1 is the body

   let expressions are syntactic sugar for lambda application. Specifically,
   the body is the return value, the identifier is the parameter, and the 
   binding expression is the argument

   let bindings are lexically scoped

   let bindings follow expected scope associated with lambda calculus
   (alpha equivalence, local variable shadowing, etc)

   each let definition binds an entirely new variable

   In order to chain together multiple commands which return unit,
   the only thing which needs to be used is a single [;], e.g.:
*)

print_endline "neato";
print_endline "burrito";;

(**
   This is an OCaml doc. It is extracted separately
*)

let rec exp base exponent accumulator =
  if exponent = 0 then accumulator else
    exp base (exponent - 1) (accumulator *. base);;

let sgn x =
  if x = 0 then 0 else if
    x < 0 then -1 else 1;;

let rms x y =
  sqrt (((x *. x) +. (y *. y)) /. 2.0);;

let valid_date d m =
  let valid_months =
    ["Jan"; "Feb"; "Mar"; "Apr"; "May"; "Jun"; "Jul"; "Aug"; "Sept"; "Oct"; "Nov"; "Dec"] in
  let valid_day d =
    (d > 0 && d < 31) in
  (valid_day d) && (List.mem m valid_months);;

let rec print_int_list = function 
  | [] -> () 
  | h::t -> print_endline (string_of_int h); 
    print_int_list t;;

let print_int_list' lst = 
  List.iter (fun x -> for i = 0 to (List.length lst) do
                print_endline (string_of_int (List.nth lst i)) done)
    lst;;

(* pattern matching can also be replaced with the function keyword, they are 
   syntactic sugar for one another. e.g.: *)

let rec sum_list_pattern l n =
  match l with
    [] -> n
  | h :: t -> sum_list_pattern t (n + h);;

let rec sum_list_function = function
    [], m -> m
  | h::t, m -> sum_list_function (t, (m + h));;


(* records are a type which can be defined in OCaml, which are similar to C structs
   or Lisp records *)

type author = {name : string; birth_year : int ; num_books : int };;

let dostoevsky:author = {name = "Fyodor"; birth_year = 1821 ; num_books = 15};;

dostoevsky.name;; (* is equivalent to *)

let find_name = function
    {name = n; birth_year = b_y; num_books = n_b } -> n;;

(* regular variants are most similar to types inductive types in Coq, while records
   are similar to C/lisp structs *)

let tolstoy = {dostoevsky with name = "Leo"};;

(* The main difference between a variant and a record is a variant offers a single
   value within the set which comprises the type, which a record offers a value
   for each member of the type (one of vs each of, respectively) 

   One of types are also referred to as sum types and each of types also known as
   product types, as variants are like disjoint unions of singleton sets of other
   types, which records are combinations (like the cartesian product) of multiple 
   sets/types.   
*)

(* multiple patterns can be matched at once by using a single pipe, like so *)

let check_small_list l =
  match l with
    [] | _::[] -> true
  | _ -> false;;

(* the [when] keyword can also be used to have implicit conditionals in matches, i.e *)
let check_big_list l a =
  match l with
    [] when a > 5 -> a
  | [] when a <= 5 -> a - 1
  | _ -> 0;;

(* dictionaries are implemented as a higher order data structure comprised of a list
   of pairs

   catch all cases [_] -> ... are not considered good [ractice as they lead to buggy
   code when types are expanded
*)

(* exceptions can be raised with [failwith]
   
   they can also be caught with pattern matching, however, instead of match, you would
   just write [try] instead

   they can also be caught in pattern matching by adding an argument which looks like:
     [exception (Failure s) -> s]

   This can also be higher order, like so 
*)

let divide_by a b =
  match a, b with
  | Some (a' : float), Some (b' : float) -> Some (a' /. b')
  | None, Some b' -> Some 0.0
  | _, _ -> None;;

(* variants can be polymorphised by just using a', b', etc in definition *)

(* the int * int corresponds with the children of left and right subtree *)
type 'a sb_tree =
  | Leaf
  | Node of 'a * int * 'a sb_tree * 'a sb_tree;;

(*  *)
let rec check_tree sb_tree
