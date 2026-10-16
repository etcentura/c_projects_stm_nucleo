#include "stm32f103xb.h"
#include "custom_data_types.h"
// Look at line 476 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the ADC register to init state
  * @retval None
  */
void init_TIM(TIM_TypeDef *TIM_p)
{
  TIM_p->CR1    = 0;
  TIM_p->CR2    = 0;
  TIM_p->SMCR   = 0;
  TIM_p->DIER   = 0;
  TIM_p->SR     = 0;
  TIM_p->EGR    = 0;
  TIM_p->CCMR1  = 0;
  TIM_p->CCMR2  = 0;
  TIM_p->CCER   = 0;
  TIM_p->CNT    = 0;
  TIM_p->PSC    = 0;
  TIM_p->ARR    = 0;
  TIM_p->RCR    = 0;
  TIM_p->CCR1   = 0;
  TIM_p->CCR2   = 0;
  TIM_p->CCR3   = 0;
  TIM_p->CCR4   = 0;
  TIM_p->BDTR   = 0;
  TIM_p->DCR    = 0;
  TIM_p->DMAR   = 0;
  TIM_p->OR     = 0;

}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CR1 register field
  * @retval None
  */
void set_TIM_CR1_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CR1 |= val;
}

/**
  * @brief Common fuction to get TIM CR1 register field
  * @retval int as the register value
  */
int get_TIM_CR1_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CR1 register field
  * @retval None
  */
void clear_TIM_CR1_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CR2 register field
  * @retval None
  */
void set_TIM_CR2_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CR2 |= val;
}

/**
  * @brief Common fuction to get TIM CR2 register field
  * @retval int as the register value
  */
int get_TIM_CR2_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CR2 register field
  * @retval None
  */
void clear_TIM_CR2_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM SMCR register field
  * @retval None
  */
void set_TIM_SMCR_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->SMCR |= val;
}

/**
  * @brief Common fuction to get TIM SMCR register field
  * @retval int as the register value
  */
int get_TIM_SMCR_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->SMCR & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM SMCR register field
  * @retval None
  */
void clear_TIM_SMCR_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->SMCR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM DIER register field
  * @retval None
  */
void set_TIM_DIER_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->DIER |= val;
}

/**
  * @brief Common fuction to get TIM DIER register field
  * @retval int as the register value
  */
int get_TIM_DIER_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->DIER & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM DIER register field
  * @retval None
  */
void clear_TIM_DIER_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->DIER &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM SR register field
  * @retval None
  */
void set_TIM_SR_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->SR |= val;
}

/**
  * @brief Common fuction to get TIM SR register field
  * @retval int as the register value
  */
int get_TIM_SR_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->SR & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM SR register field
  * @retval None
  */
void clear_TIM_SR_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->SR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM EGR register field
  * @retval None
  */
void set_TIM_EGR_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->EGR |= val;
}

/**
  * @brief Common fuction to clear TIM EGR register field
  * @retval None
  */
void clear_TIM_EGR_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->EGR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CCMR1 register field
  * @retval None
  */
void set_TIM_CCMR1_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CCMR1 |= val;
}

/**
  * @brief Common fuction to get TIM CCMR1 register field
  * @retval int as the register value
  */
int get_TIM_CCMR1_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CCMR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CCMR1 register field
  * @retval None
  */
void clear_TIM_CCMR1_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CCMR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CCMR2 register field
  * @retval None
  */
void set_TIM_CCMR2_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CCMR2 |= val;
}

/**
  * @brief Common fuction to get TIM CCMR2 register field
  * @retval int as the register value
  */
int get_TIM_CCMR2_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CCMR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CCMR2 register field
  * @retval None
  */
void clear_TIM_CCMR2_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CCMR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CCER register field
  * @retval None
  */
void set_TIM_CCER_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CCER |= val;
}

/**
  * @brief Common fuction to get TIM CCER register field
  * @retval int as the register value
  */
int get_TIM_CCER_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CCER & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CCER register field
  * @retval None
  */
void clear_TIM_CCER_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CCER &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CNT register field
  * @retval None
  */
