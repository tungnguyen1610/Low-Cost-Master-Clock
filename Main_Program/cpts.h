#ifndef CPTS_H
#define CPTS_H
/******************
 * CPTS registers *
******************/
#define CPTS_BASE 0x4A100000
#define CPTS_IDVER_REG 0x4A100C00            // CPTS Identification and Version Register
#define CPTS_CONTROL_REG 0x4A100C04          // Time Sync Control Register
#define CPTS_RFTCLK_SEL_REG 0x4603D008       // Reference Clock Select Register
#define CPTS_TS_PUSH_REG 0x4A100C0C          // Time Stamp Event Push Register
#define CPTS_TS_LOAD_VAL_REG 0x4A100C10      // Time Stamp Load Low Value (lower 32-bits) Register
#define CPTS_TS_LOAD_EN_REG 0x4A100C14       // Time Stamp Load Enable Register
#define CPTS_TS_COMP_VAL_REG 0x4603D018      // Time Stamp Comparison Low Value (lower 32-bits) Register
#define CPTS_TS_COMP_LEN_REG 0x4603D01C      // Time Stamp Comparison Length Register
#define CPTS_INTSTAT_RAW_REG 0x4A100C20      // Interrupt Status Raw Register
#define CPTS_INTSTAT_MASKED_REG 0x4A100C24   // Interrupt Status Masked Register
#define CPTS_INT_ENABLE_REG 0x4A100C28       // Interrupt Enable Register Register
#define CPTS_TS_COMP_NUDGE_REG 0x4603D02C    // Time Stamp Comparison Nudge Value Register
#define CPTS_EVENT_POP_REG 0x4A100C30        // Event Interrupt Pop Register
#define CPTS_EVENT_0_REG 0x4A100C34          // Lower 32-bits of the Event Value Registersize_t length= (size_t)PAGE_SIZE;
#define CPTS_EVENT_1_REG 0x4A100C38          // Lower Middle 32-bits of the Event Value Register    

extern volatile uint32_t *cpts_Base; //declaration for external access in main program
#ifdef __cplusplus
extern "C" {
#endif
void setupCPTS();
#ifdef __cplusplus
}
#endif
#endif
