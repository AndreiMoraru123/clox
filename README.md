## Lox (programming language implementation)

This is the C implementation of the bytecode compiler and virtual machine from the book.

Each branch (other than `master`) represents an addition to the language, encompassing all the challenges proposed by the author for each chapter (or at least a whole bunch of them).

Here are some sample Lox programs:

```
fun fib(n) {
  if (n < 2) return n;
  return fib(n - 2) + fib(n - 1);
}

var start = clock();  // built-in native function call
print fib(10);
print clock() - start;
```

```
// OOP support via class representation
class Cake {

  init(adjective) {
    this.adjective = adjective;
  }

  taste() {
    print "The " + this.flavor + " cake is " + this.adjective + "!";
  }
}

var cake = Cake("delicious");
cake.flavor = "German chocolate";
cake.taste();
```

```
class Doughnut {
  cook() {
    print "Fry until golden brown.";
  }
}

// Support for single inheritance
class BostonCream < Doughnut {
  cook() {
    super.cook();
    print "Pipe full of custard and coat with chocolate.";
  }
}

BostonCream().cook();
```
