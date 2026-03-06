# 0x00-preprocessor

## Description
This project contains a Bash script that runs a C file through the C preprocessor and saves the output into another file named `c`.

### Script
- `0-preprocessor`: A Bash script that reads the C file name from the environment variable `$CFILE`, runs the preprocessor using `gcc -E`, and saves the result into the file `c`.

### Usage
1. Export the C file you want to preprocess:
```bash
export CFILE=main.c
