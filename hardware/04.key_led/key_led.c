
#define GPM4CON     (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT     (*(volatile unsigned int *)0x110002E4)

#define GPX3CON     (*(volatile unsigned int *)0x11000C60)
#define GPX3DAT     (*(volatile unsigned int *)0x11000C64)

int main(void)
{
    int val;
    int i;
    
    /*
     * ����GPM4_0,GPM4_1,GPM4_2,GPM4_3Ϊ�������
     * ��ӦLED1/2/3/4
     */
    GPM4CON = 0x1111;

    /* ����K1��K2��K3��K4��Ӧ��GPIO(GPX3_2��GPX3_3��GPX3_4��GPX3_5)Ϊ���� */
    GPX3CON &= ~((0xf << 8) | (0xf << 12) | (0xf << 16) | (0xf << 20));
        
    while (1)
    {
        val = GPX3DAT;           /* ������������״̬ */
        
        for (i = 2; i <= 5; i++)
        {
            if (val & (1<<i)) /* ĳ���������ɿ�״̬ : �ߵ�ƽ */
            {
                /* Ϩ���ӦLED : GPIO����ߵ�ƽ */
                GPM4DAT |= (1 << (i - 2));
            }   
            else
            {
                /* ���������ӦLED : GPIO����͵�ƽ */
                GPM4DAT &= ~(1 << (i - 2));
            }
        }
     }

    return 0;
}
