/*** TMS34010: Portable TMS34010 emulator ***********************************

	Copyright (C) Alex Pasadyn/Zsolt Vasvari 1998
	 originally based on code by Aaron Giles

	This is a private include file. Drivers should NOT include it, but
	use TMS34010.h instead.

*****************************************************************************/

#ifndef _34010OPS_H
#define _34010OPS_H

#include "osd_cpu.h"
#include "memory.h"

#define SIGN(val) ((val)&0x80000000)

#define INVALID_PIX_ADDRESS  0xffffffe0  /* This is the reset vector, this should be ok */

#ifndef INLINE
#define INLINE static inline
#endif

/* Size of the memory buffer allocated for the shiftr register */
#define SHIFTREG_SIZE		 (8*512*sizeof(UINT16))

/****************************************************************************/
/* Read a byte from given memory location                                   */
/****************************************************************************/
#define TMS34010_RDMEM(A)       ((unsigned)cpu_readmem29      (A))
#define TMS34010_RDMEM_WORD(A)  ((unsigned)cpu_readmem29_word (A))
#define TMS34010_RDMEM_DWORD(A) ((unsigned)cpu_readmem29_dword(A))

/****************************************************************************/
/* Write a byte to given memory location                                    */
/****************************************************************************/
#define TMS34010_WRMEM(A,V) (cpu_writemem29(A,V))
#define TMS34010_WRMEM_WORD(A,V) (cpu_writemem29_word(A,V))
#define TMS34010_WRMEM_DWORD(A,V) (cpu_writemem29_dword(A,V))

#define STACKPTR(ADDR)	state.stackbase + TOBYTE((UINT32)(ADDR))

/****************************************************************************/
/* I/O constants and function prototypes 									*/
/****************************************************************************/
#define REG_HESYNC		0
#define REG_HEBLNK		1
#define REG_HSBLNK		2
#define REG_HTOTAL		3
#define REG_VESYNC		4
#define REG_VEBLNK		5
#define REG_VSBLNK		6
#define REG_VTOTAL		7
#define REG_DPYCTL		8
#define REG_DPYSTRT		9
#define REG_DPYINT		10
#define REG_CONTROL		11
#define REG_HSTDATA		12
#define REG_HSTADRL		13
#define REG_HSTADRH		14
#define REG_HSTCTLL		15
#define REG_HSTCTLH		16
#define REG_INTENB		17
#define REG_INTPEND		18
#define REG_CONVSP		19
#define REG_CONVDP		20
#define REG_PSIZE		21
#define REG_PMASK		22
#define REG_DPYTAP		27
#define REG_HCOUNT		28
#define REG_VCOUNT		29
#define REG_DPYADR		30
#define REG_REFCNT		31

/* Interrupts that are generated by the processor internally */
#define TMS34010_NMI         0x0100    /* NMI Interrupt */
#define TMS34010_HI          0x0200    /* Host Interrupt */
#define TMS34010_DI          0x0400    /* Display Interrupt */
#define TMS34010_WV          0x0800    /* Window Violation Interrupt */

/* IO registers accessor */
#define IOREG(reg)	     (state.IOregs[reg])
#define CONTEXT_IOREG(c,reg) ((c)->IOregs[reg])
#define PBH (IOREG(REG_CONTROL) & 0x0100)
#define PBV (IOREG(REG_CONTROL) & 0x0200)

#define WFIELDMAC(MASK,MAX) 														\
	UINT32 shift = bitaddr&0x0f;     												\
	UINT32 old;				   														\
	bitaddr = (TOBYTE(bitaddr&0xfffffff0));											\
																					\
	if (shift >= MAX)																\
	{																				\
		old = ((UINT32) TMS34010_RDMEM_DWORD(bitaddr)&~((MASK)<<shift)); 			\
		TMS34010_WRMEM_DWORD(bitaddr,((data&(MASK))<<shift)|old);					\
	}																				\
	else																			\
	{																				\
		old = ((UINT32) TMS34010_RDMEM_WORD (bitaddr)&~((MASK)<<shift)); 			\
		TMS34010_WRMEM_WORD (bitaddr,((data&(MASK))<<shift)|old);			   		\
	}

