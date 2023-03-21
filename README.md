# IPK 2022/2023

## Goal
According to the assignment, you need to create an application communicating via a network. You can implement what is not explicitly stated in the assignment according to your choice but describe significant design decisions in the documentation.

## Coding Instructions
The Project 1 will be developed in C/C++, C# or Common Lisp, the Project 2 in C/C++ or C# languages. If you decide to implement the project in C++, let it be by the C++20 standard. If you decide to implement the project in C#, make your implementation is .NET 6+ compatible and out-of-the-box runnable on the reference virtual machine with the provided developer environment active. Common Lisp implementations will be tested using SBCL.

*Makefile* is mandatory for all project variants and programming languages. Compilation of your projects will be done by calling `make`. For C/C++, compiling with *Makefile* is native, for C# you can call the standard `dotnet build` in the appropriate phony. For Common Lisp, you can call `(asdf:make)`. The goal of using *Makefile* is to make the compilation of projects agnostic to the programming language used.

Among the allowed libraries are:

### C/C++
* BSD sockets API
* libpcap
* libnet
* or any standard header files present on the reference machine (e.g., arpa/inet.h)
* any testing framework of your choice
* any utility library not directly solving the core of the project, assuming you include it directly with your source code

### C#
* anything included in the base SDK
* any NuGet package not directly solving the core of the project
* SharpPCAP
* XUnit

### Common Lisp
* alexandria
* clingon
* iterate
* str
* usocket
* lisp-unit2
* slynk

The project should be as portable and multi-platform as possible (e.g., try to show it at least once somewhere in your code that you are aware of specifics between Windows and Unix operating systems).

Project source codes should be usable and meaningful, adequately annotated and formatted, and broken down into functions and modules. The program should include help to inform the user about the program's operation and parameters. Any errors will be intuitively described to the user. In no case shall the application terminate with a `SEGMENTATION FAULT` or other violent system termination (e.g., division by zero).

An essential part of this project is demonstrating your software engineering skills. Please, use *private* [Git](https://git-scm.com/) repository on the faculty [Gitea portal](https://git.fit.vutbr.cz/) when versioning your project, to which you will give access to all [IPK instructors](https://www.fit.vut.cz/study/course/231006/.en). Your repository should have multiple commits (preferably using [semantic commit messages](https://www.conventionalcommits.org/en/v1.0.0/)) illustrating your development history. 

## Submission Instructions
The project archive (and repo as well) needs to contain at least the following mandatory files:

* all project source codes and stand-alone libraries;
* working *Makefile*, which will compile or build the executable binary (with the filename specified in the assignment) from the source codes;
* documentation written in Markdown in the file *README.md*;
* the license in the file *LICENSE* with the most restrictive (i.e., preserving maximum rights of you as the author) commonly recognized open-source license you can find;
* *CHANGELOG.md* will contain a brief description of implemented functionality and known limitations (a documented problem is better than an undocumented one).

Please, verify following steps for successful submission of your projects:

0) check whether your code successfully compiles/builds under the reference developer environment and check filename syntax of mandatory files;
1) upload ZIP (and only ZIP) archive with filename `xlogin99.zip` containing the snapshot of your Gitea repo with all mandatory files (see above);
2) give access to your private Gitea repo to logins `veselyv`, `koutenmi`, `dolejska` and `izavrel`.

We will ignore any submission via email (or any other communication channel) after the deadline.

## Documentation Instructions
Good documentation should include the following:
* content structuring;
* executive summary of the theory necessary to understand the functionality of the implemented application;
* UML diagrams or at least a narrative about interesting source code sections;
* most importantly testing part, which should prove that you have done some validation and verification of implemented functionality;
* description of extra functionality or features beyond the standard outlined by the assignment;
* bibliography with the list of all used sources.

Documentation or code comments can be in the following languages: Czech, Slovak, or English.

