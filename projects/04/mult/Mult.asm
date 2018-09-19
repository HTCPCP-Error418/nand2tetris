// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

//  n = R0;		--number to add each iteration (ex. 2 in 2x3)
//  m = R1;		--number of times to loop (ex. 3 in 2x3)
//  for(count = 0, sum = 0; count <= m; count++) {
//      sum = sum + n;
//  }
//  R2 = sum;

// n = R0
@R0         	//load R0
D=M         	//save value at R0 to D
@n          	//load variable n
M=D         	//set n to D (value of R0)

// m = R1
@R1         	//load R1
D=M         	//save value of R1 to D
@m          	//load variable m
M=D         	//set m to D (value of R1)

// R2 = 0
@R2				//load R2
M=0				//R2 = 0

// count = 0
@count      	//load variable count
M=0         	//set count to 0

// sum = 0
@sum        	//load variable sum
M=0				//set sum to 0

//loop to add needed number of multiples
(LOOP)
	//check for stop condition
	@m			//load number of times to loop
	D=M			//save number to D
	@count		//load number of times loop has executed
	D=D-M		//D = m - count
	@STOP
	D; JLE		//if count >= m, stop

	//add another multiple
	@sum		//load sum
	D=M			//load sum into D
	@n			//load n
	D=D+M		//D = sum + n
	@sum		//load sum
	M=D			//@sum = sum

	//increment counter
	@count		//load count
	M=M+1		//increment count
	@LOOP
	0; JMP		//jump back to the beginning of the loop

//after loop is done, save sum to R2
(STOP)
	@sum		//load sum
	D=M			//copy value of @sum to D
	@R2			//load R2
	M=D			//R2 = sum

//end with infinite loop
(END)
	@END
	0; JMP
