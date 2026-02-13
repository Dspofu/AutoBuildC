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

* `-path <dirname>` Enter your project path. Default is where `cmd was started`.

* `-flags <multi-flags>` To use with other flags in your project..

* `-gcc` Filters and compiles only `.c` files using **gcc**. `Default option.`

* `-g++` Filters and compiles only `.cpp` files using **g++**.

* `-logs` Enables **visual mode**, which prints out the full paths of all detected source files before compiling.

* `-name <filename>` Sets the output executable name. Default is `main.exe`.

## Example Commands

Compile all `.c` files with `gcc` and show the file paths:

```bash
cbuild -gcc -logs
```

Compile in static mode all `.cpp` files with `g++` and name the output `myApp.exe`:

```bash
cbuild -g++ -flags "-static" -name myApp.exe
```

## Notes

* This tool is built specifically for **Windows**.
* Make sure `gcc` or `g++` is available in your system's PATH.

## License

This project is open source and free to use.
