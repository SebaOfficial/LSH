# LSH
A light implementation of a shell written in C.

Since its purpose is demonstration (not feature completeness or even fitness for casual use), it has many limitations, including:

* Commands must be on a single line;
* Arguments must be separated by a whitespace;
* No quoting arguments or escaping whitespace;
* Non piping or redirection;
* Only builtins are: `cd`, `help`, `exit`.

## Running
```
make && ./lsh
```

## License
This project is under the [MIT License](https://github.com/SebaOfficial/LSH/blob/main/LICENSE).
