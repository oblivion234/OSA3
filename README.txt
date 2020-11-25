 To run RajcheGirtonA3:

- First Compile the program by running: "g++ -std=c++11 *.cpp"
- Second run the output file "a.out".
- The program will prompt you with "Enter Command: "
- The program excepts 7 commands:
	- M memorySize frameSize
	- A size pid
	- W pid address1
	- R pid address1
	- D pid
	- P
	- Exit
- The last command is to exit the program.
- Our program design uses a lot of global variables to make sure all the functions have access to the same 
information without having to pass that information into the functions. The helps to simulate memory spaces
instead of local variable. The global variables give the feel of actually accessing an area in memory. This allows
us to create a program that is able to create memeory by dynamically allocating and deallocating arrays as well 
as write to these memoery address and read from them. This program demostrates paging with frames and a page table. If
there is not a free frame avialable then the program uses an LRU agorithm to remove the least recently used page number
(victum) in the linked list. 

