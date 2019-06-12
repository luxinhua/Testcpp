#define GPM4CON		(*(volatile unsigned int *)0x110002E0)
#define GPM4DAT		(*(volatile unsigned int *)0x110002E4)

/* ��ʱ�������� */
void delay()
{
	volatile int i = 0x10000;
	while (i--);
}

int main(void)
{
	int i = 0;

	/* ����GPM4_0,GPM4_1,GPM4_2,GPM4_3Ϊ������� */
	GPM4CON = 0x1111;

	/* GPM4_0,GPM4_1,GPM4_2,GPM4_3����͵�ƽ����ɼ��� */
	while (1)
	{		
		GPM4DAT = i;
		i++;
		if (i == 16)
			i = 0;
		delay();
	}

	return 0;
}

