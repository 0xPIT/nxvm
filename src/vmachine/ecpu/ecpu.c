//////////////////////////////////////////////////////////////////////////
// ����	��CPU.cpp
// ����	��ģ��CPU
// ����	��2008��4��20��
// ����	����һ��
//////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "memory.h"

#include "../vapi.h"
#include "../vpic.h"
#include "../vcpu.h"
#include "ecpu.h"
#include "ecpuins.h"

#define eIMS (evIP+MemoryStart)
#define EvSP (t=ecpu.ss,(t<<4)+ecpu.sp)

t_ecpu ecpu;

void ecpuInit()
{
	memset(&ecpu,0,sizeof(t_ecpu));
	ecpu.cs=0xf000;
	ecpu.ip=0xfff0;
	evIP = (ecpu.cs << 4) + ecpu.ip;
	ecpuinsInit();
}

void ecpuRefresh()
{
	ecpuinsExecIns();
	ecpuinsExecInt();
}

void ecpuFinal() {ecpuinsFinal();}