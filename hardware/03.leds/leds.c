
#define GPM4CON		(*(volatile unsigned int *)0x110002E0)
#define GPM4DAT		(*(volatile unsigned int *)0x110002E4)


void delay(volatile int d)
{
    while (d--);
}

int main(void)
{
    int i = 0;

    /*
     * ����GPM4_0,GPM4_1,GPM4_2,GPM4_3Ϊ�������
     */
    GPM4CON = 0x1111;

  	/* GPM4_0,GPM4_1,GPM4_2,GPM4_3����͵�ƽ����ɼ��� */
  	while (1)
  	{		
  		GPM4DAT = i;
		if (++i == 16)
  			i = 0;
  		delay(1000000);
  	}


    return 0;
}
