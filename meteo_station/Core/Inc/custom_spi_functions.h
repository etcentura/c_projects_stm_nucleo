#include "stm32f103xb.h"
#include "custom_data_types.h"
// Look at line 458 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the SPI register to init state
  * @retval None
  */
void init_SPI(SPI_TypeDef *SPI_p)
{
  SPI_p->CR1        = 0;
  SPI_p->CR2        = 0;
  SPI_p->SR         = 0;
  SPI_p->DR         = 0;
  SPI_p->CRCPR      = 0;
  SPI_p->RXCRCR     = 0;
  SPI_p->TXCRCR     = 0;
  SPI_p->I2SCFGR    = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set SPI CR1 register field
  * @retval None
  */
void set_SPI_CR1_field(SPI_TypeDef *SPI_p, unsigned int val)
{
    SPI_p->CR1 |= val;
}

/**
  * @brief Common fuction to get SPI CR1 register field
  * @retval int as the register value
  */
int get_SPI_CR1_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    return (SPI_p->CR1 & msk) >> pos;
}

/**
  * @brief Common fuction to clear SPI CR1 register field
  * @retval None
  */
void clear_SPI_CR1_field(SPI_TypeDef *SPI_p, unsigned int msk)
{
    SPI_p->CR1 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set SPI CR2 register field
  * @retval None
  */
void set_SPI_CR2_field(SPI_TypeDef *SPI_p, unsigned int val)
{
    SPI_p->CR2 |= val;
}

/**
  * @brief Common fuction to get SPI CR2 register field
  * @retval int as the register value
  */
int get_SPI_CR2_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    return (SPI_p->CR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear SPI CR2 register field
  * @retval None
  */
void clear_SPI_CR2_field(SPI_TypeDef *SPI_p, unsigned int msk)
{
    SPI_p->CR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set SPI SR register field
  * @retval None
  */
void set_SPI_SR_field(SPI_TypeDef *SPI_p, unsigned int val)
{
    SPI_p->SR |= val;
}

/**
  * @brief Common fuction to get SPI SR register field
  * @retval int as the register value
  */
int get_SPI_SR_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    return (SPI_p->SR & msk) >> pos;
}

/**
  * @brief Common fuction to clear SPI SR register field
  * @retval None
  */
void clear_SPI_SR_field(SPI_TypeDef *SPI_p, unsigned int msk)
{
    SPI_p->SR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set SPI DR register field
  * @retval None
  */
void set_SPI_DR_field(SPI_TypeDef *SPI_p, unsigned int val)
{
    SPI_p->DR |= val;
}

/**
  * @brief Common fuction to get SPI DR register field
  * @retval int as the register value
  */
int get_SPI_DR_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    return (SPI_p->DR & msk) >> pos;
}

/**
  * @brief Common fuction to clear SPI DR register field
  * @retval None
  */
void clear_SPI_DR_field(SPI_TypeDef *SPI_p, unsigned int msk)
{
    SPI_p->DR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set SPI CRCPR register field
  * @retval None
  */
void set_SPI_CRCPR_field(SPI_TypeDef *SPI_p, unsigned int val)
{
    SPI_p->CRCPR |= val;
}

/**
  * @brief Common fuction to get SPI CRCPR register field
  * @retval int as the register value
  */
int get_SPI_CRCPR_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    return (SPI_p->CRCPR & msk) >> pos;
}

/**
  * @brief Common fuction to clear SPI CRCPR register field
  * @retval None
  */
void clear_SPI_CRCPR_field(SPI_TypeDef *SPI_p, unsigned int msk)
{
    SPI_p->CRCPR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get SPI RXCRCR register field
  * @retval int as the register value
  */
int get_SPI_RXCRCR_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    return (SPI_p->RXCRCR & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get SPI TXCRCR register field
  * @retval int as the register value
  */
int get_SPI_TXCRCR_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    return (SPI_p->TXCRCR & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set SPI I2SCFGR register field
  * @retval None
  */
void set_SPI_I2SCFGR_field(SPI_TypeDef *SPI_p, unsigned int val)
{
    SPI_p->I2SCFGR |= val;
}

/**
  * @brief Common fuction to get SPI I2SCFGR register field
  * @retval int as the register value
  */
int get_SPI_I2SCFGR_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    return (SPI_p->I2SCFGR & msk) >> pos;
}

/**
  * @brief Common fuction to clear SPI I2SCFGR register field
  * @retval None
  */
void clear_SPI_I2SCFGR_field(SPI_TypeDef *SPI_p, unsigned int msk)
{
    SPI_p->I2SCFGR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////