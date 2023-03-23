/* 
  Bidirectional_Multicore
  By Luigi Lavezzaro, 22 March 2023 
  Released into the public domain.
  PicoSem library has been tested only with the Raspberry 
  Pi Pico P2040 under Arduino IDE framework.
  --------------------------------------------------------------------
  Example of bidirectional data exchange between core0 and core1.
  --------------------------------------------------------------------
  All we need are 2 buffers and the PicoSem library.
    DataFrom0  --> data buffer written by core0 and read by core1
    DataFrom1  --> data buffer written by core1 and read by core0
*/
#include "PicoSem.h"      // Simple Pi Pico Semaphore library by L. Lavezzaro

#define NUM_BYTES   64
#define DELAY_0     1     // delay of core0 is different from delay of core1
#define DELAY_1     2     // delay of core1 is different from delay of core0
#define PICO_EMPTY  false
PicoSem Sem(PICO_EMPTY,PICO_EMPTY); // Init setting both buffers "empty"

// ------------------ global vars used by both cores ------------------
struct dataType {
  int   NPacket;                  // index of packet
  char  DataString[NUM_BYTES];    // packet of data
};
dataType DataFrom0, DataFrom1;

/************************** core 0 *************************/
// ------------------------- setup() ------------------------
void setup(){
  Sem.setDataEmptyFor(1);         // no data yet for core1
  Serial.begin(115200);
  while(!Serial);  
  delay(5000);
  Serial.println("\n------------ Core0 started ------------");
  delay(1000);
} // setup()

// ------------------------- loop() ------------------------
void loop(){
static int count=1;

  if(Sem.canISendTo(1)){          // can i send data to core1?
    sprintf(DataFrom0.DataString,"0-->1 String N. %d",count);
    DataFrom0.NPacket=count;
    Sem.setDataReadyFor(1);       // The buffer now is full
    if(count%100==0) 
      Serial.println("Core0 loop N."+String(count));
    count++;
  }
  ChkDataForCore0();              // scan DataFrom1
  delay(DELAY_0);                 // ... do something else ...
} // loop()

// ------------------------- ChkDataForCore0() ------------------------
void ChkDataForCore0(){
static int prev_data_number=0;
int np;
char str[NUM_BYTES];

  if(Sem.anyDataFor(0)){          // are there data ready from core1?
    strcpy(str,DataFrom1.DataString); // i read the data...
    np=DataFrom1.NPacket;
    Sem.setDataReadBy(0);         // ...and now the buffer is "empty" 
    
    // now i can examine what i've received checking if is orrect
    if (np==prev_data_number+1){  // received what was expected?
      prev_data_number=np;
    }
    else{
      Serial.println("core1 ERROR - received \""+String(str)+"\"");
      Serial.println(String(np)+" instead of "+String(prev_data_number+1));
      Serial.println("----------- CORE 0 STOP -----------");
      for(;;){}                   // STOP program
    }
  }
} // ChkDataForCore0()

/*************************** core 1 *************************/
// ------------------------- setup1() ------------------------
void setup1(){
  Sem.setDataEmptyFor(0);         // no data yet for core0
  delay(8000);
  Serial.println("\n------------ Core1 started ------------");
  delay(1000);
} // setup1()

// ------------------------- loop1() ------------------------
void loop1(){
static int count=1;

  if(Sem.canISendTo(0)){          // can i send data to core0?
    sprintf(DataFrom1.DataString,"0-->1 String N. %d",count);
    DataFrom1.NPacket=count;
    Sem.setDataReadyFor(0);       // The buffer now is full
    if(count%100==0) 
      Serial.println("Core1 loop N."+String(count));
    count++;
  }
  ChkDataForCore1();              // scan DataFrom0
  delay(DELAY_1);                 // ... do something else ...
} // loop1()

// ------------------------- ChkDataForCore1() ------------------------
void ChkDataForCore1(){
static int prev_data_number=0;
int np;
char str[NUM_BYTES];

  if(Sem.anyDataFor(1)){          // are there data ready from core0?
    strcpy(str,DataFrom0.DataString); // i read the data...
    np=DataFrom0.NPacket;
    Sem.setDataReadBy(1);         // ...and now the buffer is "empty" 
    // now i can examine what i've received checking if is orrect
    if (np==prev_data_number+1){  // received what was expected?
      prev_data_number=np;
    }
    else{
      Serial.println("core1 ERROR - received \""+String(str)+"\"");
      Serial.println(String(np)+" instead of "+String(prev_data_number+1));
      Serial.println("----------- CORE 1 STOP -----------");
      for(;;){}                   // STOP program
    }
  }
} // ChkDataForCore1()
