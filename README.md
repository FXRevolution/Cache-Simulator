# Cache-Simulator
L1 LRU or FIFO Cache Simulator

Use the following instructions to run the simulator on your system.

•	Using a Windows or Linux command line terminal, change directory to the folder containing the executable file SIM.exe (i.e. “../SIM/Debug/”)

•	Once in the folder execute the program in the following format:

o	./SIM.exe <cache size bytes> <associativity (pow of 2)> <replacement (0 LRU 1 FIFO)> <WB (0 write-through 1 write-back)> <Trace_File path>

•	The Trace File Path can be the file’s full path with the file name as shown below: 		

*NOTE Please use \\\  instead of \ because the string will not ignore escape characters*

 

•	If the trace file is in the same folder as the executable the file path can be just the filename and extension.

 

•	The trace file must contain input lines in the following format

  o	Read/Write 	Address

  o	R 0x123456789abcdef

  o	W 0xfedcba987654321

•	The program was created using Visual Studios and the solution can be viewed on the platform with minimal configuration.

•	To view the code in Visual Studios go to the project folder “SIM” and open the solution file “SIM.sln” using VS 2017

The Simulator outputs the following values to the console:

Number of Hits

Number of Misses

Hit Ratio

Miss Ratio

Memory Writes

Memory Reads