void set_TIM_CNT_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CNT |= val;
}

/**
  * @brief Common fuction to get TIM CNT register field
  * @retval int as the register value
  */
int get_TIM_CNT_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CNT & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CNT register field
  * @retval None
  */
void clear_TIM_CNT_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CNT &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM PSC register field
  * @retval None
  */
void set_TIM_PSC_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->PSC |= val;
}

/**
  * @brief Common fuction to get TIM PSC register field
  * @retval int as the register value
  */
int get_TIM_PSC_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->PSC & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM PSC register field
  * @retval None
  */
void clear_TIM_PSC_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->PSC &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM ARR register field
  * @retval None
  */
void set_TIM_ARR_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->ARR |= val;
}

/**
  * @brief Common fuction to get TIM ARR register field
  * @retval int as the register value
  */
int get_TIM_ARR_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->ARR & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM ARR register field
  * @retval None
  */
void clear_TIM_ARR_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->ARR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CCR1 register field
  * @retval None
  */
void set_TIM_CCR1_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CCR1 |= val;
}

/**
  * @brief Common fuction to get TIM CCR1 register field
  * @retval int as the register value
  */
int get_TIM_CCR1_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CCR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CCR1 register field
  * @retval None
  */
void clear_TIM_CCR1_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CCR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CCR2 register field
  * @retval None
  */
void set_TIM_CCR2_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CCR2 |= val;
}

/**
  * @brief Common fuction to get TIM CCR2 register field
  * @retval int as the register value
  */
int get_TIM_CCR2_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CCR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CCR2 register field
  * @retval None
  */
void clear_TIM_CCR2_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CCR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CCR3 register field
  * @retval None
  */
void set_TIM_CCR3_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CCR3 |= val;
}

/**
  * @brief Common fuction to get TIM CCR3 register field
  * @retval int as the register value
  */
int get_TIM_CCR3_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CCR3 & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CCR3 register field
  * @retval None
  */
void clear_TIM_CCR3_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CCR3 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM CCR4 register field
  * @retval None
  */
void set_TIM_CCR4_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->CCR4 |= val;
}

/**
  * @brief Common fuction to get TIM CCR4 register field
  * @retval int as the register value
  */
int get_TIM_CCR4_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->CCR4 & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM CCR4 register field
  * @retval None
  */
void clear_TIM_CCR4_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->CCR4 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM BDTR register field
  * @retval None
  */
void set_TIM_BDTR_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->BDTR |= val;
}

/**
  * @brief Common fuction to get TIM BDTR register field
  * @retval int as the register value
  */
int get_TIM_BDTR_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->BDTR & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM BDTR register field
  * @retval None
  */
void clear_TIM_BDTR_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->BDTR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM DCR register field
  * @retval None
  */
void set_TIM_DCR_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->DCR |= val;
}

/**
  * @brief Common fuction to get TIM DCR register field
  * @retval int as the register value
  */
int get_TIM_DCR_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->DCR & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM DCR register field
  * @retval None
  */
void clear_TIM_DCR_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->DCR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM DMAR register field
  * @retval None
  */
void set_TIM_DMAR_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->DMAR |= val;
}

/**
  * @brief Common fuction to get TIM DMAR register field
  * @retval int as the register value
  */
int get_TIM_DMAR_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->DMAR & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM DMAR register field
  * @retval None
  */
void clear_TIM_DMAR_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->DMAR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set TIM OR register field
  * @retval None
  */
void set_TIM_OR_field(TIM_TypeDef *TIM_p, unsigned int val)
{
    TIM_p->OR |= val;
}

/**
  * @brief Common fuction to get TIM OR register field
  * @retval int as the register value
  */
int get_TIM_OR_field(TIM_TypeDef *TIM_p, unsigned int pos, unsigned int msk)
{
    return (TIM_p->OR & msk) >> pos;
}

/**
  * @brief Common fuction to clear TIM OR register field
  * @retval None
  */
void clear_TIM_OR_field(TIM_TypeDef *TIM_p, unsigned int msk)
{
    TIM_p->OR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////