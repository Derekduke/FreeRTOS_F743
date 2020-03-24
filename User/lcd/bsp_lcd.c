/**
  ******************************************************************************
  * @file    bsp_lcd.c
  * @author  fire
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   LCDӦ�ú����ӿڣ�֧��ARGB888/RGB888/RGB565/ARGB4444/ARGB1555 (����������ʾ)
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 H743 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "./lcd/bsp_lcd.h"

LTDC_HandleTypeDef  Ltdc_Handler;
DMA2D_HandleTypeDef Dma2d_Handler;

/**
 * @brief  Initializes the LCD.
 * @param  None
 * @retval None
 */
 /**
  * @brief  ��ʼ������LCD��IO
  * @param  ��
  * @retval ��
  */
static void LCD_GPIO_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
  
  /* ʹ��LCDʹ�õ�������ʱ�� */
                          //��ɫ������
  LTDC_R0_GPIO_CLK_ENABLE();LTDC_R1_GPIO_CLK_ENABLE();LTDC_R2_GPIO_CLK_ENABLE();\
  LTDC_R3_GPIO_CLK_ENABLE();LTDC_R4_GPIO_CLK_ENABLE();LTDC_R5_GPIO_CLK_ENABLE();\
  LTDC_R6_GPIO_CLK_ENABLE();LTDC_R7_GPIO_CLK_ENABLE();LTDC_G0_GPIO_CLK_ENABLE();\
  LTDC_G1_GPIO_CLK_ENABLE();LTDC_G2_GPIO_CLK_ENABLE();LTDC_G3_GPIO_CLK_ENABLE();\
  LTDC_G3_GPIO_CLK_ENABLE();LTDC_G5_GPIO_CLK_ENABLE();LTDC_G6_GPIO_CLK_ENABLE();\
  LTDC_G7_GPIO_CLK_ENABLE();LTDC_B0_GPIO_CLK_ENABLE();LTDC_B1_GPIO_CLK_ENABLE();\
  LTDC_B2_GPIO_CLK_ENABLE();LTDC_B3_GPIO_CLK_ENABLE();LTDC_B4_GPIO_CLK_ENABLE();\
  LTDC_B5_GPIO_CLK_ENABLE();LTDC_B6_GPIO_CLK_ENABLE();LTDC_B7_GPIO_CLK_ENABLE();\
  LTDC_CLK_GPIO_CLK_ENABLE();LTDC_HSYNC_GPIO_CLK_ENABLE();LTDC_VSYNC_GPIO_CLK_ENABLE();\
  LTDC_DE_GPIO_CLK_ENABLE();LTDC_DISP_GPIO_CLK_ENABLE();LTDC_BL_GPIO_CLK_ENABLE();
