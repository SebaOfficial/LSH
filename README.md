# LSH
A light implementation of a shell written in C.

Since its purpose is demonstration (not feature completeness or even fitness for casual use), it has many limitations, including:

* Commands must be on a single line;
* Arguments must be separated by a whitespace;
* No quoting arguments or escaping whitespace;
* Non piping or redirection;
* Only builtins are: `cd`, `help`, `exit`.

## Build
You can either build with `make` or download the latest artifact in the [actions](https://github.com/SebaOfficial/LSH/actions/workflows/build.yml).

## Run
If you downloaded the artifact you first need to extract the `lsh` file from the zip, then you can just run it (*make sure it's executable*).
```
./lsh
```

## License
This project is under the [MIT License](https://github.com/SebaOfficial/LSH/blob/main/LICENSE).
