import LambdaCalculus = require("./lambda_calculus");

/*
 * terminal expressions
 */
const t1: LambdaCalculus.Top = { type: "Variable", name: "x" };
const t2: LambdaCalculus.Top = {
    type: "Lambda",
    parameter: "y",
    body: {
        type: "Variable",
        name: "y"
    }
};

console.log("Terminal expressions: ");
console.log("Variables: " + LambdaCalculus.prettyPrint(t1));
console.log("Lambdas: " + LambdaCalculus.prettyPrint(t2));
console.log("");

/*
 * basic application of a variable to a lambda
 */

const a: LambdaCalculus.Top = {
    type: "Application",
    caller: t2,
    argument: t1
}

console.log("Application of a function to a variable: ");
console.log(LambdaCalculus.prettyPrint(a));
console.log("becomes: ")
console.log(LambdaCalculus.prettyPrint(LambdaCalculus.callByName(a)));
console.log("");

/*
 * Call by name
 * λ(x.(λ(y.(x y))))(λ(z.z))
 * becomes
 * λ(y.(λ(z.z) y))
 */
const n: LambdaCalculus.Top = {
    type: "Application",
    caller: {
        type: "Lambda",
        parameter: "x",
        body: {
            type: "Lambda",
            parameter: "y",
            body: {
                type: "Application",
                caller: {
                    type: "Variable",
                    name: "x"
                },
                argument: {
                    type: "Variable",
                    name: "y"
                }
            }
        }
    },
    argument: {
        type: "Lambda",
        parameter: "z",
        body: {
            type: "Variable",
            name: "z"
        }
    }
}

console.log("Call by name: ");
console.log(LambdaCalculus.prettyPrint(n));
console.log("becomes");
console.log(LambdaCalculus.prettyPrint(LambdaCalculus.callByName(n)));
console.log("")

/*
 * Undecidable application
 * λ(x.(x x)) λ(y.(y y))
 * becomes
 * λ(y.(y y)) λ(y.(y y))
 *
 * λ(z.(z z)) λ(z.(z z))
 * becomes
 * λ(z.(z z)) λ(z.(z z))
 */
const u1: LambdaCalculus.Top = {
    type: "Application",
    caller: {
        type: "Lambda",
        parameter: "x",
        body: {
            type: "Application",
            caller: {
                type: "Variable",
                name: "x"
            },
            argument: {
                type: "Variable",
                name: "x"
            }
        }
    },
    argument: {
        type: "Lambda",
        parameter: "y",
        body: {
            type: "Application",
            caller: {
                type: "Variable",
                name: "y"
            },
            argument: {
                type: "Variable",
                name: "y"
            }
        }
    }
}

const u2: LambdaCalculus.Top = {
    type: "Application",
    caller: {
        type: "Lambda",
        parameter: "z",
        body: {
            type: "Application",
            caller: {
                type: "Variable",
                name: "z"
            },
            argument: {
                type: "Variable",
                name: "z"
            }
        }
    },
    argument: {
        type: "Lambda",
        parameter: "z",
        body: {
            type: "Application",
            caller: {
                type: "Variable",
                name: "z"
            },
            argument: {
                type: "Variable",
                name: "z"
            }
        }
    }
}

console.log("Undecidable application: ");
console.log(LambdaCalculus.prettyPrint(u1));
console.log("becomes");
console.log(LambdaCalculus.prettyPrint(LambdaCalculus.callByValue(u1)));
console.log("")
console.log(LambdaCalculus.prettyPrint(u2));
console.log("becomes");
console.log(LambdaCalculus.prettyPrint(LambdaCalculus.callByValue(u2)));
console.log("")

/*
 * Undecidable call by value, but decidable call by name
 * (λ(x.(λ(y.y))) (λ(z.(z z)) λ(z.(z z))))
 * becomes
 * (λ(x.(λ(y.y))) (λ(z.(z z)) λ(z.(z z))))
 * when called by value, but becomes
 * λ(y.y)
 * when called by name
 */
const d: LambdaCalculus.Top = {
    type: "Application",
    caller: {
        type: "Lambda",
        parameter: "x",
        body: {
            type: "Lambda",
            parameter: "y",
            body: {
                type: "Variable",
                name: "y"
            }
        }
    },
    argument: LambdaCalculus.deepCopy(u2)
}

console.log("Undecidable call by value, but decidable call by name");
console.log(LambdaCalculus.prettyPrint(d));
console.log("becomes");
console.log(LambdaCalculus.prettyPrint(LambdaCalculus.callByValue(d)));
console.log("when called by value, but becomes");
console.log(LambdaCalculus.prettyPrint(LambdaCalculus.callByName(d)));
console.log("when called by name");

/*
 * Lexical scoping
 * (λ(y.λ(y.(y y)) y) λ(z.z))
 */
const l: LambdaCalculus.Top = {
    type: "Application",
    argument: {
        type: "Lambda",
        parameter: "z",
        body: {
            type: "Variable",
            name: "z"
        }
    },
    caller: {
        type: "Lambda",
        parameter: "y",
        body: {
            type: "Application",
            argument: {
                type: "Variable",
                name: "y"
            },
            caller: {
                type: "Lambda",
                parameter: "y",
                body: {
                    type: "Application",
                    caller: {
                        type: "Variable",
                        name: "y"
                    },
                    argument: {
                        type: "Variable",
                        name: "y"
                    }
                }
            }
        }
    }
}
console.log(LambdaCalculus.prettyPrint(l));

console.log("Now is an example of the concept of lexical scoping. Lexical Scoping");
console.log("is pretty similar to scoping in traditional programming languages; variables");
console.log("inside of lambdas correspond to the parameter in the closest nest layer");
console.log("");
console.log("So, for example in the following case:");
console.log("λ(y.λ(y.y) y)")
console.log("  |   | |  | ")
console.log("  |   ╰-╯  | ");
console.log("  ╰--------╯  ")
console.log("the variables are connected like so");
console.log("Another, more complicated example:")
console.log(LambdaCalculus.prettyPrint(l));
console.log("   |    |  | |   |     | |");
console.log("   |    ╰--╯-╯   |     ╰-╯");
console.log("   ╰-------------╯");
console.log("and is evaluated to");
const l1: LambdaCalculus.Top = LambdaCalculus.callByName(l);
console.log(LambdaCalculus.prettyPrint(l1));
console.log("and then");
const l2: LambdaCalculus.Top = LambdaCalculus.callByName(l1);
console.log(LambdaCalculus.prettyPrint(l2));
console.log("and then");
const l3: LambdaCalculus.Top = LambdaCalculus.callByName(l2);
console.log(LambdaCalculus.prettyPrint(l3));

// TODO
// church calculus, true/false, currying, stlc
