Advanced Encryption Standard (AES) implementation in C
======================================================

AES is the most widely adopted symmetric encryption standard nowadays. This repository contains an implementation in C of the AES-128 algorithm. The program takes two arguments: a 32-bytes hexadecimal string representing the 128-bit input block, and another 32-bytes hexadecimal string representing the 128-bit key. It then outputs the corresponding ciphertext in hexadecimal form.


![image](https://github.com/user-attachments/assets/900b8428-7ed6-4c77-9a9c-df00db352c40)

Screenshot taken after building the project with the build.bat file.


Installation
------------

First make sure you have installed the GCC compiler v8.1.0 or above.  
The `gcc --version` command should output:
```
gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```


Then, clone this repository in any location on your computer and double-click on `build.bat`.  
You should now see the following program's output:
```
CIPHERTEXT: 732281c0a0aab8f7a54a0c67a0c45ecf
```

The corresponding plaintext and key to obtain this ciphertext are encoded within the `build.bat` file.

Usage and test vectors
----------------------

The program takes two arguments: a 32-bytes hexadecimal string representing the 128-bit input block, and another 32-bytes hexadecimal string representing the 128-bit key. It then outputs the corresponding ciphertext in hexadecimal form.  
You can find some test vectors on the official NIST website [on this page](https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/block-ciphers).  

For example, with the following sample data set:  
```
KEY = 00000000000000000000000000000000
PLAINTEXT = 6a84867cd77e12ad07ea1be895c53fa3
```

The program should output:
```
CIPHERTEXT: 732281c0a0aab8f7a54a0c67a0c45ecf
```

To check this output, build the project and then execute this command:
```
main.exe 6a84867cd77e12ad07ea1be895c53fa3 00000000000000000000000000000000
```

You should now see the ciphertext `732281c0a0aab8f7a54a0c67a0c45ecf`.


Future work
-----------

A few ideas to improve this project:
- Add decryption part.
- Test the implementation in ECB or CBC block cipher modes.
- Rewrite the key expansion function in a cleaner way.
- Add features for file encryption.

License
-------

This work is shared under the [MIT license](LICENSE).  

The AES S-Box initialization function has not been written by me and have been taken from:  
https://en.wikipedia.org/wiki/Rijndael_S-box (Accessed on March 21, 2025)  
Original licence: CC BY-SA 4.0
