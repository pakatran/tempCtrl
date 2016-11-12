/**
 * @tempCtrl.ino
 * @author  Panos Katranitsas (email:<pkat@outlook.com>)
 * @date    2016/11/12
 */

#include "Nextion.h"

void p001PopCallback(void *ptr);
void n101PopCallback(void *ptr);
void b103PopCallback(void *ptr);
void b104PopCallback(void *ptr);

/* Declare page number */
uint8_t pOff = 0;
uint8_t pMain = 1;
uint8_t pFine = 2;
uint8_t pSetup = 3;


/* Declare objects [page id:x,component id:y, component name: "zi"] */

NexPicture p001 = NexPicture(pOff, 1, "p0"); /* pOff, On-Off picture*/

NexNumber n100 = NexNumber(pMain, 5, "n0"); /* pMain, temp measurement*/
NexNumber n101 = NexNumber(pMain, 9, "n1"); /* pMain, temp target*/
NexButton b103 = NexButton(pMain, 14, "b0"); /* pMain, temp decrements*/
NexButton b104 = NexButton(pMain, 15, "b1"); /* pMain, temp increments*/

char buffer[100] = {0};

/*
 * Register object t0, b0, b1, to the touch event list.  
 */
NexTouch *nex_listen_list[] = 
{
    &p001,
    &n100,
    &n101,
    &b103,
    &b104,
    NULL
};

/*
 * Component pop callback function. 
 */
void p001PopCallback(void *ptr)
{
    n100.setValue(17);
    n101.setValue(18);
}
 
void n100PopCallback(void *ptr)
{
    n100.setValue(18);
}

void n101PopCallback(void *ptr)
{
    n101.setValue(18);
}

/*
 * Button0 component pop callback function.
 * In this example,the value of the text component will plus one every time when button0 is released.
 */
void b103PopCallback(void *ptr)
{
    uint32_t number;

    n101.getValue(&number);
    --number;
    n101.setValue(number);
}

/*
 * Button1 component pop callback function.
 * In this example,the value of the text component will minus one every time when button1 is released.
 */
void b104PopCallback(void *ptr)
{
    uint32_t number;

    n101.getValue(&number);
    ++number;
    n101.setValue(number);
}

void setup(void)
{
    /* Set the baudrate which is for debug and communicate with Nextion screen. */
    nexInit();

    /* Register the pop event callback function of the components */
    p001.attachPop(p001PopCallback);
    n100.attachPop(n100PopCallback);
    n101.attachPop(n101PopCallback);
    b103.attachPop(b103PopCallback);
    b104.attachPop(b104PopCallback);
}

void loop(void)
{
    /*
     * When a pop or push event occured every time, 
     * the corresponding component[right page id and component id] in touch event list will be asked.
     */
    nexLoop(nex_listen_list);
}

