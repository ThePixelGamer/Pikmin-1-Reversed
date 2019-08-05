<h1 align="center"> Distant Forest </hr>

## Table of Contents

* **What is this?**
	- A faithful recreation of the Pikmin 1 debug programs source code.
		- Using the same tools and compiler available back in 2001 when the program was being developed.
		- And has the compiled ASM compared side-by-side for accuracy and veracity.


* **Overview** 
	- This project provides compileable, readable code that has been reverse engineered from the debug .exe and accompanying .dll(s).
	- It was created with improvement in mind, and as we get closer to completely RE'ing the executable files we will improve the program so that we may be able to uncover some hidden secrets embedded within.

* **File names**	
	- Inside each of the 4 folders contains everything we have reversed from the exectuable in seperate `.cpp` and `.h` files for easy access/reading.
		- Note: some folders currently contain nothing, because we simply haven't gotten around to creating the projects / decompiling the appropriate functions
	
	**DLL names**
	
	- `sysCore` is the main .dll that is `imported` by all of the other .dlls and `sysBootup.exe`.
		- This .dll is the most important, which explains the size of the folder and the size of the .dll.
		
	- `sysBootup` is the .exe of the project, it has the capability to load the seperate .dll files and is what initialises everything within `sysCore`.
	
	- `plugTexConv` is the .dll we know least about, it is assumed that it could convert formats to/from the file formats of Pikmin 1.
	
	- `plugAtxServer` is literally a server, but is by far the most intruiging because it has hidden functionality that accesses most of `sysCore.dll`
	

# Setup

* **NOTE: you will need a Windows XP ISO, or a machine that has Windows XP installed***
	- The first and only tool that we'll need is a Visual Studio 6.0 ISO, or installer, to get that go [here and download it](https://winworldpc.com/product/microsoft-visual-stu/60)
	- Once that is done, find a suitable directory and download the project (using GIT or the internet) into that folder.
	- Then open up any of the 4 folders we currently have, and open the .dsp project file, and... violá! You're ready to start reversing!


