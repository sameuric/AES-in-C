Advanced Encryption Standard (AES) implementation in C
======================================================

AES is the most widely adopted symmetric encryption standard nowadays. This repository contains an implementation in C of the AES-128 algorithm. The program takes two arguments: a 32-bytes hexadecimal string representing the 128-bit input block, and another 32-bytes hexadecimal string representing the 128-bit key. It then outputs the corresponding ciphertext in hexadecimal form.


![screenshot](https://github.com/user-attachments/assets/8173fe57-0254-48df-a4e8-ebc41d01ccd0)

(Writing in progress)


Installation
------------

First install Python 3.13.2 or above.  
Then, make sure you have the following Python packages installed: `requests`, `pynput`.

You can install these packages with:
```
pip install requests pynput
```

Then, clone this repository and edit `keylogger.pyw` to add your own custom webhook URL at line 40.  

---
Double-click on `keylogger.pyw`. You will not see anything as the program starts in background. You can check if the program has successfully started with the following command:
```
tasklist | findstr /I "python"
```


Future work
-----------

A few ideas to improve this project:
- Add mouse's position capture and send this data to the server.
- Automatically take a screenshot of the whole screen and send it to the server.
- Get some system information with `os.system('systeminfo')` and send them to the server.
- Automatically start the keylogger at computer start (thus not self-destroying it).

License
-------

This work is shared under the [MIT license](LICENSE).  
Do not use this program without appropriate permissions.
