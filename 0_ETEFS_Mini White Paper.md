
# Easy Transparent Encryption File System
<center><font size=5>(Minifilter Based)</font></center><br> 
<center><font size=5>ETEFS_Mini - Version 4.2</font></center> <br>
<center><font size=5>Product White Paper</font></center> <br>

## 0 Copyright notice
<p align="left"><font size=4>
Please read the “license.doc” to get enough copyright information first. If you do not agree with this license term, please don’t use any software provided by ETEFS.COM.</p></font>

## 1 Introduction
ETEFS_Mini is a transparent file encryption SDK based on minifilter technology. It runs in ring 0 mode. ETEFS_Mini can encrypt those files containing sensitive data generated by the selected applications, such as Microsoft Word, Excel and Power Point. All files are stored in encrypted form on the disk. The encryption progress is executed at background on-the-fly, and does not change the normal operation behavior of the end user. It is easy to integrate ETEFS_Mini into your software product in a short development cycle. Besides of the core transparent file encryption functionality, ETEFS_Mini also provides some extension functionalities that are very useful in developing data security related software product, including a file access control module and an operation event monitor module. With the help of ETEFS_Mini, software developers can rapidly build various document security products from scratch, like DLP (Data Loss Prevent) system, document right management system and document operation auditing system, etc. 
## 2 Product Benefits

### Easy to use
The API set of ETEFS_Mini is comprised of several functions programming in “C” language exported by a DLL library. By using these functions, it’s very easy to build a basic transparent file encryption system. These API functions can also be called from other programming language, like “C#” and “VB”.
### Easy to extend
To add file encryption support for a new application is also very easy. ETEFS_Mini provides two functions to support adding and deleting the file encryption policy. ETEFS_Mini can support most common applications by sending correct policy.
### Provides useful extension modules 
ETEFS_Mini includes a file access control module and an operation event monitor module. The file access control module is used to restrict the operation on the currently opened file issued by the user according to the access control policy. The operation event monitor is used to capture the user’s action on the encrypted file, such as “file opened” and “file closed” event, etc. 
### Cut down the development cycle
Developing a driver is difficult. Developing a file system driver is even more difficult. If you want to create an engine from scratch, this may take a long development cycle and cause the loss of the marketing.
## 3 System Architecture
The following diagram shows the architecture of ETEFS_Mini:

![图片](https://user-images.githubusercontent.com/39994647/109901419-0264bf00-7cd4-11eb-95d0-130e655676c6.png)
### Applications
The applications diagram represents the selected executable to be encrypted, such as Microsoft Word, Excel and Power Point. The document files generated by these applications will be encrypted automatically.

### Control program
The control program diagram represents the process sending the policy to the transparent file encryption system core and receiving the file operation event log. If this program exits, all policy set by it will not take effect.

### Policy configuration
The policy configuration diagram represents the module that receives the policy from control program. It stores the policy data to a file mapping object. Other modules can get the corresponding policy by reading the file mapping object.

### Event report
The event report module receives the operation log data from the capture module and pushes these log data to the control program. It uses the named pipe as the data transport mechanism.

### File event capture and access control
The functionality of this module has been described in chapter 2.

### Transparent file encryption core
This is the key component of ETEFS_Mini. It implements transparent file encryption by a file system minifilter driver. It decrypts data while an application loads data from disk and encrypts data while an application writes data to disk.

## 4 Product Features 
### Suport for encryption with per process access restriction
To create a minifilter encryption driver is not easy, to create a driver support encryption with process access restriction
is more complicated. ETEFS_Mini does support this feature. ETEFS_Mini does not use file redirection or hidden files to suport
this feature. All I/O requests operate on the same raw on-disk file. There are two cache views for the encrypted files, 
plain data cache for trusted process, encrypted data cache for untrusted process.

### Adding an extra file header per each encrypted file
ETEFS_Mini supports adding a file header data stream at the front of the encrypted file. One part of this data area is reserved by ETEFS_Mini, another part can be used by user of ETEFS_Mini freely. 

### Implementing in kernel mode
The core module of ETEFS_Mini is implemented in kernel mode. The minfilter framework is highly recommended by Microsoft. It is very convenient to intercept the file I/O requests and insert encryption module on file system stack. 

### Random file encryption key
ETEFS_Mini supports the random file encryption key mechanism. After enable this feature, ETEFS_Mini will allocate a random file encryption key for each file. Using this method to encrypt file is much more safety than using fixed file encryption key.

### Custom data binding
ETEFS_Mini adds an extended file header data to each encrypted file. A part of this header data is reservedly used by ETEFS_Mini itself to save some basic information about encryption. Another part of this header data is free for developer. Once this area of header data is set by the developer, it is firmly bind to the encrypted file forever by ETEFS_Mini. While editing the file, this custom data is still bonded with the encrypted file. The kind of data can be used to save the extended control information for the encrypted file.

### Manually encryption (on-the-fly decrypt only)
By default, once an unencrypted file is opened by a user, it will be encrypted by ETEFS_Mini automatically. If the developer enables “manually encryption” policy, ETEFS_Mini will not encrypt the file automatically. Users must use the encryption tools, for example a shell menu item, provided by the developer to convert the file into encrypted state.

### Encryption on Save-as 
When a user saves a currently opened file to a new file, the newly created file will be encrypted by ETEFS_Mini if the currently opened file is encrypted. This mechanism is used to keep the file containing sensitive data is always in encrypted state.

### File operation event capture
ETEFS_Mini supports capturing common file operation event, such as “open”, “close “and “print” etc.



