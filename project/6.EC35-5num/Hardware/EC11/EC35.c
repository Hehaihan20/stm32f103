#include "EC35.h"


/*
�˵�ӵ�IO�����ã��������������루�����ź�ʱ�ǵ͵�ƽ����������Ƿ��иߵ�ƽ�ź����룩
ʹ���ⲿ�ж������EC11�˵��ƽ�仯��
�жϴ�����ʽ�������ش�������Ҳ������IO�����ó�����������ԭ��
�жϷ������������жϵĶ˵�Ϊ�ߵ�ƽʱ���жϴ�ʱ��һ�˵��ƽ״̬�Ǹ߻��ǵͣ��Դ����ж���ת������˳ʱ�뻹�� ��ʱ�롣
�����ת�ٶȴ�С�����Ե����жϷ����������ʱ��


*/


volatile uint16_t angel_count=0;//�Ƕ��ۼ�

volatile uint8_t encoder_direct_flag=0;//���ܵ���ת��־��//menu
volatile uint16_t total_angel=once_angel*real_point;//һȦ


uint8_t refreshScreen = 1;//ˢ����Ļ��־λ



uint8_t next_menu_flag=0;


void EC11_INIT(void) {
    //�˿������������˿�Ϊ�ߵ�ƽ��ʱ��Ҳ���ǴӸߵ��ͣ��½��أ�ʱ������жϣ�
    //����ʱB�ڵ�״̬��B����Ǹߵ�ƽ�����ʱ����ת�����͵�ƽ�Ƿ�ת��
    GPIO_InitTypeDef GPIO_InitStruture;
    RCC_APB2PeriphClockCmd(EC35_GPIO_RCC, ENABLE); //��A\Bʱ��
    GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;//��������
    GPIO_InitStruture.GPIO_Pin=EC35_A1_PIN|EC35_B1_PIN;
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(EC35_GPIO,&GPIO_InitStruture);
	
   //��A\Bʱ��
    GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;//��������
    GPIO_InitStruture.GPIO_Pin=EC35_A2_PIN|EC35_B2_PIN;
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(EC35_GPIO,&GPIO_InitStruture);
	
}
void EXTIX_Init(void) { //�жϴ�������
    EXTI_InitTypeDef EXTI_InitStrcuture;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

    EC11_INIT();
	
		
   /**********GROUP0**********/
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_A0_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_A0_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_A_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
    //B��ť�жϣ���������
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_B0_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_B0_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_B_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
	
	
	
   /**********GROUP1**********/
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_A1_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_A1_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_A_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
    //B��ť�жϣ���������
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_B1_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_B1_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_B_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);

    /**********GROUP2*********/

    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_A2_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_A2_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_A_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
    //B��ť�жϣ���������
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_B2_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_B2_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_B_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
    
		/**********GROUP3************/	
		
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_A3_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_A3_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_A_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
    //B��ť�жϣ���������
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_B3_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_B3_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_B_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
    
		/**********GROUP4************/
		
		
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_A4_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_A4_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_A_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
    //B��ť�жϣ���������
    GPIO_EXTILineConfig(EC35_EXTI_RCC, EC35_EXTI_B4_PIN);//ѡ���ź�Դ
    EXTI_InitStrcuture.EXTI_Line = EC35_B4_EXTI_Line;               //�ж���ѡ��
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_B_EXTI_Mode;  //�½��ش���
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStrcuture);
	
		
		
		
		
		
		/*===============================================================NVIC=================================================*/
		/**********GROUP0************/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EC35_A0_EXTI_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);
			
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EC35_B0_EXTI_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);
		
 	 /**********GROUP12************/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EC35_12_EXTI_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);
		
 
 	 /**********GROUP34************/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EC35_34_EXTI_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);



		
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		//�����ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);

   EXTI_ClearITPendingBit(EC35_B1_EXTI_Line|EC35_A1_EXTI_Line|EC35_B2_EXTI_Line|EC35_A2_EXTI_Line);    //���LINE6�ϵ��жϱ�־λ

}
uint16_t get_angel(void) {

    return angel_count;
}
uint8_t get_refreshScreen(void) {

    return refreshScreen;
}
void flag_to_false(void)//�ѱ�־λ��Ϊfalse��
{
    refreshScreen=0;
}





