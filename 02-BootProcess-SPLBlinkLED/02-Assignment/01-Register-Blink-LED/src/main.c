typedef struct
{
    unsigned int CRL;
    unsigned int CRH;
    unsigned int IDR;
    unsigned int ODR;
    unsigned int BSRR;
    unsigned int BRR;
    unsigned int LCKR;
} GPIO_TypeDef;

typedef struct
{
    unsigned int CR;
    unsigned int CFGR;
    unsigned int CIR;
    unsigned int APB2RSTR;
    unsigned int APB1RSTR;
    unsigned int AHBENR;
    unsigned int APB2ENR;
    unsigned int APB1ENR;
    unsigned int BDCR;
    unsigned int CSR;
} RCC_TypeDef;

#define GPIOC ((GPIO_TypeDef *)0x40011000)
#define RCC ((RCC_TypeDef *)0x40021000)

void delay(unsigned int time)
{
    for (unsigned int i = 0; i < time; i++)
        ;
}

void WritePin(GPIO_TypeDef *GPIO_Port, unsigned char Pin, unsigned char state)
{
    if (state == 1)
        GPIO_Port->ODR |= (1 << Pin);
    else
        GPIO_Port->ODR &= ~(1 << Pin);
}

int count = 0;

void GPIO_Config(void)
{
    RCC->APB2ENR |= (1 << 4);

    // PC13
    GPIOC->CRH |= (1 << 20) | (1 << 21);
    GPIOC->CRH &= ~((1 << 22) | (1 << 23));
}

int main(void)
{
    GPIO_Config();
    while (1)
    {
        WritePin(GPIOC, 13, 1);
        delay(1000000);
        WritePin(GPIOC, 13, 0);
        delay(1000000);
        count++;
    }
}
