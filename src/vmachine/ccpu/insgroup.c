
#include "../vmachine.h"
#include "ccpuapi.h"

#define rotl(x,n) ((((x)<<(n))&(-(1<<(n))))|(((x)>>(sizeof(x)*8-(n)))&((1<<(n))-1)))
#define ror(x) rotl((x),1)

static t_bool getSignByData_data8(const t_nubit8 data) {return !!(data & MASK_10000000);}
static t_bool getSignByData_data16(const t_nubit16 data) {return !!(data & 0x8000);}
static t_bool getFinalBit_data8(const t_nubit8 data) {return !!(data & MASK_00000001);}
static t_bool getFinalBit_data16(const t_nubit16 data) {return !!(data & 1);}
static t_bool isSignBitChange_data8(const t_nubit8 fir, const t_nubit8 sec)
{
	if(getSignByData_data8(fir) == getSignByData_data8(sec))
		return 0x00;
	return 0x01;
}
static t_bool isSignBitChange_data16(const t_nubit16 fir, const t_nubit16 sec)
{
	if(getSignByData_data16(fir) == getSignByData_data16(sec))
		return 0x00;
	return 0x01;
}
////////////////////////////////////////////<GROUP1> :DONE
void ins_methodGroup_ADD_Eb_Ib()//tested
{
	ins_atomMethod_ADD_8bit(p_nubit8(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_8Bit);
}
void ins_methodGroup_ADD_Ev_Iv()//tested
{
	ins_atomMethod_ADD_16bit(p_nubit16(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_16Bit);
}
void ins_methodGroup_ADD_Ev_Ib()//tested
{
	t_nubit16 tmp = ccpu.deCodeBlock.immData_8Bit;
	ins_atomMethod_ADD_16bit(p_nubit16(ccpu.deCodeBlock.prm), tmp);
}

void ins_methodGroup_OR_Eb_Ib()
{
	ins_atomMethod_OR_8bit(p_nubit8(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_8Bit);
}
void ins_methodGroup_OR_Ev_Iv()
{
	ins_atomMethod_OR_16bit(p_nubit16(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_16Bit);
}
void ins_methodGroup_OR_Ev_Ib()
{
	//vapiCallBackMachineStop();;//may be some problem
	t_nubit16 tmp = ccpu.deCodeBlock.immData_8Bit;
	ins_atomMethod_OR_16bit(p_nubit16(ccpu.deCodeBlock.prm), tmp);
}

void ins_methodGroup_ADC_Eb_Ib()//tested
{
	ins_atomMethod_ADC_8bit(p_nubit8(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_8Bit);
}
void ins_methodGroup_ADC_Ev_Iv()//tested
{
	ins_atomMethod_ADC_16bit(p_nubit16(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_16Bit);
}
void ins_methodGroup_ADC_Ev_Ib()//tested
{
	//vapiCallBackMachineStop();;//may be some problem
	t_nubit16 tmp = ccpu.deCodeBlock.immData_8Bit;
	ins_atomMethod_ADC_16bit(p_nubit16(ccpu.deCodeBlock.prm), tmp);
}

void ins_methodGroup_SBB_Eb_Ib()
{
	ins_atomMethod_SBB_8bit(p_nubit8(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_8Bit);
}
void ins_methodGroup_SBB_Ev_Iv()
{
	ins_atomMethod_SBB_16bit(p_nubit16(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_16Bit);
}
void ins_methodGroup_SBB_Ev_Ib()
{
	//vapiCallBackMachineStop();;//may be some problem
	t_nubit16 tmp = ccpu.deCodeBlock.immData_8Bit;
	ins_atomMethod_SBB_16bit(p_nubit16(ccpu.deCodeBlock.prm), tmp);
}

void ins_methodGroup_AND_Eb_Ib()
{
	ins_atomMethod_AND_8bit(p_nubit8(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_8Bit);
}
void ins_methodGroup_AND_Ev_Iv()
{
	ins_atomMethod_AND_16bit(p_nubit16(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_16Bit);
}
void ins_methodGroup_AND_Ev_Ib()
{
	//vapiCallBackMachineStop();;//may be some problem
	t_nubit16 tmp = ccpu.deCodeBlock.immData_8Bit;
	ins_atomMethod_AND_16bit(p_nubit16(ccpu.deCodeBlock.prm), tmp);
}

void ins_methodGroup_SUB_Eb_Ib()//tested
{
	ins_atomMethod_SUB_8bit(p_nubit8(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_8Bit);
}
void ins_methodGroup_SUB_Ev_Iv()//tested
{
	ins_atomMethod_SUB_16bit(p_nubit16(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_16Bit);
}
void ins_methodGroup_SUB_Ev_Ib()//tested
{
	//vapiCallBackMachineStop();;//may be some problem
	t_nubit16 tmp = ccpu.deCodeBlock.immData_8Bit;
	ins_atomMethod_SUB_16bit(p_nubit16(ccpu.deCodeBlock.prm), tmp);
}

void ins_methodGroup_XOR_Eb_Ib()
{
	ins_atomMethod_XOR_8bit(p_nubit8(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_8Bit);
}
void ins_methodGroup_XOR_Ev_Iv()
{
	ins_atomMethod_XOR_16bit(p_nubit16(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_16Bit);
}
void ins_methodGroup_XOR_Ev_Ib()
{
	//vapiCallBackMachineStop();;//may be some problem
	t_nubit16 tmp = ccpu.deCodeBlock.immData_8Bit;
	ins_atomMethod_XOR_16bit(p_nubit16(ccpu.deCodeBlock.prm), tmp);
}

void ins_methodGroup_CMP_Eb_Ib()
{
	ins_atomMethod_CMP_8bit(d_nubit8(ccpu.deCodeBlock.prm), d_nsbit8(&ccpu.deCodeBlock.immData_8Bit));
}
void ins_methodGroup_CMP_Ev_Iv()
{
/*	if ( (d_nsbit16(&ccpu.deCodeBlock.immData_16Bit)  == 0x5052)) {
			FILE *fp = fopen("d:/temp2.log","w");
			fprintf(fp,"%x\n", (t_nubit8 *)ccpu.deCodeBlock.prm - (t_nubit8 *)p_nubit8(cramGetAddr(0,0)) );
			fclose(fp);
	}*/
	ins_atomMethod_CMP_16bit(d_nubit16(ccpu.deCodeBlock.prm), d_nsbit16(&ccpu.deCodeBlock.immData_16Bit));
}
void ins_methodGroup_CMP_Ev_Ib()
{
	//vapiCallBackMachineStop();;//may be some problem
	ins_atomMethod_CMP_16bit(d_nubit16(ccpu.deCodeBlock.prm),  (t_nsbit8)ccpu.deCodeBlock.immData_8Bit);
}
////////////////////////////////////////////</GROUP1>

////////////////////////////////////////////<GROUP2> :DONE
static void ins_methodGroup_SHL_Eb_1_atom()
{
	t_nubit8  oldEb  = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool old_sign = getSignByData_data8(oldEb);
	ccpu_setCF_Flag_flag(old_sign);
	(d_nubit8(ccpu.deCodeBlock.prm)) <<= 1;
	ccpu_setOF_Flag_flag(isSignBitChange_data8(oldEb, d_nubit8(ccpu.deCodeBlock.prm)));
	ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_SHL_Ev_1_atom()
{
	t_nubit16  oldEv  = d_nubit16(ccpu.deCodeBlock.prm);
	t_bool old_sign = getSignByData_data16( oldEv );
	ccpu_setCF_Flag_flag(old_sign);
	(d_nubit16(ccpu.deCodeBlock.prm)) <<= 1;
	ccpu_setOF_Flag_flag(isSignBitChange_data16(oldEv, d_nubit16(ccpu.deCodeBlock.prm)));
	ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_SHR_Eb_1_atom()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool finalBit = getFinalBit_data8(oldEb);
	d_nubit8(ccpu.deCodeBlock.prm) >>= 1;
	ccpu_setCF_Flag_flag(finalBit);
	ccpu_setOF_Flag_flag(isSignBitChange_data8(oldEb, d_nubit8(ccpu.deCodeBlock.prm)));
	ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_SHR_Ev_1_atom()
{
	t_nsbit16 oldEv = d_nsbit16(ccpu.deCodeBlock.prm);
	t_bool finalBit = getFinalBit_data16( oldEv );
	d_nubit16(ccpu.deCodeBlock.prm) >>= 1;
	ccpu_setCF_Flag_flag(finalBit);
	ccpu_setOF_Flag_flag(isSignBitChange_data16(oldEv, d_nubit16(ccpu.deCodeBlock.prm)));
	ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_ROL_Eb_1_atom()
{
	t_nubit8  oldEb  = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool old_sign = getSignByData_data8( oldEb );
	ccpu_setCF_Flag_flag(old_sign);
	(d_nubit8(ccpu.deCodeBlock.prm)) = ((d_nubit8(ccpu.deCodeBlock.prm))<<1) | ((d_nubit8(ccpu.deCodeBlock.prm))>>7) ;
	ccpu_setOF_Flag_flag(isSignBitChange_data8(oldEb, d_nubit8(ccpu.deCodeBlock.prm)));
}
static void ins_methodGroup_ROL_Ev_1_atom()
{
	t_nubit16  oldEv  = d_nubit16(ccpu.deCodeBlock.prm);
	t_bool old_sign = getSignByData_data16( oldEv );
	ccpu_setCF_Flag_flag(old_sign);
	(d_nubit16(ccpu.deCodeBlock.prm)) = ((d_nubit16(ccpu.deCodeBlock.prm))<<1) | ((d_nubit16(ccpu.deCodeBlock.prm))>>15) ;
	ccpu_setOF_Flag_flag(isSignBitChange_data16(oldEv, d_nubit16(ccpu.deCodeBlock.prm)));
}
static void ins_methodGroup_ROR_Eb_1_atom()
{
	t_nubit8  oldEb  = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool finalBit = getFinalBit_data8( oldEb );
	ccpu_setCF_Flag_flag( finalBit );
	(d_nubit8(ccpu.deCodeBlock.prm)) = ((d_nubit8(ccpu.deCodeBlock.prm))>>1) | ((d_nubit8(ccpu.deCodeBlock.prm))<<7) ;
	ccpu_setOF_Flag_flag(isSignBitChange_data8(oldEb, d_nubit8(ccpu.deCodeBlock.prm)));
	//ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_ROR_Ev_1_atom()
{
	t_nubit16  oldEv  = d_nubit16(ccpu.deCodeBlock.prm);
	t_bool finalBit = getFinalBit_data16( oldEv );
	ccpu_setCF_Flag_flag( finalBit );
	(d_nubit16(ccpu.deCodeBlock.prm)) = ((d_nubit16(ccpu.deCodeBlock.prm))>>1) | ((d_nubit16(ccpu.deCodeBlock.prm))<<15) ;
	ccpu_setOF_Flag_flag(isSignBitChange_data16(oldEv, d_nubit16(ccpu.deCodeBlock.prm)));
	//ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_RCL_Eb_1_atom()
{
	t_bool newCF, newOF;
	t_nubit16 tmpFlags = ccpu_generateFLAG();
	ins_methodGroup_SHL_Eb_1_atom();
	newCF = ccpu_getCF_Flag();
	newOF = ccpu_getOF_Flag();
	ccpu_setFLAG(tmpFlags);
	if(ccpu_getCF_Flag())
	{
		d_nubit8(ccpu.deCodeBlock.prm) |= MASK_00000001;
	}
	ccpu_setCF_Flag_flag(newCF);
	ccpu_setOF_Flag_flag(newOF);
	//ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_RCL_Ev_1_atom()
{
	t_bool newCF, newOF;
	t_nubit16 tmpFlags = ccpu_generateFLAG();
	ins_methodGroup_SHL_Ev_1_atom();
	newCF = ccpu_getCF_Flag();
	newOF = ccpu_getOF_Flag();
	ccpu_setFLAG(tmpFlags);
	if(ccpu_getCF_Flag())
	{
		d_nubit16(ccpu.deCodeBlock.prm) |= 1;
	}
	ccpu_setCF_Flag_flag(newCF);
	ccpu_setOF_Flag_flag(newOF);
	//ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_RCR_Eb_1_atom()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool newCF, oldCF = ccpu_getCF_Flag();
	t_nubit16 tmpFlags = ccpu_generateFLAG();
	ins_methodGroup_SHR_Eb_1_atom();
	newCF = ccpu_getCF_Flag();
	ccpu_setFLAG(tmpFlags);//��Ϊins_methodGroup_SHR_Eb_1������ı�Flagsֵ����ʵ����RCR�ǲ�Ӱ���Ǽ�λ�ġ���
	if(oldCF)
	{
		d_nubit8(ccpu.deCodeBlock.prm) |= MASK_10000000;
	}
	ccpu_setOF_Flag_flag(isSignBitChange_data8(oldEb, d_nubit8(ccpu.deCodeBlock.prm)));
	ccpu_setCF_Flag_flag(newCF);
	//ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
}
static void ins_methodGroup_RCR_Ev_1_atom()
{
	t_nubit16 oldEv = d_nubit16(ccpu.deCodeBlock.prm);
	t_nubit16 tmpFlags = ccpu_generateFLAG();
	t_bool newCF, oldCF = ccpu_getCF_Flag();
	ins_methodGroup_SHR_Ev_1_atom();
	newCF = ccpu_getCF_Flag();
	ccpu_setFLAG(tmpFlags);
	if(oldCF)
	{
		d_nubit16(ccpu.deCodeBlock.prm) |= 0x8000;
	}
	ccpu_setOF_Flag_flag(isSignBitChange_data16(oldEv, d_nubit16(ccpu.deCodeBlock.prm)));
	ccpu_setCF_Flag_flag(newCF);
	//ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
}

void ins_methodGroup_ROL_Eb_Ib(){}
void ins_methodGroup_ROL_Ev_Ib(){}
void ins_methodGroup_ROL_Eb_1()
{
	t_nubit8  oldEb  = d_nubit8(ccpu.deCodeBlock.prm);
	ins_methodGroup_ROL_Eb_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_ROL_Ev_1()
{
	t_nubit16  oldEv  = d_nubit16(ccpu.deCodeBlock.prm);
	ins_methodGroup_ROL_Ev_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}
void ins_methodGroup_ROL_Eb_CL()
{
	t_nubit8  oldEb  = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool oldOF = ccpu_getOF_Flag();
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		ins_methodGroup_ROL_Eb_1_atom();
		tmpCL--;
	}
	ccpu_setOF_Flag_flag(oldOF);
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
	//ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
}
void ins_methodGroup_ROL_Ev_CL()
{
	t_nubit16  oldEv  = d_nubit16(ccpu.deCodeBlock.prm);
	t_bool oldOF = ccpu_getOF_Flag();
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		ins_methodGroup_ROL_Ev_1_atom();
		tmpCL--;
	}
	ccpu_setOF_Flag_flag(oldOF);
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
	//ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
}

void ins_methodGroup_ROR_Eb_Ib(){}
void ins_methodGroup_ROR_Ev_Ib(){}
void ins_methodGroup_ROR_Eb_1()
{
	t_nubit8  oldEb  = d_nubit8(ccpu.deCodeBlock.prm);
	ins_methodGroup_ROR_Eb_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_ROR_Ev_1()
{
	t_nubit16  oldEv  = d_nubit16(ccpu.deCodeBlock.prm);
	ins_methodGroup_ROR_Ev_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}
void ins_methodGroup_ROR_Eb_CL()
{
	t_nubit8  oldEb  = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool oldOF = ccpu_getOF_Flag();
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		ins_methodGroup_ROR_Eb_1_atom();
		tmpCL--;
	}
	ccpu_setOF_Flag_flag(oldOF);
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_ROR_Ev_CL()
{
	t_nubit16  oldEv  = d_nubit16(ccpu.deCodeBlock.prm);
	t_bool oldOF = ccpu_getOF_Flag();
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		ins_methodGroup_ROR_Ev_1_atom();
		tmpCL--;
	}
	ccpu_setOF_Flag_flag(oldOF);
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}

void ins_methodGroup_RCL_Eb_Ib(){}
void ins_methodGroup_RCL_Ev_Ib(){}
void ins_methodGroup_RCL_Eb_1()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	ins_methodGroup_RCL_Eb_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_RCL_Ev_1()
{
	t_nubit16 oldEv = d_nubit16(ccpu.deCodeBlock.prm);
	ins_methodGroup_RCL_Ev_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}
void ins_methodGroup_RCL_Eb_CL()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool oldOF = ccpu_getOF_Flag();
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		ins_methodGroup_RCL_Eb_1_atom();
		tmpCL--;
	}
	if (ccpu.cl != 1) ccpu_setOF_Flag_flag(oldOF);
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_RCL_Ev_CL()
{
	t_nubit16 oldEv = d_nubit16(ccpu.deCodeBlock.prm);
	t_bool oldOF = ccpu_getOF_Flag();
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		ins_methodGroup_RCL_Ev_1_atom();
		tmpCL--;
	}
	if (ccpu.cl != 1) ccpu_setOF_Flag_flag(oldOF);
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}

void ins_methodGroup_RCR_Eb_Ib(){}
void ins_methodGroup_RCR_Ev_Ib(){}
void ins_methodGroup_RCR_Eb_1()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	ins_methodGroup_RCR_Eb_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_RCR_Ev_1()
{
	t_nubit16 oldEv = d_nubit16(ccpu.deCodeBlock.prm);
	ins_methodGroup_RCR_Ev_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}
void ins_methodGroup_RCR_Eb_CL()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool oldOF = ccpu_getOF_Flag();
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
// NEKO DEBUG
	while(tmpCL)
	{
		ins_methodGroup_RCR_Eb_1_atom();
		tmpCL--;
	}
// NEKO DEBUG
	if(1 != ccpu.cl) ccpu_setOF_Flag_flag(oldOF);
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_RCR_Ev_CL()
{
	t_nubit16 oldEv = d_nubit16(ccpu.deCodeBlock.prm);
	t_bool oldOF = ccpu_getOF_Flag();
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		ins_methodGroup_RCR_Ev_1_atom();
		tmpCL--;
	}
// NEKO DEBUG
	if(1 != ccpu.cl) ccpu_setOF_Flag_flag(oldOF);
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}

void ins_methodGroup_SHL_Eb_Ib(){}
void ins_methodGroup_SHL_Ev_Ib(){}
void ins_methodGroup_SHL_Eb_1()
{	
	t_nubit8  oldEb  = d_nubit8(ccpu.deCodeBlock.prm);
	ins_methodGroup_SHL_Eb_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_SHL_Ev_1()
{
	t_nubit16  oldEv  = d_nubit16(ccpu.deCodeBlock.prm);
	ins_methodGroup_SHL_Ev_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}
void ins_methodGroup_SHL_Eb_CL()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool sign = 0x00;
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		sign = getSignByData_data8( d_nubit8(ccpu.deCodeBlock.prm) );
		(d_nubit8(ccpu.deCodeBlock.prm)) <<= 1; //����ʵ�֣��Ժ��޸�
		tmpCL--;
	}
	ccpu_setCF_Flag_flag(sign);
	ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_SHL_Ev_CL()
{
	t_nsbit16 oldEv = d_nsbit16(ccpu.deCodeBlock.prm);
	t_bool sign = 0x00;
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		sign = getSignByData_data16( d_nubit16(ccpu.deCodeBlock.prm) );
		(d_nubit16(ccpu.deCodeBlock.prm)) <<= 1; //����ʵ�֣��Ժ��޸�
		tmpCL--;
	}
	ccpu_setCF_Flag_flag(sign);
	ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}

void ins_methodGroup_SHR_Eb_Ib(){}
void ins_methodGroup_SHR_Ev_Ib(){}
void ins_methodGroup_SHR_Eb_1()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	ins_methodGroup_SHR_Eb_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_SHR_Ev_1()
{
	t_nsbit16 oldEv = d_nsbit16(ccpu.deCodeBlock.prm);
	ins_methodGroup_SHR_Ev_1_atom();
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}
void ins_methodGroup_SHR_Eb_CL()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool finalBit = 0x00;
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		finalBit = getFinalBit_data8(d_nubit8(ccpu.deCodeBlock.prm));
		d_nubit8(ccpu.deCodeBlock.prm) >>= 1;
		tmpCL--;
	}
	ccpu_setCF_Flag_flag(finalBit);
// NEKO DEBUG: ADD THE NEXT LINE
	if (ccpu.cl == 1) ccpu_setOF_Flag_flag(isSignBitChange_data8(oldEb, d_nubit8(ccpu.deCodeBlock.prm)));
	ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_SHR_Ev_CL()
{
	t_nsbit16 oldEv = d_nsbit16(ccpu.deCodeBlock.prm);
	t_bool finalBit = 0x00;
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		finalBit = getFinalBit_data16(d_nubit16(ccpu.deCodeBlock.prm));
		d_nubit16(ccpu.deCodeBlock.prm) >>= 1;
		tmpCL--;
	}
	ccpu_setCF_Flag_flag(finalBit);
// NEKO DEBUG: ADD THE NEXT LINE
	if (ccpu.cl == 1) ccpu_setOF_Flag_flag(isSignBitChange_data16(oldEv, d_nubit16(ccpu.deCodeBlock.prm)));
	ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}

void ins_methodGroup_SAR_Eb_Ib(){}
void ins_methodGroup_SAR_Ev_Ib(){}
void ins_methodGroup_SAR_Eb_1()
{
	t_nsbit8 oldEb = d_nsbit8(ccpu.deCodeBlock.prm);
	t_bool finalBit = getFinalBit_data8( (t_nubit8)oldEb );
	d_nsbit8(ccpu.deCodeBlock.prm) >>= 1;
	ccpu_setCF_Flag_flag(finalBit);
	ccpu_setOF_Flag_flag(0x00);//�������ƣ����ӷ���λ�ı�
	ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_SAR_Ev_1()
{
	t_nsbit16 oldEv = d_nsbit16(ccpu.deCodeBlock.prm);
	t_bool finalBit = getFinalBit_data8( (t_nubit8)oldEv );
	d_nsbit16(ccpu.deCodeBlock.prm) >>= 1;
	ccpu_setCF_Flag_flag(finalBit);
	ccpu_setOF_Flag_flag(0x00);
	ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}
void ins_methodGroup_SAR_Eb_CL()
{
	t_nubit8 oldEb = d_nubit8(ccpu.deCodeBlock.prm);
	t_bool finalBit = 0x00;
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		finalBit = getFinalBit_data8(d_nubit8(ccpu.deCodeBlock.prm));
		d_nsbit8(ccpu.deCodeBlock.prm) >>= 1;
		tmpCL--;
	}
	ccpu_setCF_Flag_flag(finalBit);
	ccpu_setOF_Flag_flag(0x00);
	ccpu_setSF_ZF_PF_byResult_data8(d_nubit8(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit8(ccpu.deCodeBlock.prm) = oldEb;
#endif
}
void ins_methodGroup_SAR_Ev_CL()
{
	t_nubit16 oldEv = d_nubit16(ccpu.deCodeBlock.prm);
	t_bool finalBit = 0x00;
	t_nubit8 tmpCL = ccpu.cl;
	if(0 == ccpu.cl)
		return;
	while(tmpCL)
	{
		finalBit = getFinalBit_data16(d_nubit16(ccpu.deCodeBlock.prm));
		d_nsbit16(ccpu.deCodeBlock.prm) >>= 1;
		tmpCL--;
	}
	ccpu_setCF_Flag_flag(finalBit);
	ccpu_setOF_Flag_flag(0x00);
	ccpu_setSF_ZF_PF_byResult_data16(d_nubit16(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) d_nubit16(ccpu.deCodeBlock.prm) = oldEv;
#endif
}
///////////////////////////////////////</Group2>

////////////////////////////////////<Group3> :DONE
void ins_methodGroup_TEST_Ib()
{
	ins_atomMethod_TEST_8bit(p_nubit8(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_8Bit);
}
void ins_methodGroup_TEST_Iv()
{
	ins_atomMethod_TEST_16bit(p_nubit16(ccpu.deCodeBlock.prm), ccpu.deCodeBlock.immData_16Bit);
}
void ins_methodGroup_NOT_8bit()
{
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) return;
#endif
	d_nubit8(ccpu.deCodeBlock.prm) = ~d_nubit8(ccpu.deCodeBlock.prm);
}
void ins_methodGroup_NOT_16bit()
{
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) return;
#endif
	d_nubit16(ccpu.deCodeBlock.prm) = ~d_nubit16(ccpu.deCodeBlock.prm);
}
void ins_methodGroup_NEG_8bit()
{
	t_nubit8 zero = 0;
	ins_atomMethod_SUB_8bit(&zero, d_nubit8(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) return;
#endif
	d_nubit8(ccpu.deCodeBlock.prm) = zero;
}
void ins_methodGroup_NEG_16bit()
{
	t_nubit16 zero = 0;
	ins_atomMethod_SUB_16bit(&zero, d_nubit16(ccpu.deCodeBlock.prm));
#if CCPU_RAM == VRAM
	if (im(ccpu.deCodeBlock.prm)) return;
#endif
	d_nubit16(ccpu.deCodeBlock.prm) = zero;
}
void ins_methodGroup_MUL_AL()
{
	ccpu.ax = d_nubit8(ccpu.deCodeBlock.prm) * ccpu.al;
	ccpu_setCF_Flag_flag(!!(ccpu.ah));
	ccpu_setOF_Flag_flag(!!(ccpu.ah));
}
void ins_methodGroup_MUL_eAX()
{
	t_nubit32 result = d_nubit16(ccpu.deCodeBlock.prm) * ccpu.ax;
	ccpu.dx = (t_nubit16)(result >> 16);
	ccpu.ax = (t_nubit16)(result & 0x0000ffff);

	ccpu_setCF_Flag_flag(!!(ccpu.dx));
	ccpu_setOF_Flag_flag(!!(ccpu.dx));
}
void ins_methodGroup_IMUL_AL()
{
	ccpu.ax = d_nsbit8(ccpu.deCodeBlock.prm) * (t_nsbit8)(ccpu.al);
	if(ccpu.ax == ccpu.al)
	{
		ccpu_setCF_Flag_flag(0x00);
		ccpu_setOF_Flag_flag(0x00);
	}
	else
	{
		ccpu_setCF_Flag_flag(0x01);
		ccpu_setOF_Flag_flag(0x01);
	}
}
void ins_methodGroup_IMUL_eAX()
{
	t_nsbit32 result = d_nsbit16(ccpu.deCodeBlock.prm) * (t_nsbit16)(ccpu.ax);
	ccpu.dx = (t_nubit16)(result >> 16);
	ccpu.ax = (t_nubit16)(result & 0x0000ffff);
	if(result == (t_nsbit32)(ccpu.ax))
	{
		ccpu_setCF_Flag_flag(0x00);
		ccpu_setOF_Flag_flag(0x00);
	}
	else
	{
		ccpu_setCF_Flag_flag(0x01);
		ccpu_setOF_Flag_flag(0x01);
	}
}
void ins_methodGroup_DIV_AL()
{
	t_nubit16 tmpAX_unsigned;
	if(0 == (d_nubit8(ccpu.deCodeBlock.prm)) )
	{//����������㣬��������ж�
		ins_atomMethod_INT(0);
		return ;
	}
	tmpAX_unsigned = ccpu.ax;
	ccpu.al = tmpAX_unsigned / (d_nubit8(ccpu.deCodeBlock.prm)); //��
	ccpu.ah = tmpAX_unsigned % (d_nubit8(ccpu.deCodeBlock.prm));//����
}
void ins_methodGroup_DIV_eAX()
{
	t_nubit32 data;
	if(0 == (d_nubit16(ccpu.deCodeBlock.prm)) )
	{//����������㣬��������ж�
		ins_atomMethod_INT(0);
		return;
	}
	data = (((t_nubit32)(ccpu.dx))<<16) + ccpu.ax;
	ccpu.ax = data / (d_nubit16(ccpu.deCodeBlock.prm)); //��
	ccpu.dx = data % (d_nubit16(ccpu.deCodeBlock.prm));//����

}
void ins_methodGroup_IDIV_AL()
{
	t_nsbit16 tmpAX_signed;
	if(0 == (d_nsbit8(ccpu.deCodeBlock.prm)) )
	{//����������㣬��������ж�
		ins_atomMethod_INT(0);
		return ;
	}
	tmpAX_signed = ccpu.ax;
	ccpu.al = tmpAX_signed / (d_nsbit8(ccpu.deCodeBlock.prm)); //��
	ccpu.ah = tmpAX_signed % (d_nsbit8(ccpu.deCodeBlock.prm));//����
}
void ins_methodGroup_IDIV_eAX()
{
	t_nsbit32 data;
	if(0 == (d_nsbit16(ccpu.deCodeBlock.prm)) )
	{//����������㣬��������ж�
		ins_atomMethod_INT(0);
		return ;
	}

	data = (((t_nubit32)(ccpu.dx))<<16) + ccpu.ax;
	ccpu.ax = data / (d_nsbit16(ccpu.deCodeBlock.prm)); //��
	ccpu.dx = data % (d_nsbit16(ccpu.deCodeBlock.prm));//����
}
//////////////////////////////////////</Group3>

//////////////////////////////////////////<Group4--5> :DONE
void ins_methodGroup_INC_Eb()
{
	ins_atomMethod_INC_8bit(p_nubit8(ccpu.deCodeBlock.prm));
}
void ins_methodGroup_INC_Ev()
{
	ins_atomMethod_INC_16bit(p_nubit16(ccpu.deCodeBlock.prm));
}
void ins_methodGroup_DEC_Eb()
{
	ins_atomMethod_DEC_8bit(p_nubit8(ccpu.deCodeBlock.prm));
}
void ins_methodGroup_DEC_Ev()
{
	ins_atomMethod_DEC_16bit(p_nubit16(ccpu.deCodeBlock.prm));
}
void ins_methodGroup_CALL_Ev()//nnn=010 ���ڼ�ӵ���
{
	ins_atomMethod_PUSH(ccpu.ip); // û��PUSH IP �������������������
	ccpu.ip = d_nubit16(ccpu.deCodeBlock.prm);//near call absolute
}
void ins_methodGroup_CALL_Ep()//nnn=011 �μ��ӵ���
{
	ins_atomMethod_PUSH(ccpu.cs);
	ins_atomMethod_PUSH(ccpu.ip); // û��PUSH IP �������������������
	ccpu.cs = *(((t_nubit16*)ccpu.deCodeBlock.prm) + 1);
	ccpu.ip = d_nubit16(ccpu.deCodeBlock.prm);
}
void ins_methodGroup_JMP_Ev()//���ڼ��ת��
{
	ccpu.ip = d_nubit16(ccpu.deCodeBlock.prm);
}
void ins_methodGroup_JMP_Ep()//�μ���ת��
{
	ccpu.cs = *(((t_nubit16*)ccpu.deCodeBlock.prm) + 1);
	ccpu.ip = d_nubit16(ccpu.deCodeBlock.prm);

}
void ins_methodGroup_PUSH_Ev()
{
	ins_atomMethod_PUSH(d_nubit16(ccpu.deCodeBlock.prm));
}
//////////////////////////////////////////</Group4--5>