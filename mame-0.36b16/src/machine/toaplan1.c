/***************************************************************************
					ToaPlan  (1988-1991 hardware)
 ***************************************************************************/

#include "driver.h"
#include "cpu/m68000/m68000.h"
#include "cpu/tms32010/tms32010.h"



int  video_ofs3_r(int offset);
void video_ofs3_w(int offset, int data);
void toaplan1_videoram3_w(int offset, int data);

int toaplan1_coin_count; /* coin count increments on startup ? , so dont count it */

int toaplan1_int_enable;
static int unk;
static int credits;
static int latch;
static int dsp_execute;
static unsigned int dsp_addr_w, main_ram_seg;

extern unsigned char *toaplan1_sharedram;



int demonwld_dsp_in(int offset)
{
	/* DSP can read data from main CPU RAM via DSP IO port 1 */

	unsigned int input_data = 0;

	switch (main_ram_seg) {
		case 0xc00000:	input_data = READ_WORD(&(cpu_bankbase[1][(dsp_addr_w)])); break;

		default:		if (errorlog)
							fprintf(errorlog,"DSP PC:%04x Warning !!! IO reading from %08x (port 1)\n",cpu_getpreviouspc(),main_ram_seg + dsp_addr_w);
	}
	if (errorlog) fprintf(errorlog,"DSP PC:%04x IO read %04x at %08x (port 1)\n",cpu_getpreviouspc(),input_data,main_ram_seg + dsp_addr_w);
	return input_data;
}

void demonwld_dsp_out(int fnction,int data)
{
	if (fnction == 0) {
		/* This sets the main CPU RAM address the DSP should */
		/*		read/write, via the DSP IO port 0 */
		/* Top three bits of data need to be shifted left 9 places */
		/*		to select which memory bank from main CPU address */
		/*		space to use */
		/* Lower thirteen bits of this data is shifted left one position */
		/*		to move it to an even address word boundary */

		dsp_addr_w = ((data & 0x1fff) << 1);
		main_ram_seg = ((data & 0xe000) << 9);
		if (errorlog) fprintf(errorlog,"DSP PC:%04x IO write %04x (%08x) at port 0\n",cpu_getpreviouspc(),data,main_ram_seg + dsp_addr_w);
	}
	if (fnction == 1) {
		/* Data written to main CPU RAM via DSP IO port 1*/

		dsp_execute = 0;
		switch (main_ram_seg) {
			case 0xc00000:	WRITE_WORD(&(cpu_bankbase[1][(dsp_addr_w)]),data);
							if ((dsp_addr_w < 3) && (data == 0)) dsp_execute = 1; break;
			default:		if (errorlog)
								fprintf(errorlog,"DSP PC:%04x Warning !!! IO writing to %08x (port 1)\n",cpu_getpreviouspc(),main_ram_seg + dsp_addr_w);
		}
		if (errorlog) fprintf(errorlog,"DSP PC:%04x IO write %04x at %08x (port 1)\n",cpu_getpreviouspc(),data,main_ram_seg + dsp_addr_w);
	}
	if (fnction == 3) {
		/* data 0xffff	means inhibit BIO line to DSP and enable  */
		/*				communication to main processor */
		/*				Actually only DSP data bit 15 controls this */
		/* data 0x0000	means set DSP BIO line active and disable */
		/*				communication to main processor*/
		if (errorlog) fprintf(errorlog,"DSP PC:%04x IO write %04x at port 3\n",cpu_getpreviouspc(),data);
		if (data & 0x8000) {
			cpu_set_irq_line(2, TMS320C10_ACTIVE_BIO, CLEAR_LINE);
		}
		if (data == 0) {
			if (dsp_execute) {
				if (errorlog) fprintf(errorlog,"Turning Main 68000 on\n");
				cpu_set_halt_line(0,CLEAR_LINE);
				dsp_execute = 0;
			}
			cpu_set_irq_line(2, TMS320C10_ACTIVE_BIO, ASSERT_LINE);
		}
	}
}

void demonwld_dsp_w(int offset,int data)
{
#if 0
	if (errorlog) fprintf(errorlog,"68000:%08x  Writing %08x to %08x.\n",cpu_get_pc() ,data ,0xe0000a + offset);
#endif

	switch (data) {
		case 0x0000: 	/* This means assert the INT line to the DSP */
						if (errorlog) fprintf(errorlog,"Turning DSP on and 68000 off\n");
						cpu_set_halt_line(2,CLEAR_LINE);
						cpu_set_irq_line(2, TMS320C10_ACTIVE_INT, ASSERT_LINE);
						cpu_set_halt_line(0,ASSERT_LINE);
						break;
		case 0x0001: 	/* This means inhibit the INT line to the DSP */
						if (errorlog) fprintf(errorlog,"Turning DSP off\n");
						cpu_set_irq_line(2, TMS320C10_ACTIVE_INT, CLEAR_LINE);
						cpu_set_halt_line(2,ASSERT_LINE);
						break;
		default:		if (errorlog)
							fprintf(errorlog,"68000:%04x  writing unknown command %08x to %08x\n",cpu_getpreviouspc() ,data ,0xe0000a + offset);
	}
}



