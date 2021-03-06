
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

