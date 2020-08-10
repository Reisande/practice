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

/*
 * Undecidable call by value
 * λ(z.(z z)) λ(z.(z z))
 * becomes
 * λ(z.(z z)) λ(z.(z z))
 */


/*
 * Undecidable call by value, but decidable call by name
 * (λ(x.(λ(y.y))) (λ(z.(z z)) λ(z.(z z))))
 * becomes
 * (λ(x.(λ(y.y))) (λ(z.(z z)) λ(z.(z z))))
 * when called by value, but becomes
 * λ(y.y)
 * when called by name
 */


/*
 * Lexical Scoping
 */


/*
 * Lexical scoping, but fancier
 */

