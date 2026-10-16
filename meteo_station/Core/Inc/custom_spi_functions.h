#include "stm32f103xb.h"
#include "custom_data_types.h"
// Look at line 458 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the SPI register to init state
  * @retval None
  */
void init_rcc(SPI_TypeDef *SPI_p)
{
  SPI_p->CR1        = 0;
  SPI_p->CR2        = ;
  SPI_p->SR         = ;
  SPI_p->DR         = ;
  SPI_p->CRCPR      = ;
  SPI_p->RXCRCR     = ;
  SPI_p->TXCRCR     = ;
  SPI_p->I2SCFGR    = ;
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
void clear_SPI_CR1_field(SPI_TypeDef *SPI_p, unsigned int pos, unsigned int msk)
{
    SPI_p->CR1 &= ~(msk << pos);
}
//////////////////////////////////////////////////////////////////////////////////////////