/* GPIO���� */

 /* ��ɫ������ */                        
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  
  GPIO_InitStruct.Pin =   LTDC_R0_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R0_AF;
  HAL_GPIO_Init(LTDC_R0_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =   LTDC_R1_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R1_AF;
  HAL_GPIO_Init(LTDC_R1_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R2_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R2_AF;
  HAL_GPIO_Init(LTDC_R2_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R3_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R3_AF;
  HAL_GPIO_Init(LTDC_R3_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R4_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R4_AF;
  HAL_GPIO_Init(LTDC_R4_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R5_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R5_AF;
  HAL_GPIO_Init(LTDC_R5_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R6_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R6_AF;
  HAL_GPIO_Init(LTDC_R6_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R7_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R7_AF;
  HAL_GPIO_Init(LTDC_R7_GPIO_PORT, &GPIO_InitStruct);
  
  //��ɫ������
  GPIO_InitStruct.Pin =   LTDC_G0_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_G0_AF;
  HAL_GPIO_Init(LTDC_G0_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =   LTDC_G1_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_G1_AF;
  HAL_GPIO_Init(LTDC_G1_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G2_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G2_AF;
  HAL_GPIO_Init(LTDC_G2_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G3_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G3_AF;
  HAL_GPIO_Init(LTDC_G3_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G4_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G4_AF;
  HAL_GPIO_Init(LTDC_G4_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G5_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G5_AF;
  HAL_GPIO_Init(LTDC_G5_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G6_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G6_AF;
  HAL_GPIO_Init(LTDC_G6_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G7_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G7_AF;
  HAL_GPIO_Init(LTDC_G7_GPIO_PORT, &GPIO_InitStruct);
  
  //��ɫ������
  GPIO_InitStruct.Pin =   LTDC_B0_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B0_AF;
  HAL_GPIO_Init(LTDC_B0_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =   LTDC_B1_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B1_AF;
  HAL_GPIO_Init(LTDC_B1_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B2_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B2_AF;
  HAL_GPIO_Init(LTDC_B2_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B3_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B3_AF;
  HAL_GPIO_Init(LTDC_B3_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B4_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B4_AF;
  HAL_GPIO_Init(LTDC_B4_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B5_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B5_AF;
  HAL_GPIO_Init(LTDC_B5_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B6_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B6_AF;
  HAL_GPIO_Init(LTDC_B6_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B7_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B7_AF;
  HAL_GPIO_Init(LTDC_B7_GPIO_PORT, &GPIO_InitStruct);
  
  //�����ź���
  GPIO_InitStruct.Pin = LTDC_CLK_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_CLK_AF;
  HAL_GPIO_Init(LTDC_CLK_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = LTDC_HSYNC_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_HSYNC_AF;
  HAL_GPIO_Init(LTDC_HSYNC_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = LTDC_VSYNC_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_VSYNC_AF;
  HAL_GPIO_Init(LTDC_VSYNC_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = LTDC_DE_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_DE_AF;
  HAL_GPIO_Init(LTDC_DE_GPIO_PORT, &GPIO_InitStruct);
  
  //����BL ��Һ��ʹ���ź�DISP
  GPIO_InitStruct.Pin = LTDC_DISP_GPIO_PIN;                             
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  
  HAL_GPIO_Init(LTDC_DISP_GPIO_PORT, &GPIO_InitStruct);
  
  
  GPIO_InitStruct.Pin = LTDC_BL_GPIO_PIN; 
  HAL_GPIO_Init(LTDC_BL_GPIO_PORT, &GPIO_InitStruct);
}
/**
  * @brief  ʱ������
  * @retval ��
  */
void LCD_ClockConfig(void)
{
  static RCC_PeriphCLKInitTypeDef  periph_clk_init_struct;

	/* Һ����ʱ������ */
	/* 5�����ĵ���PCLKΪ27 MHz�����PLL3R����Ϊ�ṩ��ʱ�� */ 
	/* AMPIRE640480 LCD clock configuration */
	/* PLL3_VCO Input = HSE_VALUE/PLL3M = 1 Mhz */
	/* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 270 Mhz */
	/* PLLLCDCLK = PLL3_VCO Output/PLL3R = 180/10 = 27Mhz */
	/* LTDC clock frequency = PLLLCDCLK = 18 Mhz */    
	periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	periph_clk_init_struct.PLL3.PLL3M = 25;    
	periph_clk_init_struct.PLL3.PLL3N = 270;
	periph_clk_init_struct.PLL3.PLL3P = 2;
	periph_clk_init_struct.PLL3.PLL3Q = 2;
	periph_clk_init_struct.PLL3.PLL3R = 10;  
	HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);  
}
void LCD_Init(void)
{ 
    /* ʹ��LTDCʱ�� */
    __HAL_RCC_LTDC_CLK_ENABLE();
    /* ʹ��DMA2Dʱ�� */
    __HAL_RCC_DMA2D_CLK_ENABLE();
	  /* Һ����ʱ������ */
		LCD_ClockConfig();
    /* ��ʼ��LCD���� */
    LCD_GPIO_Config();
//    /* ��ʼ��SDRAM ����LCD �Դ�*/
//    SDRAM_Init();
    /* ����LTDC���� */
    Ltdc_Handler.Instance = LTDC;  
    /* ������ͬ���źſ��(HSW-1) */
    Ltdc_Handler.Init.HorizontalSync =HSW-1;
    /* ���ô�ֱͬ���źſ��(VSW-1) */
    Ltdc_Handler.Init.VerticalSync = VSW-1;
    /* ����(HSW+HBP-1) */
    Ltdc_Handler.Init.AccumulatedHBP = HSW+HBP-1;
    /* ����(VSW+VBP-1) */
    Ltdc_Handler.Init.AccumulatedVBP = VSW+VBP-1;
    /* ����(HSW+HBP+��Ч���ؿ��-1) */
    Ltdc_Handler.Init.AccumulatedActiveW = HSW+HBP+LCD_PIXEL_WIDTH-1;
    /* ����(VSW+VBP+��Ч���ظ߶�-1) */
    Ltdc_Handler.Init.AccumulatedActiveH = VSW+VBP+LCD_PIXEL_HEIGHT-1;
    /* �����ܿ��(HSW+HBP+��Ч���ؿ��+HFP-1) */
    Ltdc_Handler.Init.TotalWidth =HSW+ HBP+LCD_PIXEL_WIDTH + HFP-1; 
    /* �����ܸ߶�(VSW+VBP+��Ч���ظ߶�+VFP-1) */
    Ltdc_Handler.Init.TotalHeigh =VSW+ VBP+LCD_PIXEL_HEIGHT + VFP-1;

    /* ��ʼ��LCD�����ؿ�Ⱥ͸߶� */
    Ltdc_Handler.LayerCfg->ImageWidth  = LCD_PIXEL_WIDTH;
    Ltdc_Handler.LayerCfg->ImageHeight = LCD_PIXEL_HEIGHT;
    /* ����LCD���������ɫ��Ĭ�Ϻ�ɫ */
    Ltdc_Handler.Init.Backcolor.Red = 0;
    Ltdc_Handler.Init.Backcolor.Green = 0;
    Ltdc_Handler.Init.Backcolor.Blue = 0;
    /* �������� */
    /* ��ʼ����ͬ�����ԣ��͵�ƽ��Ч */
    Ltdc_Handler.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    /* ��ʼ����ͬ�����ԣ��͵�ƽ��Ч */
    Ltdc_Handler.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    /* ��ʼ��������Ч���ԣ��͵�ƽ��Ч */
    Ltdc_Handler.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    /* ��ʼ��������ʱ�Ӽ��ԣ�ͬ����ʱ�� */
    Ltdc_Handler.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    HAL_LTDC_Init(&Ltdc_Handler);
    
    HAL_LTDC_ProgramLineEvent(&Ltdc_Handler, 0);
      
    /* Enable dithering */
    HAL_LTDC_EnableDither(&Ltdc_Handler);
    
    /* Set LTDC Interrupt to the lowest priority */
    HAL_NVIC_SetPriority(LTDC_IRQn, 0, 0);  
    /* Enable LTDC Interrupt */
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
  
     /* Configure the DMA2D default mode */ 
    Dma2d_Handler.Init.Mode         = DMA2D_R2M;
    Dma2d_Handler.Init.ColorMode    = DMA2D_INPUT_ARGB8888;
    Dma2d_Handler.Init.OutputOffset = 0x0;     

    Dma2d_Handler.Instance          = DMA2D; 

    if(HAL_DMA2D_Init(&Dma2d_Handler) != HAL_OK)
    {
      while (1);
    }
}

///**
//  * @brief  ��ʼ��LCD�� 
//  * @param  LayerIndex:  ǰ����(��1)���߱�����(��0)
//  * @param  FB_Address:  ÿһ���Դ���׵�ַ
//  * @param  PixelFormat: ������ظ�ʽ
//  * @retval ��
//  */
//void LCD_LayerInit(uint16_t LayerIndex, uint32_t FB_Address,uint32_t PixelFormat)
//{     
//  LTDC_LayerCfgTypeDef  layer_cfg;

//  /* ���ʼ�� */
//  layer_cfg.WindowX0 = 0;				//������ʼλ��X����
//  layer_cfg.WindowX1 = LCD_GetXSize();	//���ڽ���λ��X����
//  layer_cfg.WindowY0 = 0;				//������ʼλ��Y����
//  layer_cfg.WindowY1 = LCD_GetYSize();  //���ڽ���λ��Y����
//  layer_cfg.PixelFormat = PixelFormat;	//���ظ�ʽ
//  layer_cfg.FBStartAdress = FB_Address; //���Դ��׵�ַ
//  layer_cfg.Alpha = 255;				//���ڻ�ϵ�͸���ȳ�������Χ��0��255��0Ϊ��ȫ͸��
//  layer_cfg.Alpha0 = 0;					//Ĭ��͸���ȳ�������Χ��0��255��0Ϊ��ȫ͸��
//  layer_cfg.Backcolor.Blue = 0;			//�㱳����ɫ��ɫ����
//  layer_cfg.Backcolor.Green = 0;		//�㱳����ɫ��ɫ����
//  layer_cfg.Backcolor.Red = 0;			//�㱳����ɫ��ɫ����
//  layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;//����ϵ��1
//  layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;//����ϵ��2
//  layer_cfg.ImageWidth = LCD_GetXSize();//����ͼ����
//  layer_cfg.ImageHeight = LCD_GetYSize();//����ͼ��߶�
//  
//  HAL_LTDC_ConfigLayer(&Ltdc_Handler, &layer_cfg, LayerIndex); //����ѡ�еĲ����

//  DrawProp[LayerIndex].BackColor = LCD_COLOR_WHITE;//���ò��������ɫ
//  DrawProp[LayerIndex].pFont     = &LCD_DEFAULT_FONT;//���ò����������
//  DrawProp[LayerIndex].TextColor = LCD_COLOR_BLACK; //���ò�����屳����ɫ
//  
//  __HAL_LTDC_RELOAD_CONFIG(&Ltdc_Handler);//���ز�����ò���
//}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
