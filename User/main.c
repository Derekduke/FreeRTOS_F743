/**
  ******************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   ���ݴ�����-��������
  ******************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32H743������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************
  */  
#include "stm32h7xx.h"
#include "main.h"
#include "./delay/core_delay.h"   
#include "./led/bsp_led.h"  
#include "./lcd/bsp_lcd.h"
#include "./touch/bsp_i2c_touch.h"
#include "./touch/gt9xx.h"
#include "./sdram/bsp_sdram.h"
#include "./mpu/bsp_mpu.h" 
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
/* STemWINͷ�ļ� */
#include "GUI.h"
#include "DIALOG.h"

/**************************** ������ ********************************/
/* 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ�������������������������������Լ�����ô
 * ����������ΪNULL��
 */
/* ���������� */
static TaskHandle_t AppTaskCraete_Handle = NULL;
/* LED������ */
static TaskHandle_t LED_Task_Handle = NULL;
/* Touch������ */
static TaskHandle_t Touch_Task_Handle = NULL;
/* GUI������ */
static TaskHandle_t GUI_Task_Handle = NULL;

/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬�����ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */
SemaphoreHandle_t ScreenShotSem_Handle = NULL;
 
/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */


/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void AppTaskCreate(void);

static void LED_Task(void* parameter);
static void Touch_Task(void* parameter);
static void GUI_Task(void* parameter);

static void BSP_Init(void);
extern void MainTask(void);
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	
	/* ������Ӳ����ʼ�� */
	BSP_Init();
	
	xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,/* ������ں��� */
											 (const char*    )"AppTaskCreate",/* �������� */
											 (uint16_t       )512,					/* ����ջ��С */
											 (void*          )NULL,					/* ������ں������� */
											 (UBaseType_t    )1,						/* ��������ȼ� */
											 (TaskHandle_t   )&AppTaskCraete_Handle);/* ������ƿ�ָ�� */
	/* ����������� */
	if(pdPASS == xReturn)
		vTaskStartScheduler();/* �������񣬿������� */
	else
		return -1;
	
	while(1);/* ��������ִ�е����� */
}

