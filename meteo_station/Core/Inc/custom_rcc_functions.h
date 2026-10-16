#include "stm32f103xb.h"
// Look at line 907 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the RCC register to init state
  * @retval None
  */
void init_RCC(RCC_TypeDef *RCC_p)
{
    RCC_p->CR         = 0x00000083;
    RCC_p->CFGR       = 0x00000000;
    RCC_p->CIR        = 0x00000000;
    RCC_p->APB2RSTR   = 0x00000000;
    RCC_p->APB1RSTR   = 0x00000000;
    RCC_p->AHBENR     = 0x00000014;
    RCC_p->APB2ENR    = 0x00000000;
    RCC_p->APB1ENR    = 0x00000000;
    RCC_p->BDCR       = 0x00000000;
    RCC_p->CSR        = 0x00000000;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC CR register field
  * @retval None
  */
void set_RCC_CR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->CR |= val;
}

/**
  * @brief Common fuction to get RCC CR register field
  * @retval int as the register value
  */
int get_RCC_CR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->CR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC CR register field
  * @retval None
  */
void clear_RCC_CR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->CR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC CFGR register field
  * @retval None
  */
void set_RCC_CFGR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->CFGR |= val;
}

/**
  * @brief Common fuction to get RCC CFGR register field
  * @retval int as the register value
  */
int get_RCC_CFGR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->CFGR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC CFGR register field
  * @retval None
  */
void clear_RCC_CFGR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->CFGR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC CIR register field
  * @retval None
  */
void set_RCC_CIR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->CIR |= val;
}

/**
  * @brief Common fuction to get RCC CIR register field
  * @retval int as the register value
  */
int get_RCC_CIR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->CIR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC CIR register field
  * @retval None
  */
void clear_RCC_CIR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->CIR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC APB2RSTR register field
  * @retval None
  */
void set_RCC_APB2RSTR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->APB2RSTR |= val;
}

/**
  * @brief Common fuction to get RCC APB2RSTR register field
  * @retval int as the register value
  */
int get_RCC_APB2RSTR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->APB2RSTR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC APB2RSTR register field
  * @retval None
  */
void clear_RCC_APB2RSTR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->APB2RSTR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC APB1RSTR register field
  * @retval None
  */
void set_RCC_APB1RSTR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->APB1RSTR |= val;
}

/**
  * @brief Common fuction to get RCC APB1RSTR register field
  * @retval int as the register value
  */
int get_RCC_APB1RSTR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->APB1RSTR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC APB1RSTR register field
  * @retval None
  */
void clear_RCC_APB1RSTR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->APB1RSTR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC AHBENR register field
  * @retval None
  */
void set_RCC_AHBENR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->AHBENR |= val;
}

/**
  * @brief Common fuction to get RCC AHBENR register field
  * @retval int as the register value
  */
int get_RCC_AHBENR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->AHBENR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC AHBENR register field
  * @retval None
  */
void clear_RCC_AHBENR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->AHBENR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC APB2ENR register field
  * @retval None
  */
void set_RCC_APB2ENR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->APB2ENR |= val;
}

/**
  * @brief Common fuction to get RCC APB2ENR register field
  * @retval int as the register value
  */
int get_RCC_APB2ENR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->APB2ENR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC APB2ENR register field
  * @retval None
  */
void clear_RCC_APB2ENR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->APB2ENR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC APB1ENR register field
  * @retval None
  */
void set_RCC_APB1ENR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->APB1ENR |= val;
}

/**
  * @brief Common fuction to get RCC APB1ENR register field
  * @retval int as the register value
  */
int get_RCC_APB1ENR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->APB1ENR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC APB1ENR register field
  * @retval None
  */
void clear_RCC_APB1ENR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->APB1ENR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC BDCR register field
  * @retval None
  */
void set_RCC_BDCR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->BDCR |= val;
}

/**
  * @brief Common fuction to get RCC BDCR register field
  * @retval int as the register value
  */
int get_RCC_BDCR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->BDCR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC BDCR register field
  * @retval None
  */
void clear_RCC_BDCR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->BDCR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RCC CSR register field
  * @retval None
  */
void set_RCC_CSR_field(RCC_TypeDef *RCC_p, unsigned int val)
{
    RCC_p->CSR |= val;
}

/**
  * @brief Common fuction to get RCC CSR register field
  * @retval int as the register value
  */
int get_RCC_CSR_field(RCC_TypeDef *RCC_p, unsigned int pos, unsigned int msk)
{
    return (RCC_p->CSR & msk) >> pos;
}

/**
  * @brief Common fuction to clear RCC CSR register field
  * @retval None
  */
void clear_RCC_CSR_field(RCC_TypeDef *RCC_p, unsigned int msk)
{
    RCC_p->CSR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////