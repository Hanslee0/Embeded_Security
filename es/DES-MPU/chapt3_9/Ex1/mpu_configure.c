#include "start.h"
#include "mpu_manual.h"

#include <ARMCM3.h>

#include <stdbool.h>
#include <stdint.h>

void disableMPU(bool manualConfiguration)
{
  if (manualConfiguration)
  {
    uint32_t* registerAddr = MPU_REG_CTRL;
    *registerAddr = 0x7;
  }
  else
  {
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk
                   | MPU_CTRL_HFNMIENA_Msk
                   | MPU_CTRL_ENABLE_Msk);
  }
}

void ManualInitMPU(void)
{
  uint32_t* registerAddr;

  registerAddr = MPU_REG_TYPE;
  logPrint("0x%x has value 0x%x\n", registerAddr, *registerAddr);

  registerAddr = MPU_REG_CTRL;
  *registerAddr = 0x0;
  logPrint("0x%x has value 0x%x\n", registerAddr, *registerAddr);

  ManualConfigureRegion(
    0,
    0,
    0b10000 /* 128KB */,
    0b11,
    0);

  ManualConfigureRegion(
    1,
    0x20000000,
    0b01110 /* 32KB */,
    0b11,
    0);

  ManualConfigureRegion(
    2,
    0x20008000,
    0b01110 /* 32KB */,
    0b0,
    0);

  ManualConfigureRegion(
    3,
    0x2000C000,
    0b01101 /* 16KB */,
    0b11,
    1);

  registerAddr = MPU_REG_CTRL;
  *registerAddr = 0x7;
  logPrint("0x%x has value 0x%x\n", registerAddr, *registerAddr);
}