/**
  * @brief ���񴴽�����
  * @note Ϊ�˷���������е����񴴽������������������
  * @param ��
  * @retval ��
  */
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	
	taskENTER_CRITICAL();//�����ٽ���

	xReturn = xTaskCreate((TaskFunction_t)LED_Task,/* ������ں��� */
											 (const char*    )"LED_Task",/* �������� */
											 (uint16_t       )128,       /* ����ջ��С */
											 (void*          )NULL,      /* ������ں������� */
											 (UBaseType_t    )5,         /* ��������ȼ� */
											 (TaskHandle_t   )&LED_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
		printf("����LED1_Task����ɹ���\r\n");
	
	xReturn = xTaskCreate((TaskFunction_t)Touch_Task,/* ������ں��� */
											 (const char*      )"Touch_Task",/* �������� */
											 (uint16_t         )256,     /* ����ջ��С */
											 (void*            )NULL,    /* ������ں������� */
											 (UBaseType_t      )4,       /* ��������ȼ� */
											 (TaskHandle_t     )&Touch_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
		printf("����Touch_Task����ɹ���\r\n");
  
  xReturn = xTaskCreate((TaskFunction_t)GUI_Task,/* ������ں��� */
											 (const char*      )"GUI_Task",/* �������� */
											 (uint16_t         )1024,      /* ����ջ��С */
											 (void*            )NULL,      /* ������ں������� */
											 (UBaseType_t      )3,         /* ��������ȼ� */
											 (TaskHandle_t     )&GUI_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
		printf("����GUI_Task����ɹ���\r\n");
	
	vTaskDelete(AppTaskCraete_Handle);//ɾ��AppTaskCreate����
	
	taskEXIT_CRITICAL();//�˳��ٽ���
}

/**
  * @brief LED��������
  * @note ��
  * @param ��
  * @retval ��
  */
static void LED_Task(void* parameter)
{
	while(1)
	{
//    printf("%d\r\n", (int)GUI_ALLOC_GetNumUsedBytes());
		LED3_TOGGLE;
		vTaskDelay(1000);
	}
}

/**
  * @brief ���������������
  * @note ��
  * @param ��
  * @retval ��
  */
static void Touch_Task(void* parameter)
{
	while(1)
	{
		GT9xx_GetOnePiont();
		vTaskDelay(20);
	}
}

/**
  * @brief GUI��������
  * @note ��
  * @param ��
  * @retval ��
  */
static void GUI_Task(void* parameter)
{
	/* ��ʼ��GUI */
	GUI_Init();
	/* ���������� */
	WM_MULTIBUF_Enable(1);
  
	while(1)
	{
    MainTask();
	}
}

/**
  * @brief �弶�����ʼ��
  * @note ���а����ϵĳ�ʼ�����ɷ��������������
  * @param ��
  * @retval ��
  */
static void BSP_Init(void)
{
  SCB_EnableICache();
  SCB_EnableDCache();
  Board_MPU_Config(0, MPU_Normal_WT, 0x20000000, MPU_REGION_SIZE_128KB);
  Board_MPU_Config(1, MPU_Normal_WT, 0x24000000, MPU_REGION_SIZE_512KB);
  Board_MPU_Config(2, MPU_Normal_WT, 0xD0000000, MPU_REGION_SIZE_32MB);
  
	/* CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı���������
   * ����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ�
   */
  __HAL_RCC_CRC_CLK_ENABLE();
	
	/*
	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
	 * ���ȼ�����ֻ��Ҫ����һ�μ��ɣ��Ժ������������������Ҫ�õ��жϣ�
	 * ��ͳһ��ͬһ�����ȼ����飬ǧ��Ҫ�ٷ��飬�мǡ�
	 */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	
	/* ϵͳʱ�ӳ�ʼ����400MHz */
	SystemClock_Config();
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
	/* ���ô���1Ϊ��115200 8-N-1 */
	UARTx_Config();		
  /* ��ʼ�������� */
  GTP_Init_Panel(); 
  /* ��ʼ��SDRAM ����LCD �Դ�*/
	SDRAM_Init();
	/* LCD �˿ڳ�ʼ�� */ 
	LCD_Init();
}

/**
  * @brief  System Clock ����
  *         system Clock ��������: 
	*            System Clock source  = PLL (HSE)
	*            SYSCLK(Hz)           = 400000000 (CPU Clock)
	*            HCLK(Hz)             = 200000000 (AXI and AHBs Clock)
	*            AHB Prescaler        = 2
	*            D1 APB3 Prescaler    = 2 (APB3 Clock  100MHz)
	*            D2 APB1 Prescaler    = 2 (APB1 Clock  100MHz)
	*            D2 APB2 Prescaler    = 2 (APB2 Clock  100MHz)
	*            D3 APB4 Prescaler    = 2 (APB4 Clock  100MHz)
	*            HSE Frequency(Hz)    = 25000000
	*            PLL_M                = 5
	*            PLL_N                = 160
	*            PLL_P                = 2
	*            PLL_Q                = 4
	*            PLL_R                = 2
	*            VDD(V)               = 3.3
	*            Flash Latency(WS)    = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;
  
  /*ʹ�ܹ������ø��� */
  MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

  /* ��������ʱ��Ƶ�ʵ������ϵͳƵ��ʱ����ѹ���ڿ����Ż����ģ�
		 ����ϵͳƵ�ʵĵ�ѹ����ֵ�ĸ��¿��Բο���Ʒ�����ֲᡣ  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
 
  /* ����HSE������ʹ��HSE��ΪԴ����PLL */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
 
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
	/* ѡ��PLL��Ϊϵͳʱ��Դ����������ʱ�ӷ�Ƶ�� */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK  | \
																 RCC_CLOCKTYPE_HCLK    | \
																 RCC_CLOCKTYPE_D1PCLK1 | \
																 RCC_CLOCKTYPE_PCLK1   | \
                                 RCC_CLOCKTYPE_PCLK2   | \
																 RCC_CLOCKTYPE_D3PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;  
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2; 
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2; 
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2; 
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}
/****************************END OF FILE***************************/

