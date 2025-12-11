
<div align="center">
<img src="logo.png" alt="[J][C]ube[Code]">
<p align="center">
<strong>"Take your C to the next level."</strong>
</p>
<p align="center">
<a href="https://jcubeware.com/jcubecode"><strong>Documentation</strong> (WIP)</a> •
<a href="https://jcubeware.com/contact"><strong>Contact</strong></a>
</p>
<strong><small>⚠️ NOTE: [J][C]ube[Code] is still heavily under development. The purpose of 
this repo is to showcase the progress so far and the direction I am taking.</small></strong>
</div>
<br>
JCubeCode is a wrapper layer over C89/C90 that introduces new keywords and
extensive modules with the goal of modernizing the C experience.

With its own package manager, utilities, scripting enviroment and data format,
JCubeCode is a fully contained powerhouse that targets low-end machines and 
embedded chips primarily, whilst adding features for the big boy machines too.

The biggest difference between approach with tools like Zig and C3 is that
JCubeCode does not aim to replace C, it empowers it and natively integrates
even into legacy codebases.

Whilst JCubeCode offers many new features, for the scope of your project they
are optional. You don't have to use JCubeCode to enjoy features such as the
manager. For your project purposes, you can build a C89 project and compile it
right away.

## ❓ What is JCubeCode for ❓

### 🌳 Ecology / Pollution Prevention

JCubeCode's main mission is to reduce energy consumption and allow old devices
to shine again thanks to its speed and flexibility. Ecologically speaking, C is 
the most energy efficient language and also the most portable.

If there is a better enviroment for desktop apps to have, they'll be faster and
more efficient, thus preventing the usual "my PC is slow I need a new one".

### 🥴 Logical error prevention

Most common mistakes in programming happen in between the chair and monitor.
As we've seen with the Rust drama, having a "memory safe" language doesn't solve 
the biggest problem: logical errors.

JCubeCode's biggest value is clarity. Being that verbose allows anyone to read
a function at just a mere glance, reducing the mental strain of controlling
massively.

### 📖 Simple for beginners

Another big issue with programming is the code itself. C has a terse, but cumbersome
syntax. It's very clear, but programming in C takes a long time.

JCubeCode is much more friendly to beginners and thanks to everytyhing being
extensively documented, allows the person in question to plop into the header
files and read what parts are wrapped around.

### 🧰 Integrated tooling

JCubeCode updates C with the following:

* CLI
* common utilities
* project manager
* dedicated data format
* data types that wrap a whole problem, such as directories.

Everything is natively integrated within the suite so even the scripts you
write are cross platform.

### 📮 Easy porting

The biggest reason why I didn't write my own language but did this to C is the
fact that C is supported by almost every chip on this planet.

The huge amount of typedefs and macros help the programmer to write the code.
During compilation, the code is cleanly translated right back to C.

That way, you can port easily and write just as easily! Best of both worlds!

## 🔩 How to install 🔩

### ⚙️ Prerequirements

- PC with electricity (assuming as a must have)

- 🐧 **Linux**
	- GNU Make
	- C89 compliant compiler (Tested with GCC and Clang)
	- Bash

- 🪟 **Windows**
	- (TBD)

### 🧰 Process

To install everything, use the convenient install.sh script that automatically
handles everything needed for you.

## 📚 Documentation 📚

JCubeCode Documentation (JCubeWiki) is in the process of being written.
It will be located at [this link.](https://jcubeware.com/jcubecode)

## 🌐 License 🌐

This project is licensed under the MIT license.
Drop it in everywhere you want!

[LICENSE](LICENSE)

## 📚 Current Support 📚

### OS

| Platform | Tested on | Support | Comments |
|----------|-----------|---------|---------|
| Linux | Ubuntu 24.04 | <strong style="color:green">YES</strong> | Native |
| Windows | Windows XP | <strong style="color:yellow">PARTIAL</strong> | No compiler, provided .dll functions |
| MacOS | - | <strong style="color:gray">TBD</strong> | - |
| ChromeOS | - | <strong style="color:gray">TBD</strong> | - |
| FreeBSD | - | <strong style="color:gray">TBD</strong> | - |
| ReactOS | - | <strong style="color:gray">TBD</strong> | - |
| Android | - | <strong style="color:gray">TBD</strong> | - |
| iOS | - | <strong style="color:gray">TBD</strong> | - |

### Embedded

| Platform | Tested on | Support |
|----------|-----------|---------|
| ATmega | - | <strong style="color:gray">TBD</strong> | - |
| STM32 | - | <strong style="color:gray">TBD</strong> | - |
| Raspberry | - | <strong style="color:gray">TBD</strong> | - |
| 6502 | - | <strong style="color:gray">TBD</strong> | - |

Any platforms you want this for? Let me know!

## ❓ What's next ❓

Here are the things that need to be finished in the near future and are still
in the progress.

### 🚧 Project Scope 🚧
| Name | Progress |
|------|----------|
| Windows compilation | <strong><span style="color:yellow">30%</span></strong> |
| Manager GUI | <strong><span style="color:red">5%</span></strong> |
| Online Cube Store | <strong><span style="color:gray">(TBD)</span></strong> |
| JCubeWiki | <strong><span style="color:gray">(TBD)</span></strong> |
| Standalone compiler | <strong><span style="color:gray">(TBD)</span></strong> |
| Own C89 implementation | <strong><span style="color:gray">(TBD)</span></strong> |
| Mail client/server | <strong><span style="color:gray">(TBD)</span></strong> |
| Server backend | <strong><span style="color:gray">(TBD)</span></strong> |
| Scripting language | <strong><span style="color:gray">(TBD)</span></strong> |
| Office tools | <strong><span style="color:gray">(TBD)</span></strong> |

### 🧰 Modules 🧰
| Name | Progress |
|------|----------|
| JCData | <strong><span style="color:yellow">10%</span></strong> |
| Net (Pinging, sockets) | <strong><span style="color:gray">(TBD)</span></strong> |
| GUI (Display, Audio, Input) | <strong><span style="color:gray">(TBD)</span></strong> |
| JCubeCompile | <strong><span style="color:gray">(TBD)</span></strong> |
| File (and related) | <strong><span style="color:yellow">50%</span></strong> |
| Directory (and related) | <strong><span style="color:red">30%</span></strong> |
| Byte (and related) | <strong><span style="color:red">10%</span></strong> |
| String | <strong><span style="color:red">15%</span></strong> |
| Dictionary (or Catalogue) | <strong><span style="color:red">20%</span></strong> |
| Time | <strong><span style="color:gray">(TBD)</span></strong> |
| Thread | <strong><span style="color:gray">(TBD)</span></strong> |
| Socket | <strong><span style="color:gray">(TBD)</span></strong> |
| Hashmap | <strong><span style="color:gray">(TBD)</span></strong> |
| {C++} std::array | <strong><span style="color:gray">(TBD)</span></strong> |
| {C++} Vectors | <strong><span style="color:gray">(TBD)</span></strong> |
| {C++} List | <strong><span style="color:gray">(TBD)</span></strong> |
| {C++} Queue | <strong><span style="color:gray">(TBD)</span></strong> |
| {C++} Deque | <strong><span style="color:gray">(TBD)</span></strong> |
| {C++} Priority Queue| <strong><span style="color:gray">(TBD)</span></strong> |
| {C++} Stack | <strong><span style="color:gray">(TBD)</span></strong> |
| Timer | <strong><span style="color:gray">(TBD)</span></strong> |
