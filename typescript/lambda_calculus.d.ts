declare module LambdaCalculus {
    export type Top =
        | { type: "Variable", name: string }
        | { type: "Lambda", parameter: string, body: Top }
        | { type: "Application", caller: Top, argument: Top };

    export function prettyPrint(t: Top): string;
    export function replaceParameter(t: Top, argument: Top, s: string): Top;
    export function callByName(t: Top): Top;
}

