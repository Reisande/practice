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

// there's also more complex data structures like map and tuple, defined here:
// https://www.typescriptlang.org/docs/handbook/basic-types.html
let pair: [number, number] = [0, 0];

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

// classes can be defined as explicitly implementing an interface
class doctor implements Person {
    name: string
    move() {
        console.log("Hello, I am a doctor");
    }
}

// since functions are first class citizens, you can use interfaces to describe them too
interface SearchFunc {
    (source: string, object: string): boolean;
}

let mySearch: SearchFunc = function(src: string, obj: string) {
    return src.search(obj) != -1;
}

// classes, members are public by default
class Point {
    x: number;
    y: number;

    // default values of 0 for both x and y, but can take arguments
    constructor(x: number = 0, y: number = 0) {
        this.x = x;
        this.y = y;
    }

    distance() {
        return Math.sqrt((this.x * this.x) + (this.y * this.y));
    }

    // static members are like Java static rather than C static
    static origin: Point = new Point();
}


// so these are all valid initiliazations of objects:
const p1: Point = new Point(1, 1);
const p2: Point = new Point(1);
const p3: Point = new Point();

// you can make classes which inherit from other classes
class Point3D extends Point {
    private z: number;

    constructor(x: number = 0, y: number = 0, z: number = 0) {
        // superclass' constructor must be explicitly called
        super(x, y);
        this.z = z;
    }

    dist() {
        let d: number = super.distance();
        return Math.sqrt(d + (this.z + this.z));
    }
}

// modules can be used as something akin to C++ namespaces
module Geometry {
    export class Square {
        constructor(public sidelength: number = 0) { }

        area() {
            return this.sidelength * this.sidelength;
        }
    }
}

import G = Geometry;
const s1 = new G.Square();

// generics also exist, and can be used as expected
class Tuple<T1, T2> {
    constructor(public first: T1 = null, public second: T2 = null) { }
}

interface Pair<T> {
    first: T;
    second: T;
}

const pairToTuple = function <T>(p: Pair<T>) {
    return new Tuple<T, T>(p.first, p.second);
}

const templateString = `This is a square: ${s1}
this is its sidelength: ${s1.sidelength}`

console.log(templateString);

// readonly exists which acts as something like a const but only for classes and
// interfaces, and is const after assignment
class ReadPerson {
    readonly name: string;
    readonly age: number;
}

// there is also a readonly array, which is pretty much just a const array imo
let readNumbers: ReadonlyArray<number> = [1, 2, 3, 4, 5];

// there are also tagged Unions types
const numberOrString = function(b: boolean): number | string {
    if (b) {
        return 0;
    }
    else {
        return "";
    }
}

type Variable = {
    name: string;
    nest: number;
}

type Lambda = {
    parameter: Variable;
    body: Top;
}

type Application = {
    caller: Top;
    argument: Top;
};

// you can also declare types as union types, like ocaml
type Top =
    | Variable
    | Application
    | Lambda;

// you also have iterators
const iteratorList = [1, 2, 3, 4];
for (const i in sampleList) {
    console.log(i);
}

// you can also create indexable types like hashmaps like so:
class Map<T> {
    [key: string]: T;
}

let map: Map<number> = new Map<number>();
map['x'] = 0;
map['y'] = 0;

console.log(map);

console.log(map['z']);
