// the three primitive types are booleans, numbers, and strings
let isDone: boolean = false;
let lines: number = 42;
let sampleString: string = "Misha";

// type annotation can be omitted when variables are initalized with explicit literals
let isDoneImplicit = false;
let linesImplicit = 42;
let sampleStringImplicit = "Misha";

// if the type is unknown, or there may be multiple types, you can use the any type
let unknownVariable: any = 4;
unknownVariable = "Maybe this is a string";
unknownVariable = false;

// type errors are caught by the linter/autoformatter
// uncomment this in order to see the error:
// lines = false;

// const makes variables immutable
const numberOfLivesForCat: number = 9;
// this will be an error:
// numberOfLivesForCat++;

// collections can be represented as either typed arrays like so:
let sampleList: number[] = [1, 2, 3, 4];
// or using generics(which will live on the heap)
let sampleGenericList: Array<number> = [1, 2, 3];

// enums are defined like so:
enum Color { Red, Green, Blue };
let c: Color = Color.Green;

// here is how functions work
function basicAlert(a: string): void {
    alert("AAAH A WILD " + a + " THE HORROR, OH THE HORROR");
}

// typescript is functional with multiple ways to define lambdas
// any of the keywords from
let addVerbose = function(first: number, second: number): number { return first + second; }
// to
let addSuccinct = (first: number, second: number) => first + second;

// typescript is also oop, and has interfaces
// interfaces are abstract classes, where it is up to the implementing class to 
// figure it out
interface Person {
    name: string;
    // option properties are denoted with a '?'
    age?: number;
    move(): void;
}

// classes can be implicitly defined through interfaces without explicit constructors
let p: Person = { name: "Misha", move: () => { console.log("hello") } };

// since functions are first class citizens, you can use interfaces to describe them too
interface SearchFunc {
    (source: string, object: string): boolean;
}

let mySearch: SearchFunc = function(src: string, obj: string) {
    return src.search(obj) != -1;
}

// classes, members are public by default
