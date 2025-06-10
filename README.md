# bvernam

## Overview
bvernam is a simple command-line application for encrypting and decrypting files using a variant of the Vernam cipher. This project was developed as a submission for an Operating Systems exam. The cipher utilizes the basic property of the XOR operator:

```
(A XOR B) XOR B = A
```

## Algorithm Description

This application utilizes a variant of the Vernam Cipher, referred to as `bvernam`, to encrypt and decrypt files. The core of the algorithm utilizes a fundamental property of the binary XOR operator: `(A XOR B) XOR B = A`. This property ensures that the same process can be used for both encryption and decryption, making the operation reversible.

Given:
* A key file (`keyfile`) containing `k` bytes: $b_0, b_1, \dots, b_{k-1}$.
* An input file (`inputfile`) to be processed (encrypted or decrypted) containing a sequence of `N` bytes: $d_0, d_1, \dots, d_N$.

The `bvernam` algorithm processes the input file as follows:

1.  **Block Division**: The input byte sequence (`d0, ..., dN`) is first divided into blocks, `D0, ..., D((N/k)-1)`. Each block consists of exactly `k` bytes, except possibly the last block, which may contain fewer bytes. The number of blocks is the integer division of N by k (`N / k`).
2.  **Byte-level Transformation**: For each block `Dj = dj,0, ..., dj,k-1` (where `j` is the block index), each byte `dj,i` (at index `i` within the block) is transformed into a new byte `d'j,i` using the following operation:
    ```
    d'j,i = dj,i XOR b((j+i) mod k)
    ```
    This means the byte at position `i` of the block is XORed with the `(j+i) mod k`-th byte of the key.
3.  **Output Generation**: The final output byte sequence will be obtained by concatenating all the transformed blocks:
   <br>`D'0, ..., D'((N/k)-1)`.


<br>Full description of the algorithm can be found at [link](https://drive.google.com/file/d/1vD2h-qkl6G8jpxXXRx9MWQRU_MrpsrC0/view)


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
