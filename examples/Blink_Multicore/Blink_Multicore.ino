/* 
  Blink_Multicore
  By Luigi Lavezzaro, 22 March 2023 
  Released into the public domain.
  PicoSem library has been tested only with the Raspberry 
  Pi Pico P2040 under Arduino IDE framework.
  -----------------------------------------------------------------------
  This example demonstrate a simple cooperation and data 
  exchange between the 2 core of a Pi Pico.
  Core0 sends a simple "blink command" to core1 and this 
  light the LED_BUILTIN LED on the board.
  -----------------------------------------------------------------------
  All we need is a small buffer (DataFrom0) and the PicoSem library.
*/
#include "PicoSem.h"      // Simple Pi Pico Semaphore library by L. Lavezzaro
// Even if the library can use a bidirectional msg exchange with 2 semaphores 
// (one for each core) in this example i will use only the buffer 
// from core0 to core1
#define PICO_EMPTY true
PicoSem Sem(PICO_EMPTY,PICO_EMPTY); // Init setting both buffers "empty"
// ------------------ define the buffer ------------------
bool DataFrom0=false;     // true=LED ON, false=LED OFF

#define DELAY_0   200
#define DELAY_1   500

/************************** core 0 *************************/
// ------------------------- setup() ------------------------
void setup(){
  Sem.setDataEmptyFor(1);         // no valid data for core1
  Serial.begin();
  while(!Serial);  
  delay(5000);
  Serial.println("\n------------ Core0 started ------------");
  delay(1000);
} // setup()

// ------------------------- loop() ------------------------
void loop(){
  if(Sem.canISendTo(1)){          // can i send data to core1?
    DataFrom0=!DataFrom0;  
    Sem.setDataReadyFor(1);       // the buffer now contain new data
    Serial.println("core0: sent \""+String(DataFrom0)+"\" to core1...");
  }
  delay(DELAY_0);                 // ... here core0 can do something else ...
} // loop()

/*************************** core 1 *************************/
// ------------------------- setup1() ------------------------
void setup1(){
  pinMode(LED_BUILTIN, OUTPUT);
  delay(8000);                    // wait for Serial ready from core0
  Serial.println("\n------------ Core1 started ------------");
  delay(1000);
} // setup1()

// ------------------------- loop1() ------------------------
void loop1(){
  if(Sem.anyDataFor(1)){          // is there a msg from core0?
    if(DataFrom0) 
      digitalWrite(LED_BUILTIN, HIGH);
    else 
      digitalWrite(LED_BUILTIN, LOW);
    Sem.setDataReadBy(1);         // i'm ready to receive a new msg 
    Serial.println("core1: received \""+String(DataFrom0)+"\" from core0...");
  }
  delay(DELAY_1);                 // ... here core1 can do something else ...
} // loop1()