#define RFIELDMAC_Z(MASK,MAX)									\
	UINT32 shift = bitaddr&0x0f;							    \
	bitaddr = TOBYTE(bitaddr&0xfffffff0);						\
																\
	if (shift >= MAX)											\
	{															\
		return ((TMS34010_RDMEM_DWORD(bitaddr)>>shift)&(MASK));	\
	}															\
	else														\
	{															\
		return ((TMS34010_RDMEM_WORD (bitaddr)>>shift)&(MASK));	\
	}

#define RFIELDMAC_S(MASK,MAX)									\
	UINT32 ret;													\
	UINT32 shift = bitaddr&0x0f;							    \
	bitaddr = TOBYTE(bitaddr&0xfffffff0);						\
																\
	if (shift >= MAX)											\
	{															\
		ret = ((TMS34010_RDMEM_DWORD(bitaddr)>>shift)&(MASK));	\
	}															\
	else														\
	{															\
		ret = ((TMS34010_RDMEM_WORD (bitaddr)>>shift)&(MASK));	\
	}

#define WFIELDMAC_8												\
	if (bitaddr&0x07)											\
	{															\
		WFIELDMAC(0xff,9);										\
	}															\
	else														\
	{															\
		TMS34010_WRMEM(TOBYTE(bitaddr),data);					\
	}

#define RFIELDMAC_Z_8											\
	if (bitaddr&0x07)											\
	{															\
		RFIELDMAC_Z(0xff,9);									\
	}															\
	else														\
	{															\
		return TMS34010_RDMEM(TOBYTE(bitaddr));					\
	}

#define WFIELDMAC_32											\
	if (bitaddr&0x0f)											\
	{															\
		UINT32 shift = bitaddr&0x0f;							\
		UINT32 old;												\
		UINT32 hiword;											\
		bitaddr &= 0xfffffff0;									\
		old =    ((UINT32) TMS34010_RDMEM_DWORD (TOBYTE(bitaddr     ))&(0xffffffff>>(0x20-shift)));	\
		hiword = ((UINT32) TMS34010_RDMEM_DWORD (TOBYTE(bitaddr+0x20))&(0xffffffff<<shift));		\
		TMS34010_WRMEM_DWORD(TOBYTE(bitaddr     ),(data<<      shift) |old);						\
		TMS34010_WRMEM_DWORD(TOBYTE(bitaddr+0x20),(data>>(0x20-shift))|hiword);						\
	}															\
	else														\
	{															\
		TMS34010_WRMEM_DWORD(TOBYTE(bitaddr),data);				\
	}

#define RFIELDMAC_32											\
	if (bitaddr&0x0f)											\
	{															\
		UINT32 shift = bitaddr&0x0f;							\
		bitaddr &= 0xfffffff0;									\
		return (((UINT32)TMS34010_RDMEM_DWORD (TOBYTE(bitaddr     ))>>      shift) |	\
			            (TMS34010_RDMEM_DWORD (TOBYTE(bitaddr+0x20))<<(0x20-shift)));	\
	}															\
	else														\
	{															\
		return TMS34010_RDMEM_DWORD(TOBYTE(bitaddr));			\
	}


void wfield_01(UINT32 bitaddr, UINT32 data);
void wfield_02(UINT32 bitaddr, UINT32 data);
void wfield_03(UINT32 bitaddr, UINT32 data);
void wfield_04(UINT32 bitaddr, UINT32 data);
void wfield_05(UINT32 bitaddr, UINT32 data);
void wfield_06(UINT32 bitaddr, UINT32 data);
void wfield_07(UINT32 bitaddr, UINT32 data);
void wfield_08(UINT32 bitaddr, UINT32 data);
void wfield_09(UINT32 bitaddr, UINT32 data);
void wfield_10(UINT32 bitaddr, UINT32 data);
void wfield_11(UINT32 bitaddr, UINT32 data);
void wfield_12(UINT32 bitaddr, UINT32 data);
void wfield_13(UINT32 bitaddr, UINT32 data);
void wfield_14(UINT32 bitaddr, UINT32 data);
void wfield_15(UINT32 bitaddr, UINT32 data);
void wfield_16(UINT32 bitaddr, UINT32 data);
void wfield_17(UINT32 bitaddr, UINT32 data);
void wfield_18(UINT32 bitaddr, UINT32 data);
void wfield_19(UINT32 bitaddr, UINT32 data);
void wfield_20(UINT32 bitaddr, UINT32 data);
void wfield_21(UINT32 bitaddr, UINT32 data);
void wfield_22(UINT32 bitaddr, UINT32 data);
void wfield_23(UINT32 bitaddr, UINT32 data);
void wfield_24(UINT32 bitaddr, UINT32 data);
void wfield_25(UINT32 bitaddr, UINT32 data);
void wfield_26(UINT32 bitaddr, UINT32 data);
void wfield_27(UINT32 bitaddr, UINT32 data);
void wfield_28(UINT32 bitaddr, UINT32 data);
void wfield_29(UINT32 bitaddr, UINT32 data);
void wfield_30(UINT32 bitaddr, UINT32 data);
void wfield_31(UINT32 bitaddr, UINT32 data);
void wfield_32(UINT32 bitaddr, UINT32 data);

