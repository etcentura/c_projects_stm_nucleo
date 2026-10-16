#include "stm32f103xb.h"
#include "custom_data_types.h"
// Look at line 1437 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the GPIO register to init state
  * @retval None
  */
void init_gpio(GPIO_TypeDef *GPIO_p)
{
    GPIO_p->CRL   = 0x44444444;
    GPIO_p->CRH   = 0x44444444;
    // GPIO_p->IDR   = 0;
    GPIO_p->ODR   = 0;
    GPIO_p->BSRR  = 0;
    GPIO_p->BRR   = 0;
    GPIO_p->LCKR  = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set GPIO CRL register field
  * @retval None
  */
void set_GPIO_CRL_field(GPIO_TypeDef *GPIO_p, unsigned int val)
{
    GPIO_p->CRL |= val;
}

/**
  * @brief Common fuction to get GPIO CRL register field
  * @retval int as the register value
  */
int get_GPIO_CRL_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    return (GPIO_p->CRL & msk) >> pos;
}

/**
  * @brief Common fuction to clear GPIO CRL register field
  * @retval None
  */
void clear_GPIO_CRL_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    GPIO_p->CRL &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set GPIO CRH register field
  * @retval None
  */
void set_GPIO_CRH_field(GPIO_TypeDef *GPIO_p, unsigned int val)
{
    GPIO_p->CRH |= val;
}

/**
  * @brief Common fuction to get GPIO CRH register field
  * @retval int as the register value
  */
int get_GPIO_CRH_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    return (GPIO_p->CRH & msk) >> pos;
}

/**
  * @brief Common fuction to clear GPIO CRH register field
  * @retval None
  */
void clear_GPIO_CRH_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    GPIO_p->CRH &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Get GPIO IDR register field
  * @retval None
  */
int set_GPIO_IDR_field(GPIO_TypeDef *GPIO_p, unsigned int msk, unsigned int pos)
{
    return (GPIO_p->IDR & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set GPIO ODR register field
  * @retval None
  */
void set_GPIO_ODR_field(GPIO_TypeDef *GPIO_p, unsigned int val)
{
    GPIO_p->ODR |= val;
}

/**
  * @brief Common fuction to get GPIO ODR register field
  * @retval int as the register value
  */
int get_GPIO_ODR_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    return (GPIO_p->ODR & msk) >> pos;
}

/**
  * @brief Common fuction to clear GPIO ODR register field
  * @retval None
  */
void clear_GPIO_ODR_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    GPIO_p->ODR &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set GPIO BSRR register field
  * @retval None
  */
void set_GPIO_BSRR_field(GPIO_TypeDef *GPIO_p, unsigned int val)
{
    GPIO_p->BSRR |= val;
}

/**
  * @brief Common fuction to clear GPIO BSRR register field
  * @retval None
  */
void clear_GPIO_BSRR_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    GPIO_p->BSRR &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set GPIO BRR register field
  * @retval None
  */
void set_GPIO_BRR_field(GPIO_TypeDef *GPIO_p, unsigned int val)
{
    GPIO_p->BRR |= val;
}

/**
  * @brief Common fuction to clear GPIO BRR register field
  * @retval None
  */
void clear_GPIO_BRR_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    GPIO_p->BRR &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set GPIO LCKR register field
  * @retval None
  */
void set_GPIO_LCKR_field(GPIO_TypeDef *GPIO_p, unsigned int val)
{
    GPIO_p->LCKR |= val;
}

/**
  * @brief Common fuction to get GPIO LCKR register field
  * @retval int as the register value
  */
int get_GPIO_LCKR_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    return (GPIO_p->LCKR & msk) >> pos;
}

/**
  * @brief Common fuction to clear GPIO LCKR register field
  * @retval None
  */
void clear_GPIO_LCKR_field(GPIO_TypeDef *GPIO_p, unsigned int pos, unsigned int msk)
{
    GPIO_p->LCKR &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////