//GROP1


void EXTI0_IRQHandler(void)

{   
       /*****GROUP-0 edit menu*****/
    if(EXTI_GetITStatus(EC35_A0_EXTI_Line)!= RESET)//A�����жϣ��½��ش�����
    {
        if(EC35_B0_STATE == HIGH)
        {
            encoder_direct_flag=1;//������ʱ��
        }
        if(encoder_direct_flag==2&&EC35_B0_STATE == LOW) {//��һ�κ͵ڶ���ת������ʱ��

            angel_count+=once_angel;
            //��֤angel_count++֮�������ܴ���360��,���Ƚ����ж�
            angel_count=angel_count>total_angel?0:angel_count;
            printf("˳ʱ��\n��ǰ����Ϊ��%d\r\n",get_angel());
					  printf("��ǰmenuΪ��%d\r\n",angel_count);
            encoder_direct_flag=0;
            refreshScreen=1;
        }				
    }	
    EXTI_ClearITPendingBit(EC35_A0_EXTI_Line);
		


}

void EXTI1_IRQHandler(void){
		  if(EXTI_GetITStatus(EC35_B0_EXTI_Line)!= RESET) { //B�����жϣ��½��ش�����
        if(EC35_A0_STATE == HIGH)//B����A�����½��أ���A�Ǹߵ�ƽ����һ�ο�����˳ʱ��
        {
            encoder_direct_flag=2;
        }
        if(encoder_direct_flag==1&&EC35_A0_STATE == LOW)//��һ�κ͵ڶ���ת������ʱ��
        {
           
            angel_count=angel_count<(once_angel-1)?total_angel+once_angel:angel_count;
            angel_count-=once_angel;
					  printf("��ʱ��\n��ǰ����Ϊ��%d\r\n",get_angel());
            encoder_direct_flag=0;
            refreshScreen=1;
        }					
    }
    EXTI_ClearITPendingBit(EC35_B0_EXTI_Line);    //EC11_B_EXTI_Line
}


