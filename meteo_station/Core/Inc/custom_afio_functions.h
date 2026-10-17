#include "stm32f103xb.h"
// Look at line 372 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the AFIO register to init state
  * @retval None
  */
void init_AFIO(AFIO_TypeDef *AFIO_p)
{
    AFIO_p->EVCR        = 0;
    AFIO_p->MAPR        = 0;
    AFIO_p->EXTICR[0]   = 0;
    AFIO_p->EXTICR[1]   = 0;
    AFIO_p->EXTICR[2]   = 0;
    AFIO_p->EXTICR[3]   = 0;
    AFIO_p->MAPR2       = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set AFIO EVCR register field
  * @retval None
  */
void set_AFIO_EVCR_field(AFIO_TypeDef *AFIO_p, unsigned int val)
{
    AFIO_p->EVCR |= val;
}

/**
  * @brief Common fuction to get AFIO EVCR register field
  * @retval int as the register value
  */
int get_AFIO_EVCR_field(AFIO_TypeDef *AFIO_p, unsigned int pos, unsigned int msk)
{
    return (AFIO_p->EVCR & msk) >> pos;
}

/**
  * @brief Common fuction to clear AFIO EVCR register field
  * @retval None
  */
void clear_AFIO_EVCR_field(AFIO_TypeDef *AFIO_p, unsigned int msk)
{
    AFIO_p->EVCR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set AFIO MAPR register field
  * @retval None
  */
void set_AFIO_MAPR_field(AFIO_TypeDef *AFIO_p, unsigned int val)
{
    AFIO_p->MAPR |= val;
}

/**
  * @brief Common fuction to get AFIO MAPR register field
  * @retval int as the register value
  */
int get_AFIO_MAPR_field(AFIO_TypeDef *AFIO_p, unsigned int pos, unsigned int msk)
{
    return (AFIO_p->MAPR & msk) >> pos;
}

/**
  * @brief Common fuction to clear AFIO MAPR register field
  * @retval None
  */
void clear_AFIO_MAPR_field(AFIO_TypeDef *AFIO_p, unsigned int msk)
{
    AFIO_p->MAPR &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set AFIO EXTICR register field
  * @retval None
  */
void set_AFIO_EXTICR_field(AFIO_TypeDef *AFIO_p, unsigned int val, unsigned int sel)
{
    if(sel > 3)
    {
        AFIO_p->EXTICR[0] |= val;
    }
    else
    {
        AFIO_p->EXTICR[sel] |= val;
    }
}

/**
  * @brief Common fuction to get AFIO EXTICR register field
  * @retval int as the register value
  */
int get_AFIO_EXTICR_field(AFIO_TypeDef *AFIO_p, unsigned int pos, unsigned int msk, unsigned int sel)
{
    if(sel > 3)
    {
        return (AFIO_p->EXTICR[0] & msk) >> pos;
    }
    else
    {
        return (AFIO_p->EXTICR[sel] & msk) >> pos;
    }
}

/**
  * @brief Common fuction to clear AFIO EXTICR register field
  * @retval None
  */
void clear_AFIO_EXTICR_field(AFIO_TypeDef *AFIO_p, unsigned int msk, unsigned int sel)
{
    if(sel > 3)
    {
        AFIO_p->EXTICR[0] &= ~msk;
    }
    else
    {
        AFIO_p->EXTICR[sel] &= ~msk;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set AFIO MAPR2 register field
  * @retval None
  */
void set_AFIO_MAPR2_field(AFIO_TypeDef *AFIO_p, unsigned int val)
{
    AFIO_p->MAPR2 |= val;
}

/**
  * @brief Common fuction to get AFIO MAPR2 register field
  * @retval int as the register value
  */
int get_AFIO_MAPR2_field(AFIO_TypeDef *AFIO_p, unsigned int pos, unsigned int msk)
{
    return (AFIO_p->MAPR2 & msk) >> pos;
}

/**
  * @brief Common fuction to clear AFIO MAPR2 register field
  * @retval None
  */
void clear_AFIO_MAPR2_field(AFIO_TypeDef *AFIO_p, unsigned int msk)
{
    AFIO_p->MAPR2 &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////