int toaplan1_interrupt(void)
{
	if (toaplan1_int_enable)
		return MC68000_IRQ_4;
	return MC68000_INT_NONE;
}

void toaplan1_int_enable_w(int offset, int data)
{
	toaplan1_int_enable = data;
}

int toaplan1_unk_r(int offset)
{
	return unk ^= 1;
}

int vimana_input_port_4_r(int offset)
{
	int data, p;

	p = input_port_4_r(0);

	latch ^= p;
	data = (latch & p );

	/* simulate the mcu keeping track of credits */
	/* latch is so is doesn't add more than one */
	/* credit per keypress */

	if (data & 0x18)
	{
		credits++ ;
	}

	latch = p;

	return p;
}

int vimana_mcu_r(int offset)
{
	int data = 0 ;
	switch (offset >> 1)
	{
		case 0:
			data = 0xff;
			break;
		case 1:
			data = 0;
			break;
		case 2:
			data = credits;
			break;
	}
	return data;
}
void vimana_mcu_w(int offset, int data)
{
	switch (offset >> 1)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			credits = data;
			break;
	}
}

int toaplan1_shared_r(int offset)
{
	return toaplan1_sharedram[offset>>1];
}

void toaplan1_shared_w(int offset, int data)
{
	toaplan1_sharedram[offset>>1] = data;
}

void toaplan1_init_machine(void)
{
	dsp_addr_w = dsp_execute = 0;
	main_ram_seg = 0;
	toaplan1_int_enable = 0;
	unk = 0;
	credits = 0;
	latch = 0;
	toaplan1_coin_count = 0;
	coin_lockout_global_w(0,0);
}

void rallybik_coin_w(int offset,int data)
{
	switch (data) {
		case 0x08: if (toaplan1_coin_count) { coin_counter_w(0,1); coin_counter_w(0,0); } break;
		case 0x09: if (toaplan1_coin_count) { coin_counter_w(2,1); coin_counter_w(2,0); } break;
		case 0x0a: if (toaplan1_coin_count) { coin_counter_w(1,1); coin_counter_w(1,0); } break;
		case 0x0b: if (toaplan1_coin_count) { coin_counter_w(3,1); coin_counter_w(3,0); } break;
		case 0x0c: coin_lockout_w(0,1); coin_lockout_w(2,1); break;
		case 0x0d: coin_lockout_w(0,0); coin_lockout_w(2,0); break;
		case 0x0e: coin_lockout_w(1,1); coin_lockout_w(3,1); break;
		case 0x0f: coin_lockout_w(1,0); coin_lockout_w(3,0); toaplan1_coin_count=1; break;
	}
}

void toaplan1_coin_w(int offset,int data)
{
	if (errorlog) fprintf(errorlog,"Z80 writing %02x to coin control\n",data);
	/* This still isnt too clear yet. */
	/* Coin C has no coin lock ? */
	/* Are some outputs for lights ? (no space on JAMMA for it though) */

	switch (data) {
		case 0xee: coin_counter_w(1,1); coin_counter_w(1,0); break; /* Count slot B */
		case 0xed: coin_counter_w(0,1); coin_counter_w(0,0); break; /* Count slot A */
	/* The following are coin counts after coin-lock active (faulty coin-lock ?) */
		case 0xe2: coin_counter_w(1,1); coin_counter_w(1,0); coin_lockout_w(1,1); break;
		case 0xe1: coin_counter_w(0,1); coin_counter_w(0,0); coin_lockout_w(0,1); break;

		case 0xec: coin_lockout_global_w(0,0); break;	/* ??? count games played */
		case 0xe8: break;	/* ??? Maximum credits reached with coin/credit ratio */
		case 0xe4: break;	/* ??? Reset coin system */

		case 0x0c: coin_lockout_global_w(0,0); break;	/* Unlock all coin slots */
		case 0x08: coin_lockout_w(2,0); break;	/* Unlock coin slot C */
		case 0x09: coin_lockout_w(0,0); break;	/* Unlock coin slot A */
		case 0x0a: coin_lockout_w(1,0); break;	/* Unlock coin slot B */

		case 0x02: coin_lockout_w(1,1); break;	/* Lock coin slot B */
		case 0x01: coin_lockout_w(0,1); break;	/* Lock coin slot A */
		case 0x00: coin_lockout_global_w(0,1); break;	/* Lock all coin slots */
	}
}
