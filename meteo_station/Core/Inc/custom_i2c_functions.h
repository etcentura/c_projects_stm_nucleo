#include "stm32f103xb.h"
#include "custom_data_types.h"
// Look at line 907 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the I2C register to init state
  * @retval None
  */
void init_rcc(I2C_TypeDef *I2C_p)
{
  I2C_p->CR1    = 0;
  I2C_p->CR2    = 0;
  I2C_p->OAR1   = 0;
  I2C_p->OAR2   = 0;
  I2C_p->DR     = 0;
  I2C_p->SR1    = 0;
  // I2C_p->SR2    = 0;
  I2C_p->CCR    = 0;
  I2C_p->TRISE  = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set I2C CR1 register field
  * @retval None
  */
void set_I2C_CR1_field(I2C_TypeDef *I2C_p, unsigned int val)
{
    I2C_p->CR1 |= val;
}

/**
  * @brief Common fuction to get I2C CR1 register field
  * @retval int as the register value
  */
int get_I2C_CR1_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    return (I2C_p->CR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear I2C CR1 register field
  * @retval None
  */
void clear_I2C_CR1_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    I2C_p->CR1 &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set I2C CR2 register field
  * @retval None
  */
void set_I2C_CR2_field(I2C_TypeDef *I2C_p, unsigned int val)
{
    I2C_p->CR2 |= val;
}

/**
  * @brief Common fuction to get I2C CR2 register field
  * @retval int as the register value
  */
int get_I2C_CR2_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    return (I2C_p->CR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear I2C CR2 register field
  * @retval None
  */
void clear_I2C_CR2_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    I2C_p->CR2 &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set I2C OAR1 register field
  * @retval None
  */
void set_I2C_OAR1_field(I2C_TypeDef *I2C_p, unsigned int val)
{
    I2C_p->OAR1 |= val;
}

/**
  * @brief Common fuction to get I2C OAR1 register field
  * @retval int as the register value
  */
int get_I2C_OAR1_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    return (I2C_p->OAR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear I2C OAR1 register field
  * @retval None
  */
void clear_I2C_OAR1_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    I2C_p->OAR1 &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set I2C OAR2 register field
  * @retval None
  */
void set_I2C_OAR2_field(I2C_TypeDef *I2C_p, unsigned int val)
{
    I2C_p->OAR2 |= val;
}

/**
  * @brief Common fuction to get I2C OAR2 register field
  * @retval int as the register value
  */
int get_I2C_OAR2_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    return (I2C_p->OAR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear I2C OAR2 register field
  * @retval None
  */
void clear_I2C_OAR2_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    I2C_p->OAR2 &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set I2C DR register field
  * @retval None
  */
void set_I2C_DR_field(I2C_TypeDef *I2C_p, unsigned int val)
{
    I2C_p->DR |= val;
}

/**
  * @brief Common fuction to get I2C DR register field
  * @retval int as the register value
  */
int get_I2C_DR_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    return (I2C_p->DR & msk) >> pos;
}

/**
  * @brief Common fuction to clear I2C DR register field
  * @retval None
  */
void clear_I2C_DR_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    I2C_p->DR &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set I2C SR1 register field
  * @retval None
  */
void set_I2C_SR1_field(I2C_TypeDef *I2C_p, unsigned int val)
{
    I2C_p->SR1 |= val;
}

/**
  * @brief Common fuction to get I2C SR1 register field
  * @retval int as the register value
  */
int get_I2C_SR1_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    return (I2C_p->SR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear I2C SR1 register field
  * @retval None
  */
void clear_I2C_SR1_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    I2C_p->SR1 &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set I2C CCR register field
  * @retval None
  */
void set_I2C_CCR_field(I2C_TypeDef *I2C_p, unsigned int val)
{
    I2C_p->CCR |= val;
}

/**
  * @brief Common fuction to get I2C CCR register field
  * @retval int as the register value
  */
int get_I2C_CCR_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    return (I2C_p->CCR & msk) >> pos;
}

/**
  * @brief Common fuction to clear I2C CCR register field
  * @retval None
  */
void clear_I2C_CCR_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    I2C_p->CCR &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set I2C TRISE register field
  * @retval None
  */
void set_I2C_TRISE_field(I2C_TypeDef *I2C_p, unsigned int val)
{
    I2C_p->TRISE |= val;
}

/**
  * @brief Common fuction to get I2C TRISE register field
  * @retval int as the register value
  */
int get_I2C_TRISE_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    return (I2C_p->TRISE & msk) >> pos;
}

/**
  * @brief Common fuction to clear I2C TRISE register field
  * @retval None
  */
void clear_I2C_TRISE_field(I2C_TypeDef *I2C_p, unsigned int pos, unsigned int msk)
{
    I2C_p->TRISE &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////