INT32 rfield_s_01(UINT32 bitaddr);
INT32 rfield_s_02(UINT32 bitaddr);
INT32 rfield_s_03(UINT32 bitaddr);
INT32 rfield_s_04(UINT32 bitaddr);
INT32 rfield_s_05(UINT32 bitaddr);
INT32 rfield_s_06(UINT32 bitaddr);
INT32 rfield_s_07(UINT32 bitaddr);
INT32 rfield_s_08(UINT32 bitaddr);
INT32 rfield_s_09(UINT32 bitaddr);
INT32 rfield_s_10(UINT32 bitaddr);
INT32 rfield_s_11(UINT32 bitaddr);
INT32 rfield_s_12(UINT32 bitaddr);
INT32 rfield_s_13(UINT32 bitaddr);
INT32 rfield_s_14(UINT32 bitaddr);
INT32 rfield_s_15(UINT32 bitaddr);
INT32 rfield_s_16(UINT32 bitaddr);
INT32 rfield_s_17(UINT32 bitaddr);
INT32 rfield_s_18(UINT32 bitaddr);
INT32 rfield_s_19(UINT32 bitaddr);
INT32 rfield_s_20(UINT32 bitaddr);
INT32 rfield_s_21(UINT32 bitaddr);
INT32 rfield_s_22(UINT32 bitaddr);
INT32 rfield_s_23(UINT32 bitaddr);
INT32 rfield_s_24(UINT32 bitaddr);
INT32 rfield_s_25(UINT32 bitaddr);
INT32 rfield_s_26(UINT32 bitaddr);
INT32 rfield_s_27(UINT32 bitaddr);
INT32 rfield_s_28(UINT32 bitaddr);
INT32 rfield_s_29(UINT32 bitaddr);
INT32 rfield_s_30(UINT32 bitaddr);
INT32 rfield_s_31(UINT32 bitaddr);
INT32 rfield_32(UINT32 bitaddr);

INT32 rfield_z_01(UINT32 bitaddr);
INT32 rfield_z_02(UINT32 bitaddr);
INT32 rfield_z_03(UINT32 bitaddr);
INT32 rfield_z_04(UINT32 bitaddr);
INT32 rfield_z_05(UINT32 bitaddr);
INT32 rfield_z_06(UINT32 bitaddr);
INT32 rfield_z_07(UINT32 bitaddr);
INT32 rfield_z_08(UINT32 bitaddr);
INT32 rfield_z_09(UINT32 bitaddr);
INT32 rfield_z_10(UINT32 bitaddr);
INT32 rfield_z_11(UINT32 bitaddr);
INT32 rfield_z_12(UINT32 bitaddr);
INT32 rfield_z_13(UINT32 bitaddr);
INT32 rfield_z_14(UINT32 bitaddr);
INT32 rfield_z_15(UINT32 bitaddr);
INT32 rfield_z_16(UINT32 bitaddr);
INT32 rfield_z_17(UINT32 bitaddr);
INT32 rfield_z_18(UINT32 bitaddr);
INT32 rfield_z_19(UINT32 bitaddr);
INT32 rfield_z_20(UINT32 bitaddr);
INT32 rfield_z_21(UINT32 bitaddr);
INT32 rfield_z_22(UINT32 bitaddr);
INT32 rfield_z_23(UINT32 bitaddr);
INT32 rfield_z_24(UINT32 bitaddr);
INT32 rfield_z_25(UINT32 bitaddr);
INT32 rfield_z_26(UINT32 bitaddr);
INT32 rfield_z_27(UINT32 bitaddr);
INT32 rfield_z_28(UINT32 bitaddr);
INT32 rfield_z_29(UINT32 bitaddr);
INT32 rfield_z_30(UINT32 bitaddr);
INT32 rfield_z_31(UINT32 bitaddr);

#endif /* _34010OPS_H */
