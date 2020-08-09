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

type Top =
    | Variable
    | Application
    | Lambda;

class Map<V> {
    [key: string]: V;
}

class Program {
    t: Top;
    // the keys are the name of the variable, and the return value is the number
    // of preexisting symbols with the same name, so when a new variable is found
    // with the sample name then the new variable has the nest level incremented
    symbols: Map<number>;

    constructor(t: Top = null) {
        this.t = t;
    }

    static callByName(): Program {

        return null;
    }

    static callByValue(): Program {

        return null;
    }
}
