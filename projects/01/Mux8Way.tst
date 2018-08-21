// Test script for Mux8Way helper chip

load Mux8Way.hdl,
output-file Mux8Way.out,
compare-to Mux8Way.cmp,
output-list a%B3.1.3 b%B3.1.3 c%B3.1.3 d%B3.1.3 e%B3.1.3 f%B3.1.3 g%B3.1.3 h%B3.1.3 sel%B2.3.2 out%B3.1.3;

set a 0,
set b 0,
set c 0,
set d 0,
set e 0,
set f 0,
set g 0,
set h 0,
set sel 0,
eval,
output;

set a 1,
eval,
output;

set a 0,
set b 1,
set sel 1,
eval,
output;

set b 0,
set c 1,
set sel 2,
eval,
output;

set c 0,
set d 1,
set sel 3,
eval,
output;

set d 0,
set e 1,
set sel 4,
eval,
output;

set e 0,
set f 1,
set sel 5,
eval,
output;

set f 0,
set g 1,
set sel 6,
eval,
output;

set g 0,
set h 1,
set sel 7,
eval,
output;
