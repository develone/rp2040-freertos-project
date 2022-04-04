#include <FreeRTOS.h>
#include <task.h>
#include <stream_buffer.h>
#include <stdio.h>
#include <queue.h>
#include "pico/stdlib.h"

#define STORAGE_SIZE_BYTES 100

/*Used to dimension the array used to hold the streams.
The availble space is 1 less than this */
static uint8_t ucBufferStorage[STORAGE_SIZE_BYTES];

/*The varaible used to hold the stream buffer structure*/
StaticStreamBuffer_t xStreamBufferStruct;

//StreamBufferHandle_t xStreamBuffer;
StreamBufferHandle_t DynxStreamBuffer;

//const size_t xStreamBufferSizeBytes = 100,xTriggerLevel = 10;
//xStreamBuffer = xStreamBufferCreate(xStreamBufferSizeBytes,xTriggerLevel);
static QueueHandle_t xQueue = NULL;

int streamFlag,ii;
size_t numbytes1;
size_t numbytes2;
uint8_t * pucRXData;
size_t rdnumbytes1;

void led_task(void *pvParameters)
{   
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    uint uIValueToSend = 0;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);
        uIValueToSend = 1;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(50000);


        gpio_put(LED_PIN, 0);
        uIValueToSend = 0;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(50000);
    }
}

void scanline_task(void *pvParameters)
{   
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    uint uIValueToSend = 0;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);
        uIValueToSend = 1;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(100);


        gpio_put(LED_PIN, 0);
        uIValueToSend = 0;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        //vTaskDelay(100);
    }
}
void usb_task(void *pvParameters){
    uint uIReceivedValue;
		
    while(1){
        xQueueReceive(xQueue, &uIReceivedValue, portMAX_DELAY);
				
        if(uIReceivedValue == 1){
            printf("LED is ON! \n");
        }
        if(uIReceivedValue == 0){
            printf("LED is OFF! streamFlag=%d DynStreamBuffer=0x%x \n",streamFlag, DynxStreamBuffer);
						printf("numbytes1=%d numbytes2=%d\n",numbytes1,numbytes2);
						printf("rdnumbytes1=%d\n",rdnumbytes1);
						if(rdnumbytes1> 0)
							for(ii=0;ii<rdnumbytes1;ii++) printf("%d ",pucRXData[ii]); 
        }
    }

}

/*Tries to create a StreamBuffer of 100 bytes and blocks after 10*/
void vAFunction(void){
	StreamBufferHandle_t xStreamBuffer;
	const size_t xStreamBufferSizeBytes = 100,xTriggerLevel = 10;
	xStreamBuffer = xStreamBufferCreate(xStreamBufferSizeBytes,xTriggerLevel);

	if(xStreamBuffer==NULL)
	{
		streamFlag=0;
	}
	else
	{
		streamFlag=1;
		DynxStreamBuffer=xStreamBuffer;
  }
}


void MyFunction(void) {
	StreamBufferHandle_t xStreamBuffer;
	const size_t xTriggerLevel = 1;
	xStreamBuffer = xStreamBufferCreateStatic( sizeof(ucBufferStorage),
	xTriggerLevel,
  ucBufferStorage,
  &xStreamBufferStruct);
}


void vASendStream(StreamBufferHandle_t DynxStreamBuffer) {
	size_t xByteSent;
	uint8_t ucArrayToSend = (0,1,2,3);
	
	/*numbytes2 29 rdnumbytes1 30
	if the string is uncommneted*/
	//char *pcStringToSend ="String To Send String To Send";
	
	/*numbytes2 14 rdnumbytes1 15
	if the string is uncommneted*/
	char *pcStringToSend ="String To Send";

	const TickType_t x100ms = pdMS_TO_TICKS(100);

	xByteSent = xStreamBufferSend( DynxStreamBuffer,(void *) ucArrayToSend,
	sizeof(ucArrayToSend),x100ms);
	numbytes1=xByteSent;

	if(xByteSent != sizeof(ucArrayToSend)) 
	{

	}
	xByteSent = xStreamBufferSend( DynxStreamBuffer,(void *) pcStringToSend ,
	strlen(pcStringToSend ),0);
  numbytes2=strlen(pcStringToSend);

	if(xByteSent != strlen(pcStringToSend ))
	{

	}
}


void vAReadStream(StreamBufferHandle_t xStreamBuffer) 
{
	int i;	
	uint8_t ucRXData[40];
	size_t xRecivedBytes;
	const TickType_t xBlockTime = pdMS_TO_TICKS(20);
	pucRXData = &ucRXData;
	xRecivedBytes = xStreamBufferReceive(DynxStreamBuffer,
	(void *) ucRXData,sizeof(ucRXData),
xBlockTime);
	rdnumbytes1=xRecivedBytes;
	i=0;
	if (xRecivedBytes > 0)
	{
	printf("%d ",ucRXData[i]);
	i++;
	}
}

int main()
{
    
		stdio_init_all();
		
    xQueue = xQueueCreate(1, sizeof(uint));
		/*Setting the streamFlag to 0 before the call of vAFunction
		if the stream was successful the streamFlag will be set to 1		
		*/
		streamFlag=0;
		vAFunction();
		vASendStream(DynxStreamBuffer);
    vAReadStream(DynxStreamBuffer); 
 		//MyFunction();

    
		xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(usb_task, "USB_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();
		

    while(1){};
}