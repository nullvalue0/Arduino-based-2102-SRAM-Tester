# Arduino-based-2102-SRAM-Tester
Tests 1K Static RAM (2102) chips simply using an Arduino UNO and a few wires.

During a vintage computer restoration project, I needed to test 64 individual 1K SRAM chips. I developed this routine using an Arduino UNO (though I'm sure others will work - will need 14 digital I/O pins). Hookup is very straightforward with no additional hardware required. The test tests each address with both a 0 and 1. If any error occurs, the address where the failure occured will be printed in the serial console. The code itself is very simplistic and verbose. I did this on purpose to make it readable for others. There may be more complete/elegant ways of testing RAM, however this did help me track down the 1 bad chip in my lot.
