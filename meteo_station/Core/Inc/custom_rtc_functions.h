#include "stm32f103xb.h"
#include "custom_data_types.h"
// Look at line 423 at stm32f103xb.h

//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Reset all the fields of the RTC register to init state
  * @retval None
  */
void init_RTC(RTC_TypeDef *RTC_p)
{
    RTC_p->CRH  = 0;
    RTC_p->CRL  = 0;
    RTC_p->PRLH = 0;
    RTC_p->PRLL = 0;
    RTC_p->DIVH = 0;
    RTC_p->DIVL = 0;
    RTC_p->CNTH = 0;
    RTC_p->CNTL = 0;
    RTC_p->ALRH = 0;
    RTC_p->ALRL = 0;
} 
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RTC CRH register field
  * @retval None
  */
void set_RTC_CRH_field(RTC_TypeDef *RTC_p, unsigned int val)
{
    RTC_p->CRH |= val;
}

/**
  * @brief Common fuction to get RTC CRH register field
  * @retval int as the register value
  */
int get_RTC_CRH_field(RTC_TypeDef *RTC_p, unsigned int pos, unsigned int msk)
{
    return (RTC_p->CRH & msk) >> pos;
}

/**
  * @brief Common fuction to clear RTC CR register field
  * @retval None
  */
void clear_RTC_CRH_field(RTC_TypeDef *RTC_p, unsigned int msk)
{
    RTC_p->CRH &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RTC CRL register field
  * @retval None
  */
void set_RTC_CRL_field(RTC_TypeDef *RTC_p, unsigned int val)
{
    RTC_p->CRL |= val;
}

/**
  * @brief Common fuction to get RTC CRL register field
  * @retval int as the register value
  */
int get_RTC_CRL_field(RTC_TypeDef *RTC_p, unsigned int pos, unsigned int msk)
{
    return (RTC_p->CRL & msk) >> pos;
}

/**
  * @brief Common fuction to clear RTC CRL register field
  * @retval None
  */
void clear_RTC_CRL_field(RTC_TypeDef *RTC_p, unsigned int msk)
{
    RTC_p->CRL &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RTC PRLH register field
  * @retval None
  */
void set_RTC_PRLH_field(RTC_TypeDef *RTC_p, unsigned int val)
{
    RTC_p->PRLH |= val;
}

/**
  * @brief Common fuction to clear RTC PRLH register field
  * @retval None
  */
void clear_RTC_PRLH_field(RTC_TypeDef *RTC_p, unsigned int msk)
{
    RTC_p->PRLH &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RTC PRLL register field
  * @retval None
  */
void set_RTC_PRLL_field(RTC_TypeDef *RTC_p, unsigned int val)
{
    RTC_p->PRLL |= val;
}

/**
  * @brief Common fuction to clear RTC PRLL register field
  * @retval None
  */
void clear_RTC_PRLL_field(RTC_TypeDef *RTC_p, unsigned int msk)
{
    RTC_p->PRLL &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get RTC DIVH register field
  * @retval int as the register value
  */
int get_RTC_DIVH_field(RTC_TypeDef *RTC_p, unsigned int pos, unsigned int msk)
{
    return (RTC_p->DIVH & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to get RTC DIVL register field
  * @retval int as the register value
  */
int get_RTC_DIVL_field(RTC_TypeDef *RTC_p, unsigned int pos, unsigned int msk)
{
    return (RTC_p->DIVL & msk) >> pos;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RTC CNTH register field
  * @retval None
  */
void set_RTC_CNTH_field(RTC_TypeDef *RTC_p, unsigned int val)
{
    RTC_p->CNTH |= val;
}

/**
  * @brief Common fuction to get RTC CNTH register field
  * @retval int as the register value
  */
int get_RTC_CNTH_field(RTC_TypeDef *RTC_p, unsigned int pos, unsigned int msk)
{
    return (RTC_p->CNTH & msk) >> pos;
}

/**
  * @brief Common fuction to clear RTC CNTH register field
  * @retval None
  */
void clear_RTC_CNTH_field(RTC_TypeDef *RTC_p, unsigned int msk)
{
    RTC_p->CNTH &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RTC CNTL register field
  * @retval None
  */
void set_RTC_CNTL_field(RTC_TypeDef *RTC_p, unsigned int val)
{
    RTC_p->CNTL |= val;
}

/**
  * @brief Common fuction to get RTC CNTL register field
  * @retval int as the register value
  */
int get_RTC_CNTL_field(RTC_TypeDef *RTC_p, unsigned int pos, unsigned int msk)
{
    return (RTC_p->CNTL & msk) >> pos;
}

/**
  * @brief Common fuction to clear RTC CNTL register field
  * @retval None
  */
void clear_RTC_CNTL_field(RTC_TypeDef *RTC_p, unsigned int msk)
{
    RTC_p->CNTL &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RTC ALRH register field
  * @retval None
  */
void set_RTC_ALRH_field(RTC_TypeDef *RTC_p, unsigned int val)
{
    RTC_p->ALRH |= val;
}

/**
  * @brief Common fuction to clear RTC ALRH register field
  * @retval None
  */
void clear_RTC_ALRH_field(RTC_TypeDef *RTC_p, unsigned int msk)
{
    RTC_p->ALRH &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief Common fuction to set RTC ALRL register field
  * @retval None
  */
void set_RTC_ALRL_field(RTC_TypeDef *RTC_p, unsigned int val)
{
    RTC_p->ALRL |= val;
}

/**
  * @brief Common fuction to clear RTC ALRL register field
  * @retval None
  */
void clear_RTC_ALRL_field(RTC_TypeDef *RTC_p, unsigned int msk)
{
    RTC_p->ALRL &= ~msk;
}
//////////////////////////////////////////////////////////////////////////////////////////