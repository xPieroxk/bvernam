# bvernam

## Overview
bvernam is a simple command-line application for encrypting and decrypting files using a variant of the Vernam cipher. This project was developed as a submission for an Operating Systems exam. The cipher leverages the basic property of the XOR operator:

```
(A XOR B) XOR B = A
```

## Algorithm Description
Given:
- A key file containing k bytes: b0, b1, …, bk-1
- An input file (to be encrypted or decrypted) containing a sequence of bytes: d0, d1, …, dN

The algorithm works as follows:
1. The input file is divided into blocks of k bytes (except possibly the last block).
2. For each block j and for each byte i in that block, compute:

   ```
   d'_j,i = d_j,i XOR b_{(j+i) mod k}
   ```

3. The output is the concatenation of all modified blocks.

## Usage
The application is invoked from the command line with the following parameters:

```
bvernam keyfile inputfile outputfile
```

Where:
- **keyfile**: The file containing the encryption/decryption key.
- **inputfile**: The file to encrypt or decrypt.
- **outputfile**: The file where the result will be saved.

## Building the Project
Follow these steps to build the project with CMake:

1. Open a terminal and navigate to the project directory:

   ```
   cd bvernam
   ```

2. Create a build directory and change into it:

   ```
   mkdir build && cd build
   ```

3. Configure the project:

   ```
   cmake ..
   ```

4. Build the executable:

   ```
   make

   ```

The binary file `bvernam` will be created inside the `build/` directory.

### Optional: Move the Executable and Clean Up
To keep only the binary and delete all build files:

```
cp build/bvernam .
rm -rf build
```

Now you will have a clean project folder with just your source files and the compiled executable.


## Testing
A `test/` folder is provided in the project directory to verify the encryption and decryption functionality of the application. It contains:

- `bvernam.c` – used as the input file
- `bvernam.h` – used as the key file
- `cipher.txt` – the result of encrypting `bvernam.c` with `bvernam.h`
- `recovered.c` – the output you get when decrypting `cipher.txt` with the same key

### Example Workflow

From the project root, after building the project:

1. Move into the `test/` directory:

   ```
   cd test
   ```

2. Encrypt `bvernam.c` using `bvernam.h` as the key:

   ```
   ../bvernam bvernam.h bvernam.c cipher.txt
   ```

3. Decrypt the file back:

   ```
   ../bvernam bvernam.h cipher.txt recovered.c
   ```

4. You can compare the original and recovered files to verify correctness:

   ```
   diff bvernam.c recovered.c
   ```

   The output should be empty, indicating the files are identical.

### Notes
- File names like `cipher.txt` and `recovered.c` are used for clarity. Feel free to change them.
- The same file (`bvernam.h`) is used as the key for both encryption and decryption, thanks to the symmetric nature of the XOR operation.
