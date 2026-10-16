#include "stm32f103xb.h"
#include "custom_data_types.h"
// Look at line 1437

/**
  * @brief Reset all the fields of the GPIO register to init state
  * @retval None
  */
void init_gpio(GPIO_TypeDef *GPIO)
{
    GPIO->CRL   = 0x44444444;
    GPIO->CRH   = 0x44444444;
    GPIO->IDR   = 0;
    GPIO->ODR   = 0;
    GPIO->BSRR  = 0;
    GPIO->BRR   = 0;
    GPIO->LCKR  = 0;
}

/**
  * @brief Set GPIO CNF register filed with desired value using the GPIO_CRL_CNFx_y define
  * @retval None
  */
void set_gpio_CRL_CRH_cnf_field(GPIO_TypeDef *GPIO, unsigned int cnf_val, boolean is_crl)
{
    if (is_crl == FALSE)
    {
        GPIO->CRH |= cnf_val;
    }
    else
    {
        GPIO->CRL |= cnf_val;
    }
}

/**
  * @brief Clear GPIO CNF register filed with desired value using the GPIO_CRL_CNFx define
  * @retval None
  */
void clear_gpio_CRL_CRH_cnf_field(GPIO_TypeDef *GPIO, unsigned int cnf_msk, boolean is_crl)
{
    if (is_crl == FALSE)
    {
        GPIO->CRH &= ~cnf_msk;
    }
    else
    {
        GPIO->CRL &= ~cnf_msk;
    }
}

/**
  * @brief Set GPIO MODE register filed with desired value using the GPIO_CRL_MODEx_y define
  * @retval None
  */
void set_gpio_CRL_CRH_mode_field(GPIO_TypeDef *GPIO, unsigned int mode_val, boolean is_crl)
{
    if (is_crl == FALSE)
    {
        GPIO->CRH |= mode_val;
    }
    else
    {
        GPIO->CRL |= mode_val;
    }
}

/**
  * @brief Clear GPIO MODE register filed with desired value using the GPIO_CRL_MODEx define
  * @retval None
  */
void clear_gpio_CRL_CRH_mode_field(GPIO_TypeDef *GPIO, unsigned int mode_msk, boolean is_crl)
{
    if (is_crl == FALSE)
    {
        GPIO->CRH &= ~mode_msk;
    }
    else
    {
        GPIO->CRL &= ~mode_msk;
    }
}

/**
  * @brief Clear GPIO IDR register filed with desired value using the GPIO_IDR_IDRx define
  * @retval None
  */
void set_gpio_IDR_field(GPIO_TypeDef *GPIO, unsigned int idr_val)
{
    GPIO->IDR |= idr_val;
}

/**
  * @brief Clear GPIO IDR register filed with desired value using the GPIO_IDR_IDRx_Msk define
  * @retval None
  */
void clear_gpio_IDR_field(GPIO_TypeDef *GPIO, unsigned int idr_msk)
{
    GPIO->IDR &= ~idr_msk;
}

/**
  * @brief Clear GPIO ODR register filed with desired value using the GPIO_ODR_ODRx define
  * @retval None
  */
void set_gpio_ODR_field(GPIO_TypeDef *GPIO, unsigned int odr_val)
{
    GPIO->ODR |= odr_val;
}

/**
  * @brief Clear GPIO ODR register filed with desired value using the GPIO_ODR_ODRx_Msk define
  * @retval None
  */
void clear_gpio_ODR_field(GPIO_TypeDef *GPIO, unsigned int odr_msk)
{
    GPIO->ODR &= ~odr_msk;
}

/**
  * @brief Clear GPIO BSRR register filed with desired value using the GPIO_BSRR_BSx or GPIO_BSRR_BRx define
  * @retval None
  */
void set_gpio_BSRR_field(GPIO_TypeDef *GPIO, unsigned int bsrr_val)
{
    GPIO->BSRR |= bsrr_val;
}

/**
  * @brief Clear GPIO BSRR register filed with desired value using the GPIO_BSRR_BSx_Msk or GPIO_BSRR_BRx_Msk define
  * @retval None
  */
void clear_gpio_BSRR_field(GPIO_TypeDef *GPIO, unsigned int bsrr_msk)
{
    GPIO->BSRR &= ~bsrr_msk;
}

/**
  * @brief Clear GPIO BRR register filed with desired value using the GPIO_BRR_BRx define
  * @retval None
  */
void set_gpio_BRR_field(GPIO_TypeDef *GPIO, unsigned int brr_val)
{
    GPIO->BRR |= brr_val;
}

/**
  * @brief Clear GPIO BRR register filed with desired value using the GPIO_BRR_BRx_Msk define
  * @retval None
  */
void clear_gpio_BRR_field(GPIO_TypeDef *GPIO, unsigned int brr_msk)
{
    GPIO->BRR &= ~brr_msk;
}

/**
  * @brief Clear GPIO LCKR register filed with desired value using the GPIO_LCKR_LCKx define
  * @retval None
  */
void set_gpio_LCKR_field(GPIO_TypeDef *GPIO, unsigned int lckr_val)
{
    GPIO->LCKR |= lckr_val;
}

/**
  * @brief Clear GPIO LCKR register filed with desired value using the GPIO_LCKR_LCKx_Msk define
  * @retval None
  */
void clear_gpio_LCKR_field(GPIO_TypeDef *GPIO, unsigned int lckr_msk)
{
    GPIO->LCKR &= ~lckr_msk;
}

/**
  * @brief Make full GPIO register setup with desired values using GPIO define
  * @retval None
  */
 void setup_gpio_register
                        (
                            GPIO_TypeDef *GPIO          , 
                            unsigned int cnf_val_low    , unsigned int cnf_val_high   ,
                            unsigned int mode_val_low   , unsigned int mode_val_high  ,
                            unsigned int idr_val        , unsigned int odr_val        ,
                            unsigned int bsrr_val       , unsigned int brr_val        ,
                            unsigned int lckr_val
                        )
 {
    init_gpio(GPIO);
    set_gpio_CRL_CRH_cnf_field(GPIO, cnf_val_low, TRUE);
    set_gpio_CRL_CRH_cnf_field(GPIO, cnf_val_high, FALSE);
    set_gpio_CRL_CRH_mode_field(GPIO, mode_val_low, TRUE);
    set_gpio_CRL_CRH_mode_field(GPIO, mode_val_high, FALSE);
    set_gpio_IDR_field(GPIO, idr_val);
    set_gpio_ODR_field(GPIO, odr_val);
    set_gpio_BSRR_field(GPIO, bsrr_val);
    set_gpio_BRR_field(GPIO, brr_val);
    set_gpio_LCKR_field(GPIO, lckr_val);
 }