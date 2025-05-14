# autoBuildC
> Copy and paste the executable into the path: `C:\Windows\System32`

**autoBuildC** is a simple Windows executable named `cbuild` that helps you quickly compile all `.c` or `.cpp` files in the current directory and its subdirectories using `gcc` or `g++`.

## Features

- Recursively scans for all `.c` or `.cpp` source files.
- Automatically compiles the sources using the appropriate compiler.
- Allows you to specify the output executable name.
- Visual mode prints all detected file paths before compiling.
- Supports both C and C++ source file filters.

## Example

<img src="https://github.com/Dspofu/AutoBuildC/blob/main/image.png">

## Usage

```bash
cbuild [options]
````

### Options

* `-gcc` Filters and compiles only `.c` files using **gcc**. `Default option.`

* `-g++` Filters and compiles only `.cpp` files using **g++**.

* `-l` Enables **visual mode**, which prints out the full paths of all detected source files before compiling.

* `-static` Creates in static mode.

* `-name <filename>` Sets the output executable name. Default is `main.exe`.

## Example Commands

Compile all `.c` files with `gcc` and show the file paths:

```bash
cbuild -gcc -l
```

Compile in static mode all `.cpp` files with `g++` and name the output `myApp.exe`:

```bash
cbuild -g++ -static -name myApp.exe
```

## Notes

* This tool is built specifically for **Windows**.
* Make sure `gcc` or `g++` is available in your system's PATH.

## License

This project is open source and free to use.
