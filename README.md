# PicoSem
Simple library that implements semaphores to **exchange data between two cores of a Raspberry Pi Pico** under Arduino IDE framework.

The library has been tested only with Raspberry Pi Pico P2040,  Arduino IDE 1.8 and 2.0.

## **Why this project**
I'm a beginner with the Pi Pico but from the first glance I understood that the processing speed combined with the presence of the 2 cores can provide an interesting potential compared to the Arduino and ESP16 families.

But in order to be able to delegate different tasks to the 2 cores by transferring information produced during their respective processing, it is necessary to have a system of message exchange and synchronization.

On the other hand, I know the Arduino IDE and C/C++ quite well but I don't have skills in other environments and languages and unfortunately on the net I struggled to find useful information regarding the use of Pi Pico in the Aduino environment.

Perhaps the most interesting document is https://arduino-pico.readthedocs.io/en/latest/multicore.html where at the "**Multicore Processing**" chapter is described how to manage the dialogue between the 2 cores through the use of semaphores and FIFO queues but the limitation is that any information size is reduced to a single uint32_t variable.

So for this reason I started thinking about a different solution in which the size of the exchange data buffers could be potentially limited only by the available memory.

## **How to use the library**
**First of all create an istance with:**
```ruby
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
