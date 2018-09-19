// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

	//@colored
	//	0 = screen is currently white
	//	1 = screen is currently black

	//@n = 8192 - total number of registers in the screen (w/16) x h = 32 x 256 = 8192

	//LISTEN:
	//	1) Read @KBD
	//		if != 0 - GOTO BLACK
	//		if == 0 - GOTO WHITE
	//	2) GOTO LISTEN -- Shouldn't be needed, but I'll include it just in case.

	//BLACK
	//	1) Read @colored
	//		if != 0 - GOTO LISTEN (screen already black)
	//	2) Set @i = 0
	//	3) Set @new = -1
	//	4) Set @colored = 1
	//	5) GOTO LISTEN

	//WHITE
	//	1) Read @colored
	//		if == 0 - GOTO LISTEN (screen already white)
	//	2) Set @colored, @new, @i = 0
	//	3) GOTO PAINT



//initialize @colored to 0 (white)
@colored				//load colored
M=0						//set colored to 0

//initialize @n to 512
@8192					//load 8192 to save to n
D=A						//copy 8192 as a number
@n						//load n
M=D						//n = 8192

//continuously read @KBD
(LISTEN)
	@KBD				//load KBD
	D=M					//read value of KBD
	@BLACK				//load BLACK for jump
	D; JNE				//JMP if KBD != 0

	@WHITE				//load WHITE for jump
	D; JEQ				//JMP if KBD == 0

	@LISTEN				//load LISTEN for jump
	0; JMP				//loop through LISTEN again

//set screen = black (1)
(BLACK)
	@colored			//load colored
	D=M					//read value of colored
	@LISTEN				//load LISTEN for jump
	D; JNE				//if colored != 0, screen already black, GOTO LISTEN

	@new				//load variable for new screen state
	M=-1				//set new screen state to -1 (black)

	@i					//load loop counter
	M=0					//zero loop counter

	@colored			//load colored
	M=1					//set colored to 1 (to show screen is black)

	@SCREEN				//load screen memory map base address
	D=A					//save base address
	@add_ptr			//load address pointer
	M=D					//add_ptr set to base address

	@PAINT				//load PAINT for jump
	0; JMP				//paint screen

//set screen = white (0)
(WHITE)
	@colored			//load colored
	D=M					//read value of colored
	@LISTEN				//load LISTEN for jump
	D; JEQ				//if colored == 0, screen already white, GOTO LISTEN

	@new				//load variable for new screen state
	M=0					//set new screen state to 0 (white)

	@i					//load loop counter
	M=0					//zero loop counter

	@colored			//load colored
	M=0					//set colored to 0 (to show screen is white)

	@SCREEN				//load screen memory map base address
	D=A					//save base address
	@add_ptr			//load address pointer
	M=D					//add_ptr set to base address

	@PAINT				//load PAINT for jump
	0; JMP				//paint screen

//actually set screen color
(PAINT)
	@i					//load loop counter
	D=M					//store loop counter
	@n					//load number of times to loop (512)
	D=D-M				//times to loop - loop counter
	@LISTEN				//load LISTEN for jump
	D; JGE				//if (i-n)>=0, screen is painted, GOTO LISTEN

	@new				//load new state for screen
	D=M					//save value of @new
	@add_ptr			//load current register pointer
	A=M					//dereference pointer
	M=D					//register = new state

	@i					//load loop counter
	M=M+1				//counter++
	@add_ptr			//load register pointer
	M=M+1				//add_ptr++

	@PAINT				//load PAINT for jump
	0; JMP				//iterate through PAINT again
