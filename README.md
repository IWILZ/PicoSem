# PicoSem
Simple library that implements semaphores to **exchange data between two cores of a Raspberry Pi Pico** under Arduino IDE framework.

The library has been tested only with Raspberry Pi Pico P2040,  Arduino IDE 1.8 and 2.0

![multicore](https://user-images.githubusercontent.com/94467184/227287932-86e3caef-43c6-4c5b-bab0-bbf243b89ef1.jpg)

## **Why this project**
I'm a beginner with the Pi Pico but from the first glance I understood that the processing speed combined with the presence of the 2 cores can provide an interesting potential compared to the Arduino and ESP16 families.

But in order to be able to delegate different tasks to the 2 cores by transferring information produced during their respective processing, it is necessary to have a system of message exchange and synchronization.

On the other hand, I know the Arduino IDE and C/C++ quite well but I don't have skills in other environments and languages and unfortunately on the net I struggled to find useful information regarding the use of Pi Pico in the Aduino environment.

Perhaps the most interesting document is https://arduino-pico.readthedocs.io/en/latest/multicore.html where at the "**Multicore Processing**" chapter is described how to manage the dialogue between the 2 cores through the use of semaphores and FIFO queues but the limitation is that any information size is reduced to a single uint32_t variable.

So for this reason I started thinking about a different solution in which the size of the exchange data buffers could be potentially limited only by the available memory.

## **The concept of this work**
As defined in https://en.wikipedia.org/wiki/Semaphore_(programming), a semaphore is "a variable or abstract data type used to control access to a common resource by multiple threads".

This library uses 2 semaphores and 2 unidirectional data buffers to reach the goal but it's important to underline that each buffer is "one-way" even if is also a "common resource" betwen the 2 cores (one writing and the other reading) and so to make a complete bidirectional data exchange, you will need to define and use 2 different data buffers.

This library employs 2 semaphores (built into the library itself) to allow information to be exchanged between 2 cores by signaling the status of 2 data buffers.
It is important to note that the definition of the 2 buffers is left to the user who thus has the possibility to create them as he likes both in terms of structure and size.

Furthermore, each buffer (although a shared resource) must be used in a "unidirectional" way in the sense that it will be written by one core and read by the other using the library functions to coordinate in carrying out their tasks.

## **Installing the library into Arduino framework**
To install the library:

1. download the "zip" file from GitHub using "Code/Download ZIP" in a folder of your PC
2. open Arduino IDE
3. select "sketch/include library/add ZIP library"
4. go to the folder you used to save the zip and select "PicoSem-main.zip"

Now you should see the PicoSem library in your "**sketch/include library**" list.

## **How to use the library**
**First of all include the header file into your sketch and create an istance with:**
```ruby
#include "PicoSem.h"
#define PICO_EMPTY true
PicoSem Sem(PICO_EMPTY,PICO_EMPTY);
```
**And then you can use the following calls remembering that valid values of `core` are 0 and 1:**
```ruby
void setDataEmptyFor(uint8_t core);
```
Called to say that the data buffer for `core` is empty so is ready to accept a new data set.
```ruby
bool canISendTo(uint8_t core);
```
`true` if i can send a new data set to `core`
```ruby
void setDataReadyFor(uint8_t core);
```
Called to say that i have just written a new data set for `core`
```ruby
void setDataReadBy(uint8_t core);
```
Called to say that i've just read the last data set.
```ruby
bool anyDataFor(uint8_t core);
```
`true` if there is a new data set ready for `core`

**For more info see the examples and enjoy!**
