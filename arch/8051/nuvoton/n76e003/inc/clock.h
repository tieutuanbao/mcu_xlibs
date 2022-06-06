/**
  ******************************************************************************
  * @file           : clock.h
  * @brief          : Thư viện lập trình chip N76E003.
    *    @author                    :    Tiêu Tuấn Bảo
  ******************************************************************************
  * @attention
  *
    *
  ******************************************************************************
  */

extern unsigned char  BIT_TMP;

void clock_HIRC_16_config(void);
void clock_HIRC_24_config(void);
void clock_HIRC_166_config(void);
