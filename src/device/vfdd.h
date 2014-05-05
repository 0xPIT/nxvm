/* Copyright 2012-2014 Neko. */

#ifndef NXVM_VFDD_H
#define NXVM_VFDD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vglobal.h"

#define NXVM_DEVICE_FDD "3.5\" Floppy Disk Drive"

typedef struct {
    t_nubit16 cyl;     /* vfdc.C; cylinder id (0 to 79) */
    t_nubit16 head;    /* vfdc.H; head id (0 or 1) */
    t_nubit16 sector;  /* vfdc.R; sector id (1 to 18) */

    t_nubit16 ncyl;    /* number of cylinders */
    t_nubit16 nhead;   /* number of heads */
    t_nubit16 nsector; /* vfdc.EOT; end sector id (default is 18) */
    t_nubit16 nbyte;   /* vfdc.N; bytes per sector (default is 512) */

    t_nubit8  gpl;     /* vfdc.GPL; gap length of sector (default is 3) */

    t_bool flagReadOnly;  /* write protect status */
    t_bool flagDiskExist; /* flag of floppy disk existance */

    t_vaddrcc pImgBase;   /* pointer to disk in ram */
    t_vaddrcc pCurrByte;  /* pointer to current byte */
    t_nubit16 transCount; /* number of transfer bytes */
} t_fdd;

extern t_fdd vfdd;

#define VFDD_BYTE_PER_MB ((1 << 10) * 1000)

#define vfddSetPointer (vfdd.pCurrByte = vfdd.pImgBase + \
    ((vfdd.cyl * vfdd.nhead + vfdd.head) * vfdd.nsector + \
    (vfdd.sector - 1)) * vfdd.nbyte)
#define vfddGetImageSize (vfdd.nbyte * vfdd.nsector * vfdd.nhead * vfdd.ncyl)

void vfddTransRead();
void vfddTransWrite();
void vfddFormatTrack(t_nubit8 fillByte);

void vfddRegister();

#ifdef __cplusplus
}/*_EOCD_*/
#endif

#endif