The section of the documentation describing testing should be sound and reproducible (e.g., accurate description of network topology and involved hardware specification and software versions). Testing should include at least a few runs of your application testing proper functionality and various edge cases. Please, compare your project with another similar tool (if such exists). Testing proofs can have the form of textual program outputs, screenshots or screencasts. 

When working with any bibliography or sources on the Internet, please cite according to [faculty guidelines](https://www.fit.vut.cz/study/theses/citations/.en). It is worth to read also this [web page](http://www.fit.vutbr.cz/~martinek/latex/citace.html) by David Martinek. 

When adopting or inserting snippets of someone else's source code into your project, you need to use them according to the author's license terms. Moreover, you need to mark this source code and reference the author explicitly in your source files.

## Developer Environment and Virtualization Remarks
The individual assignment specifies a custom reference environment, located in `./Devenv`. To not waste resources with language toolchains you don't need, the reference environment is separate from the provided virtual machine, and activated on-demand for a particular language.

To use the developer environment, you can use the virtual machines located at [FIT Nextcloud](https://nextcloud.fit.vutbr.cz/s/YTxbDiCxFjHL29o)
(hosted by e.g., [VMWare Player](https://www.vmware.com/products/workstation-player.html) or [VirtualBox](https://www.virtualbox.org/) or [Hyper-V](https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/about/)). The user login is `ipk` with password `ipk`.
Alternatively, you can install [Nix, the package manager](https://nixos.org/download.html#nix-install-linux) on your own machine.

There are three developer environments provided:
- `c`
- `csharp`
- `clisp`

To activate the environment, clone this repository and run `nix develop ./Devenv#csharp` from the repository root (replace `csharp` with the environment of choice).
You can edit the environment definitions (to, e.g., add JetBrains Rider, add `jetbrains.rider` to the `packages` list; to add a C library for testing, add it to the `buildInputs` list; search for packages [here](https://search.nixos.org/packages?channel=22.11)). However, your *Makefile* should work with the default, unedited environment.

Due to the nature of the projects, you can assume that:
* the project will be run and tested with root privileges,
* reference machine will be connected to the Internet.

## Evaluation
You can get up to 13 points for working applications in compliance with the assignment. You can get up to 7 points for documentation and demonstrating good programmer skills on the project. 

You can earn extra points for extending features of your program. You cannot get more than 20 points from the project, but the points for extra effort can help you minimize any losses during the assignment evaluation of standard requirements.

Common criteria for the evaluation:
* unstructured, uncommented or spaghetti source code = up to -7 points
* non-functioning or missing Makefile = up to -4 points
* missing or poor documentation = up to -7 points
* wrong bibliography = up to -2 points
* missing testing of the project = up to -3 points
* wrong binary filename = up to -2 points
* temporary or irrelevant files inside the submitted archive = up to -2 points
* the project cannot be compiled, executed or tested = 0 points
* the project is not in compliance with the assignment = 0 points
* plagiarism = 0 points for all involved parties

----

## Project 1
### Deadlines
Tuesday 21st March 2023 at 23:59:59

### Languages
* C/C++, C#, Common Lisp

### Variants
* Client for remote calculator

----

## Project 2
### Deadlines
Monday 17th April 2023 at 23:59:59 

### Languages
* C/C++, C#

### Variants
Students of 2BIT (i.e., students in the second year of the BIT bachelor's program) can choose from any non-ALPHA variant. Students of 3BIT (i.e., all non-2BIT students such as students of 3rd and later years) can register for either the ALPHA or the IOTA variant. The reason behind this restriction is that no student of the IPK course will have the same project twice.

* ALPHA: Last year's points from project 2
* [DELTA: L2/L3 scanner](https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Project%202/delta)
* [OMEGA: L4 scanner](https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Project%202/omega)
* [ZETA: Network sniffer](https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Project%202/zeta)
* [IOTA: Server for remote calculator (mandatory for 3BIT+)](https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Project%202/iota)

