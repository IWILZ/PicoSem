# PicoSem
Simple library to exchange data between core0 and core1 of a Raspberry Pi Pico under Arduino IDE framework.

The library has been tested only with Raspberry Pi Pico P2040,  Arduino IDE 1.8 and 2.0.

## **Why this project**
I'm a beginner with the Pi Pico but from the first glance I understood that the processing speed combined with the presence of the 2 cores can provide an interesting potential compared to the Arduino and ESP16 families.

But in order to be able to delegate different tasks to the 2 cores by transferring information produced during their respective processing, it is necessary to have a system of message exchange and synchronization.

On the other hand, I know the Arduino IDE and C/C++ quite well but I don't have skills in other environments and languages and unfortunately on the net I struggled to find useful information regarding the use of Pi Pico in the Aduino environment.

Perhaps the most interesting document is https://arduino-pico.readthedocs.io/en/latest/multicore.html where at the "**Multicore Processing**" chapter is described how to manage the dialogue between the 2 cores through the use of semaphores and FIFO queues but the limitation is that any information size is reduced to a single uint32_t variable.

So for this reason I started thinking about a different solution in which the size of the data exchange buffers could be potentially limited only by the available memory.
