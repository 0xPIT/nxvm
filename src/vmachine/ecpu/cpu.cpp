//////////////////////////////////////////////////////////////////////////
// ����	��CPU.cpp
// ����	��ģ��CPU
// ����	��2008��4��20��
// ����	����һ��
//////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "memory.h"

#include "../vpic.h"
#include "../vcpu.h"
#include "cpu.h"
#include "Instruction.h"

#define eIMS (evIP+MemoryStart)
#define EvSP (t=eCPU.ss,(t<<4)+eCPU.sp)

t_cpu eCPU;					//�������CPU��ʵ��
unsigned int evIP;			//evIP��ָ��ʱ��ָ��
unsigned int GlobINT;		//���з�INTָ��������ж�
t_bool bStartRecord=0x00;			//��ĳ��λ�ÿ�ʼ���������״̬
unsigned int InstructionCount=0;

void IO_NOP()		//δʵ�ֵ�IO��
{
	__asm mov eax,0xcccccccc				//Debug�汾������һ�䣬��ʹ��������cc������Release�汾��û���ˡ�
											//�˿ڷ���CC�պø�ʹĳЩ����������У�������������ȷ������Ӧ����ʵ���Ǹ��˿ڡ�����3DAh�˿�
	__asm nop
}

int CPUInit()
{
	memset(&eCPU,0,sizeof(t_cpu));
	SetupInstructionTable();
	eCPU.cs=0xf000;
	eCPU.ip=0xfff0;
	evIP=eCPU.cs;
	evIP<<=4;
	evIP+=eCPU.ip;
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// ִ��evIP��ָ�����һ��ָ��
int ExecIns()
{
	unsigned char OpC=*(unsigned char *)(evIP+MemoryStart);
	unsigned int InsFucAddr=InsTable[OpC];
	unsigned int tcs=eCPU.cs;
	evIP++;	
	InstructionCount++;
	__asm call InsFucAddr;
	eCPU.ip=(evIP - (tcs << 4)) % 0x10000;
	tmpDs=eCPU.ds;
	tmpSs=eCPU.ss;
	return 0;
}


//////////////////////////////////////////////////////////////////////////
// ǰ��ĳ���жϷ������
void GoInt(int r)
{
	//LongCallNewIP(1);					//��ΪExcIns��������ִ��ָ�����޸�CS:IP�ģ��������е������CS:IP��δ��ִ�еģ����Բ�����LongCallNewIP�ˡ�
	unsigned int t;	
	eCPU.sp-=2;
	*(unsigned short*)( EvSP +MemoryStart)=eCPU.flags;
	eCPU.flags&=~IF;
	eCPU.flags&=~TF;
	eCPU.flags&=~AF;
	eCPU.sp-=2;
	*(unsigned short*)( EvSP +MemoryStart)=eCPU.cs;				//��ѹCS����ѹIP��������ҪѹCALLָ��֮���IP
	eCPU.sp-=2;
	*(unsigned short*)( EvSP +MemoryStart)=eCPU.ip;
	eCPU.ip=*(unsigned short *)((r)*4+MemoryStart);
	eCPU.cs=*(unsigned short *)((r)*4+2+MemoryStart);
	evIP=((t=eCPU.cs,t<<4))+eCPU.ip;
}


//////////////////////////////////////////////////////////////////////////
// ����Ƿ����ж����󣬲���������Ӧ����
int ExecInt()
{	
	char intR;
	unsigned int tmpGlobINT;
	unsigned int IntNo;
	if (eCPU.flags&TF)
	{
		GlobINT|=0x2;
		eCPU.flags&=~TF;
	}
	tmpGlobINT=GlobINT;
	IntNo=0;

	while (!(tmpGlobINT&1) && IntNo<8)		//��������7���жϣ��������ӵ�8259�ϵ��жϣ�
	{
		IntNo++;
	}

	if (IntNo==2)
	{
		GoInt(2);							//���������ж�
		GlobINT&=~0x2;
		return IntNo;
	}

	if (eCPU.flags&IF)
	{	
		if (IntNo<8)
		{
			GoInt(IntNo);
			GlobINT&=~(unsigned int)(1<<IntNo);
			return IntNo;
		}
		if (!vpicScanINTR()) return -1;

		intR=vpicGetINTR();
		GoInt(intR+8);						//PIC��IR0���жϺ�8
		return intR+8;
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////
// easyVM�ػ�ʱ������
void CPUTerminate() {}