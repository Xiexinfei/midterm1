#include "mbed.h"
#include <stdio.h>
#include "uLCD_4DGL.h"
using namespace std::chrono;


uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
InterruptIn down(A0);
InterruptIn Up(A1);
InterruptIn confirm(A2);
AnalogOut Aout(D7); // Declare pin 18 as an analog out
double i;
double fre; // Declare a float to range between 0 and 1
int mode, mode_next, j, Generate, k;
Thread thread;
AnalogIn Ain_s(A3);
int sample = 100;
float ADCdata[1000];

EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

void D()
{
    if(mode > 1){
        mode_next = mode - 1;
    }
    else{
        mode_next = mode;
    }
    mode = mode_next;
}

void U()
{
    if(mode < 4){
        mode_next = mode + 1;
    }
    else{
        mode_next = mode;
    }
    mode = mode_next;
}
void S()
{
    mode = mode_next;
    Generate = mode;
}
void mode_thread()
 {
     while(1){
        if(mode_next == 1){  
            uLCD.locate(0,0);
            uLCD.printf("\n1/8\n");
        }
        else if(mode_next == 2)
        {
            uLCD.locate(0,0);
            uLCD.printf("\n1/4\n");
        }
        else if(mode_next == 3){
            fre = 0.036;
            uLCD.locate(0,0);
            uLCD.printf("\n1/2\n");
        }
        else if(mode_next == 4){
            fre = 0.036;
            uLCD.locate(0,0);
            uLCD.printf("\n1             \n");
        }
        ThisThread::sleep_for(50ms);
     }
 }
void Sample(){
    mode = mode_next;
    Generate = mode;
    for (j = 0; j <= 500; j++){
        ADCdata[j] = Ain_s.read()*3.3;
        printf("%f\r\n", ADCdata[j]);//ADCdata[j]);
        wait_us(300);
    }
}

int main()
{
    mode = 1;
    mode_next = 1;
    thread.start(mode_thread);
    Up.rise(&U);
    down.rise(&D);

    confirm.rise(queue.event(Sample));
    t.start(callback(&queue, &EventQueue::dispatch_forever));


    while(1) 
    {
        if(Generate == 4){      // 1HZ
            for(i = 0, j = 0; i <= 1; i=i+0.0625)
            {
                Aout = 0.91 * i;
                ThisThread::sleep_for(4ms);
            }
            for(i = 0.91, k = 0; k <= 8; k = k + 1){
                Aout = 0.91;
                ThisThread::sleep_for(10ms);
            }
            
            for(i = 0.91; i >= 0; i=i-0.0625)
            {
                Aout = 0.91 * i;
                ThisThread::sleep_for(4ms);
            }  
        }
        if(Generate == 3){  // 1/2HZ
            for(i = 0, j = 0; i <= 0.91; i=i+0.056875)
            {
                Aout = i * 0.91;
                wait_us(1500);
            }
            for(i = 0.91, k = 0; k <= 16; k = k + 1){
                Aout = 0.91;
                ThisThread::sleep_for(10ms);
            }
            
            for(i = 0.91; i >= 0; i=i-0.0625)
            {
                Aout = i * 0.91;
                wait_us(1500);
            }  
        }
        if(Generate == 2){      // 1/4HZ
            for(i = 0, j = 0; i <= 0.91; i=i+0.0625)
            {
                Aout = i * 0.91;
                ThisThread::sleep_for(1ms);
            }
            for(i = 0.91, k = 0; k <= 20; k = k + 1){
                Aout = 0.91;
                ThisThread::sleep_for(10ms);
            }
            
            for(i = 0.91; i >= 0; i=i-0.0625)
            {
                Aout = i * 0.91;
                ThisThread::sleep_for(1ms);
            }  
        }
                if(Generate == 1){      // 1/8HZ
            for(i = 0, j = 0; i <= 1; i=i+0.0625)
            {
                Aout = i * 0.91;
                wait_us(500);
            }
            for(i = 0.91, k = 0; k <= 22; k = k + 1){
                Aout = 0.91;
                ThisThread::sleep_for(10ms);
            }
             
            for(i = 0.91; i >= 0; i=i-0.0625)
            {
                Aout = i * 0.91;
                wait_us(500);
            }  
        }
    }
}