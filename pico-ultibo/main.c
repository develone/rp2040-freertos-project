#include <FreeRTOS.h>
#include <task.h>
#include <stream_buffer.h>
#include <stdio.h>
#include <queue.h>
#include <string.h>
#include "pico/stdlib.h"
#include "semphr.h"
#include "event_groups.h"

#define STORAGE_SIZE_BYTES 100

#define TASK1_BIT  (1UL << 0UL) //zero
#define TASK2_BIT  (1UL << 1UL) //1
#define TASK3_BIT  (1UL << 2UL) //2
#define TASK4_BIT  (1UL << 3UL) //3
#define TASK5_BIT  (1UL << 4UL) //4
#define TASK6_BIT  (1UL << 5UL) //5

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
size_t Event=0;

static SemaphoreHandle_t mutex;

//EventGroupHandle_t xEventGroupCreate( void);
		/*Declare a variables to hold the created event groups
		#define configUSE_16_BIT_TICKS                  0
		This means the the number of bits(or flags) implemented
		within an event group is 24			
		*/

		EventGroupHandle_t xCreatedEventGroup;

 void led_task(void *pvParameters)
{   
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    uint uIValueToSend = 0;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
				// set flag bit TASK1_BIT
				xEventGroupSetBits(xCreatedEventGroup, TASK1_BIT);    
        gpio_put(LED_PIN, 1);
        uIValueToSend = 1;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(5000);


        gpio_put(LED_PIN, 0);
        uIValueToSend = 0;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(5000);
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
        vTaskDelay(5000);


        gpio_put(LED_PIN, 0);
        uIValueToSend = 0;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(5000);
    }
}
void usb_task(void *pvParameters){
    uint uIReceivedValue;
		
    while(1){
        xQueueReceive(xQueue, &uIReceivedValue, portMAX_DELAY);
				// set flag bit TASK2_BIT
				xEventGroupSetBits(xCreatedEventGroup, TASK2_BIT);			
        if(uIReceivedValue == 1){
            printf("LED is ON! \n");
        }
        if(uIReceivedValue == 0){
            printf("LED is OFF! streamFlag=%d DynStreamBuffer=0x%x \n",streamFlag, DynxStreamBuffer);
						printf("numbytes1=%d numbytes2=%d\n",numbytes1,numbytes2);
						printf("rdnumbytes1=%d Event=%d\n",rdnumbytes1,Event);
						printf("EGroup=0x%x \n",xCreatedEventGroup);
						
						if(rdnumbytes1> 0)
							for(ii=0;ii<rdnumbytes1;ii++) printf("%c ",pucRXData[ii]);
						printf("\n"); 
        }
    }

}


void task1(void *pvParameters)
{   
    char ch = '1';
    while (true) {
				// set flag bit TASK3_BIT
				xEventGroupSetBits(xCreatedEventGroup, TASK3_BIT);
        if(xSemaphoreTake(mutex, 0) == pdTRUE){
            for(int i = 1; i < 10; i++){
                putchar(ch);
            }
            puts("");
            xSemaphoreGive(mutex);
						vTaskDelay(5000);
        }
        
    }
}

void task2(void *pvParameters)
{   
    char ch = '2';
    while (true) {
				// set flag bit TASK4_BIT
				xEventGroupSetBits(xCreatedEventGroup, TASK4_BIT);
        if(xSemaphoreTake(mutex, 0) == pdTRUE){
            for(int i = 1; i < 10; i++){
                putchar(ch);
            }
            puts("");
            xSemaphoreGive(mutex);
						vTaskDelay(5000);
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
	char *pcStringToSend ="String To Send String To Send";
	
	/*numbytes2 14 rdnumbytes1 15
	if the string is uncommneted*/
	//char *pcStringToSend ="String To Send";

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
		mutex = xSemaphoreCreateMutex();



		/*Attempt to create the event groups*/
		xCreatedEventGroup = xEventGroupCreate();
 

		/*Need to test if the Event Group was created*/
    /**************************/

		if(xCreatedEventGroup==NULL) 
		{
			/*The event group was not created*/
		}
		else
		{
			/*The event group was created*/
			Event=1;
		}
 		/*Need to test if the Event Group was created*/
    /**************************/
		const uint SERIAL_BAUD = 1000000;
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
		xTaskCreate(task1, "Task 1", 256, NULL, 1, NULL);
    xTaskCreate(task2, "Task 2", 256, NULL, 1, NULL);
    vTaskStartScheduler();
		

    while(1){};
}
