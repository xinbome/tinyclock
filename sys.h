#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
extern "C" {
#endif


void SYSTEM_EnableVIC(void);
void SYSTEM_DisableVIC(void);
void SYSTEM_EnableIRQ(void);
void SYSTEM_DisableIRQ(void);
void SYSTEM_EnableFIQ(void);
void SYSTEM_DisableFIQ(void);

void SYSTEM_EnableBP(void);
void SYSTEM_EnableICache(void);
void SYSTEM_DisableICache(void);
void SYSTEM_EnableDCache(void);
void SYSTEM_DisableDCache(void);
void SYSTEM_EnableMMU(void);
void SYSTEM_DisableMMU(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_H__*/
