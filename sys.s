				AREA	|C$$code|, CODE, READONLY
						EXPORT	SYSTEM_EnableVIC
SYSTEM_EnableVIC		PROC
						mrc 	p15,0,r0,c1,c0,0
						orr 	r0,r0,#(1<<24)
						mcr 	p15,0,r0,c1,c0,0
						mov		pc,lr
						ENDP


						EXPORT	SYSTEM_DisableVIC
SYSTEM_DisableVIC		PROC
						mrc 	p15,0,r0,c1,c0,0
						bic 	r0,r0,#(1<<24)
						mcr 	p15,0,r0,c1,c0,0
						mov		pc,lr
						ENDP


						EXPORT	SYSTEM_EnableIRQ
SYSTEM_EnableIRQ		PROC
						mrs		r0,cpsr
						bic		r0,r0,#(1<<7)
						msr		cpsr_cxsf,r0             
						mov		pc,lr
						ENDP


						EXPORT	SYSTEM_DisableIRQ				
SYSTEM_DisableIRQ		PROC
						mrs		r0,cpsr
						orr		r0,r0,#(1<<7)
						msr		cpsr_cxsf,r0             
						mov		pc,lr
						ENDP
				
				

						EXPORT	SYSTEM_EnableFIQ
SYSTEM_EnableFIQ		PROC
						mrs		r0,cpsr
						bic		r0,r0,#(1<<6)
						msr		cpsr_cxsf,r0             
						mov		pc,lr
						ENDP


						EXPORT	SYSTEM_DisableFIQ
SYSTEM_DisableFIQ		PROC
						mrs		r0,cpsr
						orr		r0,r0,#(1<<6)
						msr		cpsr_cxsf,r0             
						mov		pc,lr
						ENDP
					 
;;===============================================================================
;;
;;	MMU/Cache
;;
					 
						EXPORT	SYSTEM_EnableBP
SYSTEM_EnableBP			PROC				
						mrc		p15,0,r0,c1,c0,0
						orr		r0,r0,#(1<<11)
						mcr		p15,0,r0,c1,c0,0
						mov		pc,lr
						ENDP
				
						EXPORT	SYSTEM_EnableICache
SYSTEM_EnableICache		PROC				
						mrc		p15,0,r0,c1,c0,0
						orr		r0,r0,#(1<<12)
						mcr		p15,0,r0,c1,c0,0
						mov		pc,lr
						ENDP


						EXPORT	SYSTEM_DisableICache
SYSTEM_DisableICache	PROC
						mrc		p15,0,r0,c1,c0,0
						bic		r0,r0,#(1<<12)
						mcr		p15,0,r0,c1,c0,0
						mov		pc,lr
						ENDP


						EXPORT	SYSTEM_EnableDCache
SYSTEM_EnableDCache		PROC
						mrc		p15,0,r0,c1,c0,0
						orr		r0,r0,#(1<<2)
						mcr		p15,0,r0,c1,c0,0
						mov		pc,lr
		   				ENDP


						EXPORT	SYSTEM_DisableDCache
SYSTEM_DisableDCache	PROC
						mrc		p15,0,r0,c1,c0,0
						bic		r0,r0,#(1<<2)
						mcr		p15,0,r0,c1,c0,0
						mov		pc,lr
						ENDP

						EXPORT	SYSTEM_EnableMMU
SYSTEM_EnableMMU		PROC
						mrc		p15,0,r0,c1,c0,0
						orr		r0,r0,#(1<<0)
						mcr		p15,0,r0,c1,c0,0
						mov		pc,lr
						ENDP


						EXPORT	SYSTEM_DisableMMU
SYSTEM_DisableMMU		PROC
						mrc		p15,0,r0,c1,c0,0
						bic		r0,r0,#(1<<0)
						mcr		p15,0,r0,c1,c0,0
						mov		pc,lr
						ENDP

				END
