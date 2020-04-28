/*
   2102 1K SRAM Tester 
   Version 1.0
   Aron Hoekstra 2020
   Released under MIT License
*/


//PINS          Arduino    2102
const int pA0 = A0;     // Addr 0
const int pA1 = A1;     // Addr 1
const int pA2 = A2;     // Addr 2
const int pA3 = A3;     // Addr 3
const int pA4 = A4;     // Addr 4
const int pA5 = A5;     // Addr 5
const int pA6 = 8;      // Addr 6
const int pA7 = 9;      // Addr 7
const int pA8 = 10;     // Addr 8
const int pA9 = 11;     // Addr 9
const int pRW = 12;     // R/W
const int pCE = 13;     // Chip Enable
const int pDO = 4;      // Data Out
const int pDI = 5;      // Data In

int c = 0;

void setup() {
  //Set pin I/O
  pinMode(pA0, OUTPUT);
  pinMode(pA1, OUTPUT);
  pinMode(pA2, OUTPUT);
  pinMode(pA3, OUTPUT);
  pinMode(pA4, OUTPUT);
  pinMode(pA5, OUTPUT);
  pinMode(pA6, OUTPUT);
  pinMode(pA7, OUTPUT);
  pinMode(pA8, OUTPUT);
  pinMode(pA9, OUTPUT);
  pinMode(pRW, OUTPUT);
  pinMode(pCE, OUTPUT);
  pinMode(pDO, INPUT);
  pinMode(pDI, OUTPUT);

  //Disable the chip
  digitalWrite(pRW, HIGH);
  digitalWrite(pCE, HIGH);

  Serial.begin(9600);
  Serial.println("\nTesting 2102...");

  delay(1000);
}

void delay250ns()
{  //4 clock cycles @ 16mhz=250ns
  asm ("NOP");
  asm ("NOP");
  asm ("NOP");
  asm ("NOP");
}

void writeb(int addr, int data) {
  //Set the address bits to write to
  digitalWrite(pA0, bitRead(addr,9));
  digitalWrite(pA1, bitRead(addr,8));
  digitalWrite(pA2, bitRead(addr,7));
  digitalWrite(pA3, bitRead(addr,6));
  digitalWrite(pA4, bitRead(addr,5));
  digitalWrite(pA5, bitRead(addr,4));
  digitalWrite(pA6, bitRead(addr,3));
  digitalWrite(pA7, bitRead(addr,2));
  digitalWrite(pA8, bitRead(addr,1));
  digitalWrite(pA9, bitRead(addr,0));
  //Enable the chip
  digitalWrite(pCE, LOW);
  delay250ns();
  //Enable Write
  digitalWrite(pRW, LOW);
  delay250ns();
  //Write the data (0 or 1) to the SRAM's Input pin
  digitalWrite(pDI, data);
  delay250ns();
  //Latch the data write
  digitalWrite(pRW, HIGH);
  //Disable the chip
  digitalWrite(pCE, HIGH);
}


int readb(int addr) {
  //Set the address bits to read from
  digitalWrite(pA0, bitRead(addr,9));
  digitalWrite(pA1, bitRead(addr,8));
  digitalWrite(pA2, bitRead(addr,7));
  digitalWrite(pA3, bitRead(addr,6));
  digitalWrite(pA4, bitRead(addr,5));
  digitalWrite(pA5, bitRead(addr,4));
  digitalWrite(pA6, bitRead(addr,3));
  digitalWrite(pA7, bitRead(addr,2));
  digitalWrite(pA8, bitRead(addr,1));
  digitalWrite(pA9, bitRead(addr,0));
  delay250ns();
  //Enable the chip
  digitalWrite(pCE, LOW);
  delay250ns();
  //Read the data (0 or 1) from the SRAM's Output pin
  int val = digitalRead(pDO);
  //Disable the chip
  digitalWrite(pCE, HIGH);
  return val;
}

void runTest(int data) {
  //loop through each address to fill the memory
  for (int i=0;i<1024;i++)
  {
    writeb(i,data);
  }

  //loop again and make sure what we read out matches what we wrote
  for (int i=0;i<1024;i++)
  {
    if (readb(i) != data)
    {
      Serial.print("TEST FAILED AT ");
      Serial.println(i);
    }
  } 
}


void loop() {
  runTest(HIGH);
  Serial.println("Test 1111 Complete");
  runTest(LOW);
  Serial.println("Test 0000 Complete"); 
}
