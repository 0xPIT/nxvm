/* This file is a part of NXVM project. */

#define PRODUCT "Neko's x86 Virtual Machine [0.1.0x64]\n\
Copyright (c) 2012-2013 Neko. All rights reserved.\n"

/*
 * Developer: Xu Ha
 * Email:     cshaxu@gatech.edu
 * Start:     01/25/2012
 * End:       (null)
 *
 * Project Phases
 * 1. Read documents and list all necessary functionality
 * 2. Code the functions
 * 3. Add comment for each I/O function, check logic
 * 4. Create test functions and corresponding test case
 * 5. Perform unit tests
 * 6. Read official document and PC.PDF, then check logic
 *
 * Module: Console
 *     Files:   main.c, global.h
 *     Files:   console.c, console.h
 *     Files:   dosint.c, dosint.h
 *
 * Module: Debugger
 * Component 1: debugger
 *     Files:   debug.c, debug.h
 *     Phase 1:
 *     Phase 2: 01/01/2012 - 01/24/2012
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 * Component 2: asembler
 *     Files:   asm86.c, asm86.h
 *     Phase 1:
 *     Phase 2: 01/25/2012 - 01/31/2012
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 * Component 3: disassembler 
 *     Files:   asm86.c, asm86.h
 *     Phase 1:
 *     Phase 2: 02/01/2012 - 02/05/2012
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 *
 * Module: VMachine - Global
 * Component 1: types and definitions
 *     Files:   global.h, coption.h
 *     Phase 1:
 *     Phase 2: done
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 * Component 2: chassis
 *     Files:   vmachine.c, vmachine.h
 *     Phase 1:
 *     Phase 2: done
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 *
 * Module: VMachine - Kernel
 * Component 1: cpu (8086)
 *     Files:   vcpu.c, vcpu.h
 *     Files:   vcpuins.c, vcpuins.h
 *     Phase 1:
 *     Phase 2: 02/06/2012 - 02/12/2012
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 *     Note:    simply tested
 * Component 2: ram
 *     Files:   vram.c, vram.h
 *     Phase 1:
 *     Phase 2: 02/06/2012 - 02/12/2012
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 *     Note:    simply tested
 * Component 3: pic (8259)
 *     Files:   vpic.c, vpic.h
 *     Phase 1: 02/06/2012 - 02/12/2012
 *     Phase 2: 02/06/2012 - 02/12/2012
 *     Phase 3: 03/17/2013 - 03/21/2013
 *     Phase 4: 03/20/2013 - 03/21/2013
 *     Phase 5: 03/21/2013 - 03/21/2013
 *     Phase 6:
 *     Note:    fully tested, except for
 *              OCW2, ICW4(AEOI) not tested
 * Component 4: pit (8254)
 *     Files:   vpit.c, vpit.h
 *     Phase 1: 03/22/2013 - 03/23/2013
 *     Phase 2: 03/03/2012 - 04/01/2012
 *     Phase 3: 03/23/2013 - 03/25/2013
 *     Phase 4: 03/25/2013 - 03/25/2013
 *     Phase 5:
 *     Phase 6:
 *     Note:    simply tested
 * Component 5: dma (8237)
 *     Files:   vdma.c, vdma.h
 *     Phase 1: 03/25/2013 - 03/28/2013
 *     Phase 2: 03/03/2012 - 04/01/2012
 *     Phase 3: 03/25/2013 - 03/28/2013
 *     Phase 4: 03/25/2013 - 03/28/2013
 *     Phase 5:
 *     Phase 6:
 *     Note:    simply tested
 * Componenet 6: fdc (8272)
 *     Phase 1:
 *     Phase 2: 03/07/2012 - 03/18/2012
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 *     Note:    Transfers data between flp image and memory
 * Componenet 7: fdd
 *     Phase 1:
 *     Phase 2: 03/08/2012 - 03/18/2012
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 *     Note:    Load and unload floppy image file
 *
 * Module: VMachine - HCI
 * Component 1: kbc
 *     Files:   vkbc.c, vkbc.h
 * Component 2: keyb (?)
 *     Files:   vkeyb.c, vkeyb.h
 * Component 3: vadapter
 *     Files:  vvadp.c, vvadp.h
 * Component 4: display (?)
 *     Files:  vdisp.c, vdisp.h
 *
 * Module: VMachine - BIOS
 * Component 1: cmos
 *     Files:   vcmos.c, vcmos.h
 *     Phase 1:
 *     Phase 2: 03/02/2012 - 04/01/2012
 *     Phase 3:
 *     Phase 4:
 *     Phase 5:
 *     Phase 6:
 *     Note:    init regs; continue when creating BIOS
 * Component 2: bios
 *     Files:   vbios.asm
 *
 * Module: VMachine - Platform Related APIs
 * Component 1: none
 *     Files:   vapi.c, vapi.h
 * Component 2: win32con
 *     Files:   win32con.c, win32con.h
 * Component 3: win32app
 *     Files:   win32app.c, win32app.h
 *
 * Module: VMachine - Additional
 * Component 1: serial
 *     Files:   vseri.c, vseri.h
 * Component 2: parallel
 *     Files:   vpara.c, vpara.h
 * Component 3: hdc, hdd
 *     Files:   vhdc.c, vhdc.h, vhdd.c, vhdd.h
 * Component 4: printer
 *     Files:   vprinter.c, vprinter.h
 * Component 5: cdrom
 *     Files:   vcdrom.c, vcdrom.h
 *
 * Format Unify:
 * all boolean type should be t_bool, declared TRUE or FALSE
 * check all parameters of macros
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "vmachine/coption.h"
#include "global.h"
#include "console.h"

#if NXVM_SYSTEM == NXVM_NONE
int main(int argc, char **argv)
{
	fprintf(stdout,"%s\n",PRODUCT);
	NSConsole();
    return 0;
}
#elif NXVM_SYSTEM == NXVM_LINUX_TERMINAL
#elif NXVM_SYSTEM == NXVM_LINUX_APPLICATION
#elif NXVM_SYSTEM == NXVM_WIN32_CONSOLE
int main(int argc, char **argv)
{
	fprintf(stdout, "%s\n", PRODUCT);
	NSConsole();
    return 0;
}
#elif NXVM_SYSTEM == NXVM_WIN32_APPLICATION
#include "windows.h"
/*
#pragma comment(linker, \
	"/subsystem:\"console\" /entry:\"WinMainCRTStartup\"") 
#pragma comment(linker, \
	"/manifestdependency:\"type='win32' \
	 name='Microsoft.Windows.Common-Controls' \
	 version='6.0.0.0' \
	 processorArchitecture='*' \
	 publicKeyToken='6595b64144ccf1df' \
	 language='*'\"")
*/
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPreInstance,
                   LPSTR lpCmdLine,
                   int nShowCmd)
{
	return 0;
}
#else
#endif

/********************************************
* COMMENTS
*	unsigned int x = (unsigned int)test;
*	void (*y)(void) = (*(void (*)(void))(x));
*	y();
*	MessageBox(NULL,"Neko's x86 Virtual Machine WIN32APP Edition","WinMain",MB_OK);
*	The NTVDM CPU has encountered an illegal instruction.
*	CS:0db 1 IP:ffd3 OP:63 fa 65 13 64 Choose 'close' to terminate the application.
********************************************/