//
void EXTI9_5_IRQHandler(void)
{   
          /*****GROUP-1  edit menu*****/
    if(EXTI_GetITStatus(EC35_A1_EXTI_Line)!= RESET)//A�����жϣ��½��ش�����
    {
        if(EC35_B1_STATE == HIGH)
        {
            encoder_direct_flag=1;//������ʱ��
        }
        if(encoder_direct_flag==2&&EC35_B1_STATE == LOW) {//��һ�κ͵ڶ���ת������ʱ��

            EC1_CW_ACTIVE();
            encoder_direct_flag=0;
        
        }				
    }
		
     EXTI_ClearITPendingBit(EC35_A1_EXTI_Line);
		
		
		  if(EXTI_GetITStatus(EC35_B1_EXTI_Line)!= RESET) { //B�����жϣ��½��ش�����
        if(EC35_A1_STATE == HIGH)//B����A�����½��أ���A�Ǹߵ�ƽ����һ�ο�����˳ʱ��
        {
            encoder_direct_flag=2;
        }
        if(encoder_direct_flag==1&&EC35_A1_STATE == LOW)//��һ�κ͵ڶ���ת������ʱ��
        {
           
            EC1_CWW_ACTIVE();
            encoder_direct_flag=0;
        
        }					
    }
    EXTI_ClearITPendingBit(EC35_B1_EXTI_Line);    //EC11_B_EXTI_Line
		
		
		   /*****GROUP-2 usb*****/
		
		if(EXTI_GetITStatus(EC35_A2_EXTI_Line)!= RESET)//A�����жϣ��½��ش�����
    {
        if(EC35_B2_STATE == HIGH)
        {
            encoder_direct_flag=1;//������ʱ��
        }
        if(encoder_direct_flag==2&&EC35_B2_STATE == LOW) {//��һ�κ͵ڶ���ת������ʱ��
            EC2_CW_ACTIVE();
            encoder_direct_flag=0;

        }				
    }
		
     EXTI_ClearITPendingBit(EC35_A2_EXTI_Line);
		
		  if(EXTI_GetITStatus(EC35_B2_EXTI_Line)!= RESET) { //B�����жϣ��½��ش�����
        if(EC35_A2_STATE == HIGH)//B����A�����½��أ���A�Ǹߵ�ƽ����һ�ο�����˳ʱ��
        {
            encoder_direct_flag=2;
        }
        if(encoder_direct_flag==1&&EC35_A2_STATE == LOW)//��һ�κ͵ڶ���ת������ʱ��
        {
           
					  EC2_CWW_ACTIVE();
            encoder_direct_flag=0;

        }					
    }
    EXTI_ClearITPendingBit(EC35_B2_EXTI_Line);    //EC11_B_EXTI_Line


}
void EXTI15_10_IRQHandler(void)
{   
          /*****GROUP-3  edit menu*****/
    if(EXTI_GetITStatus(EC35_A3_EXTI_Line)!= RESET)//A�����жϣ��½��ش�����
    {
        if(EC35_B3_STATE == HIGH)
        {
            encoder_direct_flag=1;//������ʱ��
        }
        if(encoder_direct_flag==2&&EC35_B3_STATE == LOW) {//��һ�κ͵ڶ���ת������ʱ��

            EC3_CW_ACTIVE();
            encoder_direct_flag=0;
        
        }				
    }
		
     EXTI_ClearITPendingBit(EC35_A3_EXTI_Line);
		
		
		  if(EXTI_GetITStatus(EC35_B3_EXTI_Line)!= RESET) { //B�����жϣ��½��ش�����
        if(EC35_A3_STATE == HIGH)//B����A�����½��أ���A�Ǹߵ�ƽ����һ�ο�����˳ʱ��
        {
            encoder_direct_flag=2;
        }
        if(encoder_direct_flag==1&&EC35_A3_STATE == LOW)//��һ�κ͵ڶ���ת������ʱ��
        {
           
            EC3_CWW_ACTIVE();
            encoder_direct_flag=0;
        
        }					
    }
    EXTI_ClearITPendingBit(EC35_B3_EXTI_Line);    //EC11_B_EXTI_Line
		
		
		   /*****GROUP-4 usb*****/
		
		if(EXTI_GetITStatus(EC35_A4_EXTI_Line)!= RESET)//A�����жϣ��½��ش�����
    {
        if(EC35_B4_STATE == HIGH)
        {
            encoder_direct_flag=1;//������ʱ��
        }
        if(encoder_direct_flag==2&&EC35_B4_STATE == LOW) {//��һ�κ͵ڶ���ת������ʱ��
            EC4_CW_ACTIVE();
            encoder_direct_flag=0;

        }				
    }
		
     EXTI_ClearITPendingBit(EC35_A4_EXTI_Line);
		
		  if(EXTI_GetITStatus(EC35_B4_EXTI_Line)!= RESET) { //B�����жϣ��½��ش�����
        if(EC35_A4_STATE == HIGH)//B����A�����½��أ���A�Ǹߵ�ƽ����һ�ο�����˳ʱ��
        {
            encoder_direct_flag=2;
        }
        if(encoder_direct_flag==1&&EC35_A4_STATE == LOW)//��һ�κ͵ڶ���ת������ʱ��
        {
           
					  EC4_CWW_ACTIVE();
            encoder_direct_flag=0;

        }					
    }
    EXTI_ClearITPendingBit(EC35_B4_EXTI_Line);    //EC11_B_EXTI_Line


}






