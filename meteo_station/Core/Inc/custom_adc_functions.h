#include "stm32f103xb.h"
#include "custom_data_types.h"
// Look at line 144 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the ADC register to init state
  * @retval None
  */
void init_ADC(ADC_TypeDef *ADC_p)
{
    ADC_p->SR       = 0;
    ADC_p->CR1      = 0;
    ADC_p->CR2      = 0;
    ADC_p->SMPR1    = 0;
    ADC_p->SMPR2    = 0;
    ADC_p->JOFR1    = 0;
    ADC_p->JOFR2    = 0;
    ADC_p->JOFR3    = 0;
    ADC_p->JOFR4    = 0;
    ADC_p->HTR      = 0;
    ADC_p->LTR      = 0;
    ADC_p->SQR1     = 0;
    ADC_p->SQR2     = 0;
    ADC_p->SQR3     = 0;
    ADC_p->JSQR     = 0;
    ADC_p->JDR1     = 0;
    ADC_p->JDR2     = 0;
    ADC_p->JDR3     = 0;
    ADC_p->JDR4     = 0;
    ADC_p->DR       = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC SR register field
  * @retval None
  */
void set_ADC_SR_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->SR |= val;
}

/**
  * @brief Common fuction to get ADC SR register field
  * @retval int as the register value
  */
int get_ADC_SR_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->SR & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC SR register field
  * @retval None
  */
void clear_ADC_SR_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->SR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC CR1 register field
  * @retval None
  */
void set_ADC_CR1_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->CR1 |= val;
}

/**
  * @brief Common fuction to get ADC CR1 register field
  * @retval int as the register value
  */
int get_ADC_CR1_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->CR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC CR1 register field
  * @retval None
  */
void clear_ADC_CR1_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->CR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC CR2 register field
  * @retval None
  */
void set_ADC_CR2_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->CR2 |= val;
}

/**
  * @brief Common fuction to get ADC CR2 register field
  * @retval int as the register value
  */
int get_ADC_CR2_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->CR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC CR2 register field
  * @retval None
  */
void clear_ADC_CR2_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->CR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC SMPR1 register field
  * @retval None
  */
void set_ADC_SMPR1_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->SMPR1 |= val;
}

/**
  * @brief Common fuction to get ADC SMPR1 register field
  * @retval int as the register value
  */
int get_ADC_SMPR1_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->SMPR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC SMPR1 register field
  * @retval None
  */
void clear_ADC_SMPR1_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->SMPR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC SMPR2 register field
  * @retval None
  */
void set_ADC_SMPR2_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->SMPR2 |= val;
}

/**
  * @brief Common fuction to get ADC SMPR2 register field
  * @retval int as the register value
  */
int get_ADC_SMPR2_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->SMPR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC SMPR2 register field
  * @retval None
  */
void clear_ADC_SMPR2_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->SMPR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC JOFR1 register field
  * @retval None
  */
void set_ADC_JOFR1_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->JOFR1 |= val;
}

/**
  * @brief Common fuction to get ADC JOFR1 register field
  * @retval int as the register value
  */
int get_ADC_JOFR1_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JOFR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC JOFR1 register field
  * @retval None
  */
void clear_ADC_JOFR1_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->JOFR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC JOFR2 register field
  * @retval None
  */
void set_ADC_JOFR2_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->JOFR2 |= val;
}

/**
  * @brief Common fuction to get ADC JOFR2 register field
  * @retval int as the register value
  */
int get_ADC_JOFR2_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JOFR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC JOFR2 register field
  * @retval None
  */
void clear_ADC_JOFR2_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->JOFR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC JOFR3 register field
  * @retval None
  */
void set_ADC_JOFR3_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->JOFR3 |= val;
}

/**
  * @brief Common fuction to get ADC JOFR3 register field
  * @retval int as the register value
  */
int get_ADC_JOFR3_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JOFR3 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC JOFR3 register field
  * @retval None
  */
void clear_ADC_JOFR3_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->JOFR3 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC JOFR4 register field
  * @retval None
  */
void set_ADC_JOFR4_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->JOFR4 |= val;
}

/**
  * @brief Common fuction to get ADC JOFR4 register field
  * @retval int as the register value
  */
int get_ADC_JOFR4_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JOFR4 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC JOFR4 register field
  * @retval None
  */
void clear_ADC_JOFR4_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->JOFR4 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC HTR register field
  * @retval None
  */
void set_ADC_HTR_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->HTR |= val;
}

/**
  * @brief Common fuction to get ADC HTR register field
  * @retval int as the register value
  */
int get_ADC_HTR_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->HTR & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC HTR register field
  * @retval None
  */
void clear_ADC_HTR_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->HTR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC LTR register field
  * @retval None
  */
void set_ADC_LTR_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->LTR |= val;
}

/**
  * @brief Common fuction to get ADC LTR register field
  * @retval int as the register value
  */
int get_ADC_LTR_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->LTR & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC LTR register field
  * @retval None
  */
void clear_ADC_LTR_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->LTR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC SQR1 register field
  * @retval None
  */
void set_ADC_SQR1_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->SQR1 |= val;
}

/**
  * @brief Common fuction to get ADC SQR1 register field
  * @retval int as the register value
  */
int get_ADC_SQR1_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->SQR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC SQR1 register field
  * @retval None
  */
void clear_ADC_SQR1_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->SQR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC SQR2 register field
  * @retval None
  */
void set_ADC_SQR2_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->SQR2 |= val;
}

/**
  * @brief Common fuction to get ADC SQR2 register field
  * @retval int as the register value
  */
int get_ADC_SQR2_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->SQR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC SQR2 register field
  * @retval None
  */
void clear_ADC_SQR2_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->SQR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC SQR3 register field
  * @retval None
  */
void set_ADC_SQR3_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->SQR3 |= val;
}

/**
  * @brief Common fuction to get ADC SQR3 register field
  * @retval int as the register value
  */
int get_ADC_SQR3_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->SQR3 & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC SQR3 register field
  * @retval None
  */
void clear_ADC_SQR3_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->SQR3 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set ADC JSQR register field
  * @retval None
  */
void set_ADC_JSQR_field(ADC_TypeDef *ADC_p, unsigned int val)
{
    ADC_p->JSQR |= val;
}

/**
  * @brief Common fuction to get ADC JSQR register field
  * @retval int as the register value
  */
int get_ADC_JSQR_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JSQR & msk) >> pos;
}

/**
  * @brief Common fuction to clear ADC JSQR register field
  * @retval None
  */
void clear_ADC_JSQR_field(ADC_TypeDef *ADC_p, unsigned int msk)
{
    ADC_p->JSQR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get ADC JDR1 register field
  * @retval int as the register value
  */
int get_ADC_JDR1_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JDR1 & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get ADC JDR2 register field
  * @retval int as the register value
  */
int get_ADC_JDR2_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JDR2 & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get ADC JDR3 register field
  * @retval int as the register value
  */
int get_ADC_JDR3_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JDR3 & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get ADC JDR4 register field
  * @retval int as the register value
  */
int get_ADC_JDR4_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->JDR4 & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get ADC DR register field
  * @retval int as the register value
  */
int get_ADC_DR_field(ADC_TypeDef *ADC_p, unsigned int pos, unsigned int msk)
{
    return (ADC_p->DR & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


