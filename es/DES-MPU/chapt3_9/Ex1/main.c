#include "start.h"
#include "mpu_manual.h"
#include "mpu_configure.h"

#include <ARMCM3.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * Memory mapping with the regions that are accessed in the program.
 * The linker script defines the RAM, ROM addresses
 *
 * 0x20030000U
 *     Region 8 - Size 16KB
 * 0x20028000U
 *     Region 7 - Size 16KB
 * 0x20024000U
 *     Region 6 - Size 16KB
 * 0x20020000U
 *     Region 5 - Size 16KB
 * 0x20018000U
 *     Region 4 - Size 16KB
 * 0x20014000
 *     Region 3 - Size 16KB
 * 0x20010000
 *     Region 2 - Size 32KB
 * 0x20008000
 *     Region 1 - Size 32KB
 * 0x20000000
 *
 * ...
 *
 * 0x00020000
 *     Region 0 - 128KB
 * 0x00000000                                -- ROM
 *
 */
void accessRegionsMPU(bool manualConfiguration)
{
  uint32_t* const addrRegion2 = (uint32_t*) 0x20010000U;
  uint32_t* const addrRegion3 = (uint32_t*) 0x20014000U;
  uint32_t* const addrRegion4 = (uint32_t*) 0x20018000U;
  uint32_t* const addrRegion5 = (uint32_t*) 0x20020000U;
  uint32_t* const addrRegion6 = (uint32_t*) 0x20024000U;
  uint32_t* const addrRegion7 = (uint32_t*) 0x20028000U;
  
  uint32_t readValueRegion;
  /* Suppress warning as variable is only assigned and never used after */
  (void) readValueRegion;

  /* ARM_MPU_AP_NONE No access */
  logPrint("[R2] Write  -> expect MemManage Fault\n");
  *addrRegion2 = 0;
  /* Fault and MPU has been disabled in MemHandler. */
  disableMPU(manualConfiguration);

  logPrint("[R2] Read   -> expect MemManage Fault\n");
  readValueRegion = *addrRegion2;
  /* Fault and MPU has been disabled in MemHandler. */
  disableMPU(manualConfiguration);

  /* ARM_MPU_AP_FULL  Full access */
  logPrint("[R3] Write  -> expect NO fault\n");
  *addrRegion3 = 0;
  disableMPU(manualConfiguration);
  logPrint("[R3] Read   -> expect NO fault\n");
  readValueRegion = *addrRegion3;
  
  /* No fault. No need to enable MPU. */
  logPrint("\n [R3] inside sub region 1(disabled)\n");
  uint32_t *const sr1 = (uint32_t*)(0x20014000 + 0x0800);
  logPrint("[R3] inside sub region 2(AP PRO)\n");
  uint32_t *const sr2 = (uint32_t*)(0x20014000 + 0x1000);
  logPrint("[R3] Try WRITE to sub region 1 (disabled, should succed)\n");
  *sr1=0;
  logPrint("[R3] Try WRITE to sub region 2 (enabled, should fault)\n");
  *sr2=0;

  /* ARM_MPU_AP_PRO  Privileged Read-only */
  logPrint("[R4] Read   -> expect NO fault (Privileged read)\n");
  readValueRegion = *addrRegion4;
  logPrint("[R4] Write  -> expect MemManage Fault (Privileged write)\n");
  *addrRegion4 = 0;
  disableMPU(manualConfiguration);
  
  logPrint("[R5] Write  -> expect NO fault (Privileged write)\n");
  *addrRegion5 = 0;
  logPrint("[R5] Read   -> expect NO fault (Privileged read)\n");
  readValueRegion = *addrRegion5;
  
  logPrint("[R6] Write  -> expect NO fault (Privileged write)\n");
  *addrRegion6 = 0;
  logPrint("[R6] Read   -> expect NO fault (Privileged read)\n");
  readValueRegion = *addrRegion6;
  
  logPrint("[R7] Write  -> expect MemManage Fault (Privileged write)\n");
  *addrRegion7 = 0;
  disableMPU(manualConfiguration);
  logPrint("[R7] Read   -> expect NO fault\n");
  readValueRegion = *addrRegion7;

}

int main(void)
{
  __set_PSP(0x20000000U);

  logPrint("Control 0x%x\n"
           "PSP 0x%x\n"
           "MSP 0x%x\n\n",
            __get_CONTROL(), __get_PSP(), __get_MSP());

  //ManualInitMPU();
  //accessRegionsMPU(true);

  CmsisInitMPU();
  accessRegionsMPU(false);

  return 0;
}