void CmsisInitMPU(void)
{
  ARM_MPU_Disable();

  ARM_MPU_SetRegionEx(
    0UL                                    /* Region Number */,
    0x00000000UL                           /* Base Address  */,
    ARM_MPU_RASR(0UL                       /* DisableExec */,
                 ARM_MPU_AP_FULL           /* AccessPermission*/,
                 0UL                       /* TypeExtField*/,
                 0UL                       /* IsShareable*/,
                 0UL                       /* IsCacheable*/,
                 0UL                       /* IsBufferable*/,
                 0x00UL                    /* SubRegionDisable*/,
                 ARM_MPU_REGION_SIZE_128KB /* Size*/)
  );

  ARM_MPU_SetRegionEx(
    1UL                                   /* Region Number */,
    0x20000000UL                          /* Base Address  */,
    ARM_MPU_RASR(0UL                      /* DisableExec */,
                 ARM_MPU_AP_FULL          /* AccessPermission*/,
                 0UL                      /* TypeExtField*/,
                 0UL                      /* IsShareable*/,
                 0UL                      /* IsCacheable*/,
                 0UL                      /* IsBufferable*/,
                 0x00UL                   /* SubRegionDisable*/,
                 ARM_MPU_REGION_SIZE_64KB /* Size*/)
  );

  ARM_MPU_SetRegionEx(
    2UL                                   /* Region Number */,
    0x20010000UL                          /* Base Address  */,
    ARM_MPU_RASR(1UL                      /* DisableExec */,
                 ARM_MPU_AP_NONE          /* AccessPermission*/,
                 0UL                      /* TypeExtField*/,
                 0UL                      /* IsShareable*/,
                 0UL                      /* IsCacheable*/,
                 0UL                      /* IsBufferable*/,
                 0x00UL                   /* SubRegionDisable*/,
                 ARM_MPU_REGION_SIZE_16KB /* Size*/)
  );

  ARM_MPU_SetRegionEx(
    3UL                                   /* Region Number */,
    0x20014000UL                          /* Base Address  */,
    ARM_MPU_RASR(1UL                      /* DisableExec */,
                 ARM_MPU_AP_PRO           /* AccessPermission*/,
                 0UL                      /* TypeExtField*/,
                 0UL                      /* IsShareable*/,
                 0UL                      /* IsCacheable*/,
                 0UL                      /* IsBufferable*/,
                 0x2AUL                   /* SubRegionDisable*/,
                 ARM_MPU_REGION_SIZE_16KB /* Size*/)
  );

  ARM_MPU_SetRegionEx(
    4UL                                   /* Region Number */,
    0x20018000UL                          /* Base Address  */,
    ARM_MPU_RASR(1UL                      /* DisableExec */,
                 ARM_MPU_AP_PRO           /* AccessPermission*/,
                 0UL                      /* TypeExtField*/,
                 0UL                      /* IsShareable*/,
                 0UL                      /* IsCacheable*/,
                 0UL                      /* IsBufferable*/,
                 0x00UL                   /* SubRegionDisable*/,
                 ARM_MPU_REGION_SIZE_16KB /* Size*/)
  );
  ARM_MPU_SetRegionEx(
    5UL                                   /* Region Number */,
    0x20020000UL                          /* Base Address  */,
    ARM_MPU_RASR(1UL                      /* DisableExec */,
                 ARM_MPU_AP_PRIV          /* AccessPermission*/,
                 0UL                      /* TypeExtField*/,
                 0UL                      /* IsShareable*/,
                 0UL                      /* IsCacheable*/,
                 0UL                      /* IsBufferable*/,
                 0x00UL                   /* SubRegionDisable*/,
                 ARM_MPU_REGION_SIZE_16KB /* Size*/)
  );
  ARM_MPU_SetRegionEx(
    6UL                                   /* Region Number */,
    0x20024000UL                          /* Base Address  */,
    ARM_MPU_RASR(1UL                      /* DisableExec */,
                 ARM_MPU_AP_URO           /* AccessPermission*/,
                 0UL                      /* TypeExtField*/,
                 0UL                      /* IsShareable*/,
                 0UL                      /* IsCacheable*/,
                 0UL                      /* IsBufferable*/,
                 0x00UL                   /* SubRegionDisable*/,
                 ARM_MPU_REGION_SIZE_16KB /* Size*/)
  );
  ARM_MPU_SetRegionEx(
    7UL                                   /* Region Number */,
    0x20028000UL                          /* Base Address  */,
    ARM_MPU_RASR(1UL                      /* DisableExec */,
                 ARM_MPU_AP_RO            /* AccessPermission*/,
                 0UL                      /* TypeExtField*/,
                 0UL                      /* IsShareable*/,
                 0UL                      /* IsCacheable*/,
                 0UL                      /* IsBufferable*/,
                 0x00UL                   /* SubRegionDisable*/,
                 ARM_MPU_REGION_SIZE_16KB /* Size*/)
  );
/*************************************************************
 * 실습 가이드
 *   1) Region Number
 *   2) Base Address
 *   3) AccessPermission
 *   4) Size
 *
 * Region별 권장값
 *   Region4 : 시작주소 0x20018000, AccessPermission = ARM_MPU_AP_PRO , Size = ARM_MPU_REGION_SIZE_16KB
 *   Region5 : 시작주소 0x20020000, AccessPermission = ARM_MPU_AP_PRIV, Size = ARM_MPU_REGION_SIZE_16KB
 *   Region6 : 시작주소 0x20024000, AccessPermission = ARM_MPU_AP_URO , Size = ARM_MPU_REGION_SIZE_16KB
 *   Region7 : 시작주소 0x20028000, AccessPermission = ARM_MPU_AP_RO  , Size = ARM_MPU_REGION_SIZE_16KB
 *
 *  AccessPermission 설명
 *   - ARM_MPU_AP_FULL : 특권/사용자 모두 R/W
 *   - ARM_MPU_AP_PRO  : 특권 R/O, 사용자 NO access
 *   - ARM_MPU_AP_PRIV : 특권 R/W, 사용자 NO access
 *   - ARM_MPU_AP_URO  : 특권 R/W, 사용자 R/O
 *   - ARM_MPU_AP_RO   : 특권/사용자 모두 R/O
 *************************************************************/

  ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk
                 | MPU_CTRL_HFNMIENA_Msk
                 | MPU_CTRL_ENABLE_Msk);
}
