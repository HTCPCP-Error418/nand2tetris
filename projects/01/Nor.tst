// Test script for the Nor helper chip

load Nor.hdl,
output-file Nor.out,
compare-to Nor.cmp,
output-list a%B3.1.3 b%B3.1.3 out%B3.1.3;

set a 0,
set b 0,
eval,
output;

set b 1,
eval,
output;

set b 0,
set a 1,
eval,
output;

set b 1,
eval,
output;
