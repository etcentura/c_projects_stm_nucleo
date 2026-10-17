#include "stm32f103xb.h"
// Look at line 507 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the USART register to init state
  * @retval None
  */
void init_USART(USART_TypeDef *USART_p)
{
    USART_p->SR     =   0x000000C0;  
    USART_p->DR     =   0x00000000;  
    USART_p->BRR    =   0x00000000; 
    USART_p->CR1    =   0x00000000; 
    USART_p->CR2    =   0x00000000; 
    USART_p->CR3    =   0x00000000; 
    USART_p->GTPR   =   0x00000000;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set USART SR register field
  * @retval None
  */
void set_USART_SR_field(USART_TypeDef *USART_p, unsigned int val)
{
    USART_p->SR |= val;
}

/**
  * @brief Common fuction to get USART SR register field
  * @retval int as the register value
  */
int get_USART_SR_field(USART_TypeDef *USART_p, unsigned int pos, unsigned int msk)
{
    return (USART_p->SR & msk) >> pos;
}

/**
  * @brief Common fuction to clear USART SR register field
  * @retval None
  */
void clear_USART_SR_field(USART_TypeDef *USART_p, unsigned int msk)
{
    USART_p->SR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set USART DR register field
  * @retval None
  */
void set_USART_DR_field(USART_TypeDef *USART_p, unsigned int val)
{
    USART_p->DR = val;
}

/**
  * @brief Common fuction to get USART DR register field
  * @retval int as the register value
  */
int get_USART_DR_field(USART_TypeDef *USART_p, unsigned int pos, unsigned int msk)
{
    return (USART_p->DR & msk) >> pos;
}

/**
  * @brief Common fuction to clear USART DR register field
  * @retval None
  */
void clear_USART_DR_field(USART_TypeDef *USART_p, unsigned int msk)
{
    USART_p->DR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set USART BRR register field
  * @retval None
  */
void set_USART_BRR_field(USART_TypeDef *USART_p, unsigned int val)
{
    USART_p->BRR |= val;
}

/**
  * @brief Common fuction to get USART BRR register field
  * @retval int as the register value
  */
int get_USART_BRR_field(USART_TypeDef *USART_p, unsigned int pos, unsigned int msk)
{
    return (USART_p->BRR & msk) >> pos;
}

/**
  * @brief Common fuction to clear USART BRR register field
  * @retval None
  */
void clear_USART_BRR_field(USART_TypeDef *USART_p, unsigned int msk)
{
    USART_p->BRR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set USART CR1 register field
  * @retval None
  */
void set_USART_CR1_field(USART_TypeDef *USART_p, unsigned int val)
{
    USART_p->CR1 |= val;
}

/**
  * @brief Common fuction to get USART CR1 register field
  * @retval int as the register value
  */
int get_USART_CR1_field(USART_TypeDef *USART_p, unsigned int pos, unsigned int msk)
{
    return (USART_p->CR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear USART CR1 register field
  * @retval None
  */
void clear_USART_CR1_field(USART_TypeDef *USART_p, unsigned int msk)
{
    USART_p->CR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set USART CR2 register field
  * @retval None
  */
void set_USART_CR2_field(USART_TypeDef *USART_p, unsigned int val)
{
    USART_p->CR2 |= val;
}

/**
  * @brief Common fuction to get USART CR2 register field
  * @retval int as the register value
  */
int get_USART_CR2_field(USART_TypeDef *USART_p, unsigned int pos, unsigned int msk)
{
    return (USART_p->CR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear USART CR2 register field
  * @retval None
  */
void clear_USART_CR2_field(USART_TypeDef *USART_p, unsigned int msk)
{
    USART_p->CR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set USART CR3 register field
  * @retval None
  */
void set_USART_CR3_field(USART_TypeDef *USART_p, unsigned int val)
{
    USART_p->CR3 |= val;
}

/**
  * @brief Common fuction to get USART CR3 register field
  * @retval int as the register value
  */
int get_USART_CR3_field(USART_TypeDef *USART_p, unsigned int pos, unsigned int msk)
{
    return (USART_p->CR3 & msk) >> pos;
}

/**
  * @brief Common fuction to clear USART CR3 register field
  * @retval None
  */
void clear_USART_CR3_field(USART_TypeDef *USART_p, unsigned int msk)
{
    USART_p->CR3 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set USART GTPR register field
  * @retval None
  */
void set_USART_GTPR_field(USART_TypeDef *USART_p, unsigned int val)
{
    USART_p->GTPR |= val;
}

/**
  * @brief Common fuction to get USART GTPR register field
  * @retval int as the register value
  */
int get_USART_GTPR_field(USART_TypeDef *USART_p, unsigned int pos, unsigned int msk)
{
    return (USART_p->GTPR & msk) >> pos;
}

/**
  * @brief Common fuction to clear USART GTPR register field
  * @retval None
  */
void clear_USART_GTPR_field(USART_TypeDef *USART_p, unsigned int msk)
{
    USART_p->GTPR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////