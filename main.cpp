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
int mode, mode_next, j, Generate;
Thread thread;
AnalogIn Ain_s(A3);
int sample = 100;
float ADCdata[1000];

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
            //fre = 1;
            uLCD.locate(0,0);
            //uLCD.color(RED);
            uLCD.printf("\n1/8\n");
            /*uLCD.locate(0,2);
            uLCD.color(GREEN);
            uLCD.printf("\n1/4\n");
            uLCD.printf("\n1/2\n");
            uLCD.printf("\n1\n");*/
        }
        else if(mode_next == 2)
        {
            //fre = 0.36;
            uLCD.locate(0,0);
            /*uLCD.color(GREEN);
            uLCD.printf("\n1/8\n");
            uLCD.locate(0,2);*/
            //uLCD.color(RED);
            uLCD.printf("\n1/4\n");
            /*uLCD.color(GREEN);
            uLCD.printf("\n1/2\n");
            uLCD.printf("\n1\n");*/
        }
        else if(mode_next == 3){
            fre = 0.036;
            uLCD.locate(0,0);
            /*uLCD.color(GREEN);
            uLCD.printf("\n1/8\n");
            uLCD.locate(0,2);
            uLCD.color(GREEN);
            uLCD.printf("\n1/4\n");*/
            //uLCD.color(RED);
            uLCD.printf("\n1/2\n");
            //uLCD.printf("\n1\n");
        }
        else if(mode_next == 4){
            fre = 0.036;
            uLCD.locate(0,0);
            /*uLCD.color(GREEN);
            uLCD.printf("\n1/8\n");
            uLCD.locate(0,2);
            uLCD.color(GREEN);
            uLCD.printf("\n1/4\n");
            uLCD.locate(0,4);
            uLCD.color(GREEN);
            uLCD.printf("\n1/2\n");*/
            //uLCD.color(RED);
            uLCD.printf("\n1             \n");
        }
        ThisThread::sleep_for(50ms);
     }
 }


int main()
{
    mode = 1;
    mode_next = 1;
    thread.start(mode_thread);
    Up.rise(&U);
    down.rise(&D);
    confirm.rise(&S);

    while(1) 
    {
        if(Generate == 1){      // 1HZ
            for(i = 0, j = 0; i <= 0.91; i=i+0.03033)
            {
                Aout = i;
                ADCdata[j] = Ain_s.read()*3.3;
                ThisThread::sleep_for(10ms);
                j = j + 1;
            }
            // Make 'aout' go from 1 to 0, in 100 steps of 0.01
            for(i = 0.91; i >= 0; i=i-0.013)
            {
                Aout = i;
                ADCdata[j] = Ain_s.read()*3.3;
                ThisThread::sleep_for(10ms);
                j = j + 1;
            }  
            for (j = 0; j <=100; j++)
            {
                printf("%f\r\n", ADCdata[j]);
            }
        }
        if(Generate == 2){  // 0.36HZ
            for(i = 0, j = 0; i <= 0.91; i=i+0.03033)
            {
                Aout = i;
                ADCdata[j] = Ain_s.read()*3.3;
                ThisThread::sleep_for(27ms);
                j = j +1;
            }
            // Make 'aout' go from 1 to 0, in 100 steps of 0.01
            for(i = 0.91; i >= 0; i=i-0.013)
            {
                Aout = i;
                ADCdata[j] = Ain_s.read()*3.3;
                ThisThread::sleep_for(27ms);
                j = j + 1;
            }  
            for (j = 0; j <=100; j++)
            {
                printf("%f\r\n", ADCdata[j]);
            }
        }
        if(Generate == 3){      // 0.036HZ
            for(i = 0, j = 0; i <= 0.91; i=i+0.03033)
            {
                Aout = i;
                ADCdata[j] = Ain_s.read()*3.3;
                ThisThread::sleep_for(270ms);
                j = j + 1;
            }
            // Make 'aout' go from 1 to 0, in 100 steps of 0.01
            for(i = 0.91; i >= 0; i=i-0.013)
            {
                Aout = i;
                ADCdata[j] = Ain_s.read()*3.3;
                ThisThread::sleep_for(270ms);
                j = j + 1;
            }  
            for (j = 0; j <=100; j++)
            {
                printf("%f\r\n", ADCdata[j]);
            }
        }
    }
}