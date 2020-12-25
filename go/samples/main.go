package main

import (
	"fmt"
	"math"

	"rsc.io/quote"
)

const (
	// Create a huge number by shifting a 1 bit left 100 places.
	// In other words, the binary number that is 1 followed by 100 zeroes.
	Big = 1 << 100
	// Shift it right again 99 places, so we end up with 1<<1, or 2.
	Small = Big >> 99
)

// I could definitely see this being a realistic use case for lazy evaluation
func fibonacci() func() int {
	i, j := 0, 1
	return func() int {
		if i < j {
			i += j
			return i
		} else {
			j += i
			return j
		}
	}
}

func printSlice(x []int) {
	fmt.Printf("len=%d cap=%d %v\n",
		len(x), cap(x), x)
}

// you can return multiple variables at once by declaring them in a tuple
// if you give a return variable a name, it is treated as though it was declared
// at the top of the function in order to maintain readability
func split() (x int, y int) {
	x = 1
	y = x + 1

	// a return statement without arguments is known as a naked return, and should
	// only be used in short functions
	return
}

func needInt(x int) int {
	return x*10 + 1
}

func needFloat(x float64) float64 {
	return x * 0.1
}

// structs are declared as:
type Point struct {
	X int
	Y int
}

func adder() func(int) int {
	sum := 0
	return func(x int) int {
		sum += x
		return sum
	}
}

func main() {
	fmt.Println(quote.Go())
	// values from other packages(functions, variables, etc), can only be referenced
	// if they start with capital letters. So
	fmt.Println(math.Pi)

	// is valid, but
	// fmt.Println(math.pi) // is an error because .pi would be a static variable

	fmt.Println(split())

	// var declares a list of variables of size >= 1 with the type at the end
	var i, count int
	i = 0
	count = i + 1
	fmt.Println(i + count)

	// variables can also be initialized prematurely, with type inference
	var name, id, good = "string", " first ", true

	fmt.Println(name + id + fmt.Sprintf("%v", !good))

	// you can also declare short variables inside of functions using the walrus
	// operator
	a, b := 5, 6
	fmt.Println(a + b)

	// casts are done by the format: var = Type(other_var)
	var c = float64(a)
	fmt.Println("Float version of a: " + fmt.Sprintf("%v", c))

	// go also has constants, but they can only be defined by other constants,
	// and without :=
	const d int = 10

	fmt.Println(needInt(Small))
	fmt.Println(needFloat(Small))
	fmt.Println(needFloat(Big))
	// the following line would fail due to overflow, but the error is caught at
	// compile time
	// fmt.Println(needInt(Big))

	var sum = 0
	// go only has for loops (while is just `for cond`)
	// iterators defined in the loop can only be defined with :=
	// braces are always required, no parens, while init and post statements are optional
	for i := 0; i < 10; i++ {
		sum += i
	}

	fmt.Println(sum)

	// a while true in go looks like:
	for true {
		break
	}

	// or it can also be expressed as
	for {
		break
	}

	// if is identical to rust ifs

	// defer also allows for an interesting feature which prevents an operation
	// from occurring until the surrounding function returns
	// defer has its own stacks, which may make it useful as a quick and dirty concurrent
	// debugging tool
	defer fmt.Println("Function main has returned")

	fmt.Println("Line 104")

	// pointers are identical to C's pointers, except they are declared as:
	var p *int
	fmt.Println(p)
	// but go has no pointer arithmetic

	point := Point{X: 1, Y: 2}
	fmt.Println(point)

	// pointers to structs don't require arrow notation
	pPoint := &point
	pPoint.X = 2

	fmt.Println(pPoint)

	// arrays are declared and defined as such:
	primes := [3]int{2, 3, 5}
	// or
	var composites = [4]int{4, 6, 8, 9}
	fmt.Println(primes)

	// you can slices with the [:] notation
	// inclusive lower bound non inclusive upper bound(probably syntactic sugar
	// for a for loop at some point in compilation)
	// default values are lower and upper bound
	fmt.Println(composites[1:3])

	// you can also quickly define slices of structs like so
	v := []struct {
		x int32
		y int32
	}{
		{1, 1},
		{2, 2},
	}

	// a slice has a predefined length and capacity
	fmt.Printf("%x, %x, %x\n", cap(v), len(v), v)

	// you can resize slices like so:
	v = v[:1]
	fmt.Printf("%x, %x, %x\n", cap(v), len(v), v)

	// you can re-extend a slice as long as it does not go past its previously
	// defined capacity(whatever it was initialized with), otherwise it becomes
	// a runtime error
	v = v[:2]
	fmt.Printf("%x, %x, %x\n", cap(v), len(v), v)

	// dynamic slices are created with the make keyword
	// arrays are automatically initialized with 0
	dynamic := make([]int, 0)

	printSlice(dynamic)

	for i := 0; i < 11; i++ {
		// if something is defined with make and then appended to, then the
		// leading 0s which the array was initialized with are kept
		dynamic = append(dynamic, i)
		printSlice(dynamic)

		// probably a good idea to call make with a second arg of 0, unless you
		// are accessing individual elements
		// TODO: check performance of allocating and accessing elements in
		//  arrays less than and greater than a page size
		//  also read https://blog.golang.org/slices-intro
	}

	// range is explicit in range based for loop
	var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}

	// can be thought of as a function which returns the index and the index
	// value (I wonder how this affects cache performance)
	// the second value can be omitted or can be replaced with a _ like rust
	for i, v := range pow {
		fmt.Println("2 ^ %d = %d", i, v)
	}

	// maps are pretty similar to typescript maps
	myMap := make(map[string]struct {
		X int
		Y int
	})
	myMap["bellman"] = struct {
		X int
		Y int
	}{1, 1}

	fmt.Println(myMap["bellman"])

	// you can also make map literals in the same way as struct or slice
	// literals

	// you can delete variables with delete
	delete(myMap, "bellman")
	// deleting a key which doesn't exist just succeeds quietly
	delete(myMap, "ford")

	elem, ok := myMap["bellman"]
	fmt.Println("Mymap", elem, ok)
	// if ok is false, elem is just a nil elem/0 initialized elem

	myLambda := func(x int, y int) int {
		return 0
	}

	fmt.Println(myLambda)

	// you can have lazy evaluation pretty simply by creating a monad which
	// takes functions and computes them as the return statement

	// go also has closures
	// closures are lambdas which have been defined at various points,
	// and functions are truly first class citizens
	pos, neg := adder(), adder()
	for i := 0; i < 10; i++ {
		// since all lambdas are closures and the spawning functions have
		// different environments for pos and neg due to having different
		// call stacks, pos and neg have different sets of the sum variable
		fmt.Println(
			pos(i),
			neg(-2*i),
		)
	}

}
