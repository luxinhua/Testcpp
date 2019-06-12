// GPIO
#define GPA0CON				(*(volatile unsigned int *)0x11400000)
#define GPA1CON				(*(volatile unsigned int *)0x11400020)
// system clock
#define CLK_SRC_PERIL0		(*(volatile unsigned int *)0x1003C250)
#define CLK_DIV_PERIL0		(*(volatile unsigned int *)0x1003C550)
// UART
#define ULCON0				(*(volatile unsigned int *)0x13800000)
#define UCON0				(*(volatile unsigned int *)0x13800004)
#define UBRDIV0				(*(volatile unsigned int *)0x13800028)
#define UFRACVAL0			(*(volatile unsigned int *)0x1380002c)
#define UTXH0				(*(volatile unsigned int *)0x13800020)
#define URXH0				(*(volatile unsigned int *)0x13800024)
#define UTRSTAT0				(*(volatile unsigned int *)0x13800010)

void uart_init(void)
{
	/* 1.������Ӧ��GPIO���ڴ��ڹ��� */
	GPA0CON = 0x22222222;
	GPA1CON = 0x222222;

	/* 2.����SCLK_UART */
	/*
		PWM_SEL = 0;
		UART5_SEL = 0;
		UART4_SEL = 6;		// ����ʱ��Դѡ SCLKMPLL_USER_T
		UART3_SEL = 6;
		UART2_SEL = 6;
		UART1_SEL = 6;
		UART0_SEL = 6;
	*/
	CLK_SRC_PERIL0 = ((0 << 24) | (0 << 20) | (6 << 16) | (6 << 12) | (6<< 8) | (6 << 4)	| (6));
	/*
		��Ƶϵ�� = 7+1 = 8
	*/
	CLK_DIV_PERIL0 = ((7 << 20) | (7 << 16) | (7 << 12) | (7 << 8) | (7 << 4) | (7));

	/* 3.���ô���0��� */
	/* bit[1:0]:0x3 = 8λ����λ
	 * ����λĬ��,��1λֹͣλ����У�飬����ģʽ
	 */
	ULCON0 = 0x3;

	/*
	 * Receive Mode [1:0]:1 = ���ղ��ò�ѯ�����ж�ģʽ
	 * Transmit Mode[3:2]:1 = ���Ͳ��ò�ѯ�����ж�ģʽ
	 * bit[6]:1 = ���������ж�
	 * bit[10]:0 = ʱ��ԴΪPCLK
	 */
	UCON0 = (1<<6)|(1<<2)|(1<<0);

	/* ���ò����� */
	UBRDIV0 = 0x35;
	UFRACVAL0 = 0x4;
}

char getc(void)
{
	char c;
	/* ��ѯ״̬�Ĵ�����ֱ������Ч���� */
	while (!(UTRSTAT0 & (1<<0)));
	
	c = URXH0; /* ��ȡ���ռĴ�����ֵ */
		
	return c;
}

void putc(char c)
{
	/* ��ѯ״̬�Ĵ�����ֱ�����ͻ���Ϊ�� */
	while (!(UTRSTAT0 & (1<<2)));
	
	UTXH0 = c; /* д�뷢�ͼĴ��� */
	
	return;
}

