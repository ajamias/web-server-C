# Web Server in C

## 1. Why Am I Doing This Project:
For starters, I like writing efficient and low-level code in C/C++. Second, I am confident in stating that I have a good understanding of what a computer does to perform a specific action if I can implement it in C/C++ (in this case, a web server). Third, I am/was a student for Boston University's Cloud Computing (EC528) and Cybersecurity (EC521) classes, and I want to implement some of the techniques from those classes onto this project. Lastly, I want to play around with a Raspberry Pi to simulate a physical server in a cloud provider's data center.

## 2. Vision and Goals Of The Project:
This is a project where I learn and explore more how the web works under the hood by creating my own web server in C. Specifically, I want to learn more about:
* The C Programming Language
  * _New system calls_
  * Socket programming
* The client/server system architecture
* Internet Protocol Suite
  * _HTTP 1.1/2/3_
  * IP, TCP, _UDP_, _QUIC_, DNS, etc.
* Kubernetes
  * Load balancing
  * _Scaling_
* Databases/storage
* _HTTPS + other security practices_

**Note:** Text that is italicized indicates that I have no previous experience working with that technology/methodology.

This project is related to my [portfolio website project](https://github.com/ajamias/portfolio); this web server will be serving the content from that repo to people who visit my website @ [austinjamias.us](austinjamias.us). An end goal is to see this server up and running under Kubernetes deployed on a Raspberry Pi that displays my website on a browser.

## 3. Scope and Features Of The Project:
The features of this project mostly depends on what web projects I want to take in the future. The features that I currently envision are:
* Implement some type of REST/SOAP API to interact with the server
* Implement some database system to store messages
* Using Kubernetes to load balance and scale this web server
* Deploying on Raspberry Pi
* Create a text chat room using TCP (stretch goal)
* Create a video streaming room using UDP (stretch goal)
