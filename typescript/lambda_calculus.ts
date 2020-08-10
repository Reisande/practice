function deepCopy<T>(a: T): T {
    return JSON.parse(JSON.stringify(a));
}

// you can also declare types as union types, like ocaml
export type Top =
    | { type: "Variable", name: string }
    | { type: "Lambda", parameter: string, body: Top }
    | { type: "Application", caller: Top, argument: Top };

export function prettyPrint(t: Top): string {
    switch (t.type) {
        case "Variable":
            return t.name;
        case "Lambda":
            return "λ(" + t.parameter + "." + prettyPrint(t.body) + ")";
        case "Application":
            return "(" + prettyPrint(t.caller) + " " + prettyPrint(t.argument) + ")";
    }
}

/*
 * the program is the lambda which we will recursively descend down and replace 
 * all instances of a parameter until we hit another instance of a paramater with
 * the same name, or we hit the primitive case of reaching a variable
 *
 * p is the program we are replacing parameters in, t is the argument we passed
 * and name is the parameter we are replacing 
 */
export function replaceParameter(t: Top, argument: Top, s: string): Top {
    switch (t.type) {
        case "Application":
            return {
                type: "Application",
                caller: this.replaceParameter(t.caller, argument, s),
                argument: this.replaceParameter(t.argument, argument, s)
            };

        case "Lambda":
            if (t.parameter === s) {
                return deepCopy(t);
            }
            else {
                return {
                    type: "Lambda",
                    parameter: t.parameter,
                    body: this.replaceParameter(t.body, argument, s)
                };
            }

        case "Variable":
            if (t.name === s) {
                return deepCopy(argument);
            }
            else {
                return deepCopy(t);
            }
    }
}

/*
 * go through and do one stage of evaluation, so an example would be:
 * λ(x.(λ(y.(x y))))(λ(z.z))
 * becomes
 * λ(y.(λ(z.z) y))
 */
export function callByName(t: Top): Top {
    if (t.type !== "Application") {
        console.log(t);
        console.log(" the program has been fully evaluated");
        return deepCopy(t);
    }

    if (t.caller.type !== "Lambda") {
        console.log(t);
        console.log(" This is an invalid caller (only functions can be called)");
        console.log(" if this is a variable, then the variable is unbound and");
        console.log(" this expression has been fully evaluated");
        return deepCopy(t);
    }

    let returnT: Top = this.replaceParameter(t.caller.body, t.argument, t.caller.parameter);

    return returnT;
}

/*
 * evaluate the argument once and then do one stage of evaluation
 * the argument is not evaluated fully because it is possible that the
 * argument is undecidable and will be thrown away later
 * for example:
 * (λ(x.(λ(y.y))) (λ(z.(z z)) λ(z.(z z))))
 * is a function which *does* halt if evaluated in call by name semantics
 * but *cannot* halt if evaluated in call by value semantics. This is
 * this is because the expression (λ(z.(z z)) λ(z.(z z))) cannot be evaluated
 * at all. In both call by name and call by value semantics it is a quine
 * however, if we evaluate the first expression in call by name semantics
 * we get the terminal expression λ(y.y)
 */
export function callByValue(t: Top): Top {
    // just because it is simplest, if the argument is in a form where it
    // can be evaluated, we will just do one step of the call by name
    // evaluation on the argument and leave the calling function alone
    // if the argument has been fully evaluated, then we will just do a
    // call by name evaluation
    let returnT: Top = deepCopy(t);

    // this isn't DRY, but making it into a separate function makes tide unhappy
    if (returnT.type !== "Application") {
        console.log(t);
        console.log(" the program has been fully evaluated");
        return deepCopy(t);
    }

    if (returnT.caller.type !== "Lambda") {
        console.log(t);
        console.log(" This is an invalid caller (only functions can be called)");
        console.log(" if this is a variable, then the variable is unbound and");
        console.log(" this expression has been fully evaluated");
        return deepCopy(t);
    }


    if (returnT.argument.type == "Application") {
        returnT.argument = this.callByName(returnT.argument);
    }
    else {
        return this.callByName(returnT);
    }
}

