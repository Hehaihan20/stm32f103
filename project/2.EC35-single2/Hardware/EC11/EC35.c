#include "EC35.h"


/*
端点接的IO口设置：均采用上拉输入（不接信号时是低电平，用来检测是否有高电平信号输入）
使用外部中断来检测EC11端点电平变化：
中断触发方式：上升沿触发（这也是上面IO口设置成下拉输出入的原因）
中断服务函数：触发中断的端点为高电平时，判断此时另一端点电平状态是高还是低，以此来判断旋转方向是顺时针还是 逆时针。
针对旋转速度大小，可以调节中断服务函数里的延时。


*/


volatile uint16_t angel_count=0;//角度累加
volatile uint8_t encoder_direct_flag=0;//可能的旋转标志。
volatile uint16_t total_angel=once_angel*real_point;//一圈
uint8_t refreshScreen = 1;//刷新屏幕标志位
uint8_t next_menu_flag=0;
void EC11_INIT(void) {
    //端口上拉，当检测端口为高电平的时候（也就是从高到低，下降沿）时候出发中断，
    //检测此时B口的状态，B如果是高电平，则此时是正转动，低电平是反转。
    GPIO_InitTypeDef GPIO_InitStruture;
    RCC_APB2PeriphClockCmd(EC35_GPIO_RCC, ENABLE); //打开A\B时钟
    GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
    GPIO_InitStruture.GPIO_Pin=EC35_A_PIN|EC35_B_PIN;
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(EC35_GPIO,&GPIO_InitStruture);
}
void EXTIX_Init(void) { //中断触发机制
    EXTI_InitTypeDef EXTI_InitStrcuture;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

    EC11_INIT();

    GPIO_EXTILineConfig(EC35_EXTI_A_RCC, EC35_EXTI_A_PIN);//选择信号源

    EXTI_InitStrcuture.EXTI_Line = EC35_A_EXTI_Line;               //中断线选择
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTI为中断模式
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_A_EXTI_Mode;  //下降沿触发
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //使能中断
    EXTI_Init(&EXTI_InitStrcuture);
    //B按钮中断，用来消抖
    GPIO_EXTILineConfig(EC35_EXTI_B__RCC, EC35_EXTI_B_PIN);//选择信号源
    EXTI_InitStrcuture.EXTI_Line = EC35_B_EXTI_Line;               //中断线选择
    EXTI_InitStrcuture.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTI为中断模式
    EXTI_InitStrcuture.EXTI_Trigger = EXTI_B_EXTI_Mode;  //下降沿触发
    EXTI_InitStrcuture.EXTI_LineCmd = ENABLE;                //使能中断
    EXTI_Init(&EXTI_InitStrcuture);



    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		//子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		//子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能外部中断通道

    NVIC_Init(&NVIC_InitStructure);
    EXTI_ClearITPendingBit(EC35_B_EXTI_Line|EC35_A_EXTI_Line);    //清除LINE6上的中断标志位

}
uint16_t get_angel(void) {

    return angel_count;
}
uint8_t get_refreshScreen(void) {

    return refreshScreen;
}
void flag_to_false(void)//把标志位置为false；
{
    refreshScreen=0;
}



//A
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EC35_A_EXTI_Line)!= RESET)//A进入中断，下降沿触发。
    {
        if(EC35_B_STATE == HIGH)
        {
            encoder_direct_flag=1;//可能逆时针
        }
        if(encoder_direct_flag==2&&EC35_B_STATE == LOW) {//第一次和第二次转都是逆时针

            angel_count+=once_angel;
            //保证angel_count++之后结果不能大于360度,故先进行判断
            angel_count=angel_count>total_angel?0:angel_count;
            printf("顺时针\n当前度数为：%d\r\n",get_angel());
            encoder_direct_flag=0;
            refreshScreen=1;
        }				
    }
		
    EXTI_ClearITPendingBit(EC35_A_EXTI_Line);
		
		
		  if(EXTI_GetITStatus(EC35_B_EXTI_Line)!= RESET) { //B进入中断，下降沿触发。
        if(EC35_A_STATE == HIGH)//B先于A触发下降沿，且A是高电平，第一次可能是顺时针
        {
            encoder_direct_flag=2;
        }
        if(encoder_direct_flag==1&&EC35_A_STATE == LOW)//第一次和第二次转都是逆时针
        {
           
            angel_count=angel_count<(once_angel-1)?total_angel+once_angel:angel_count;
            angel_count-=once_angel;
					  printf("逆时针\n当前度数为：%d\r\n",get_angel());
            encoder_direct_flag=0;
            refreshScreen=1;
        }					
    }
    EXTI_ClearITPendingBit(EC35_B_EXTI_Line);    //EC11_B_EXTI_Line

		

}


//void EXTI1_IRQHandler(void) {
//    if(EXTI_GetITStatus(EC35_B_EXTI_Line)!= RESET) { //B进入中断，下降沿触发。
//        if(EC35_A_STATE == HIGH)//B先于A触发下降沿，且A是高电平，第一次可能是顺时针
//        {
//            encoder_direct_flag=2;
//        }
//        if(encoder_direct_flag==1&&EC35_A_STATE == LOW)//第一次和第二次转都是逆时针
//        {
//            
//            angel_count=angel_count<(once_angel-1)?total_angel+once_angel:angel_count;
//            angel_count-=once_angel;
//					  printf("逆时针\n当前度数为：%d\r\n",get_angel());
//            encoder_direct_flag=0;
//            refreshScreen=1;


//        }
//						

//    }

//    EXTI_ClearITPendingBit(EC35_B_EXTI_Line);    //EC11_B_EXTI_Line


//}
