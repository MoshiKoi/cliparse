# CliParse (Provisional name)

Simple command line parsing utility.

## Usage

This is what a basic calculator command line tool might look like

```c++
int
run(float a, float b, char const *op) {
    // ...
}

int
main(int argc, char const **argv) {
	cli::Command program{"calc", "Calculate the sum, difference, product, or division of two numbers"};

	cli::Argument<float> arg1{"arg1", "First number"};
	cli::Argument<float> arg2{"arg2", "Second number"};
	cli::Option<char const *> operation{"--op", "operation", "add"};

	program.add_usage(run, arg1, arg2, operation);

	return program.run(argc, argv);
}
```

 - Automatic delegation: Instead of manually calling `auto arg_value = get_argument("arg1")` or some variation, it's just passed to the function provided.
 - Compile-time sanity check: if the parameters of the function passed in doesn't match the arguments in `add_usage`, it will not compile.

More examples can be found in the `examples` folder.

## Todo

 - [x] Argument parsing
 - [x] Option parsing
 - [ ] Mandatory options
 - [ ] Command line help