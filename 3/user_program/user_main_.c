/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.00.00
 *
 *    Copyright (C) 2006-2019 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2019/12/11.
 *
 *----------------------------------------------------------------------
 */

#include <tk/tkernel.h>
#include <tm/tmonitor.h>


LOCAL	ID	tskid1, tskid2;
LOCAL	ID	flgid;

/* ----------------------------------------------------------
 *
 * User Task-1 Definition
 *
 */
void tsk1(INT stacd, void *exinf)
{
	tm_putstring("Start Task-1\n");
	tk_slp_tsk(TMO_FEVR);
	tm_putstring("Wake-up Task-1\n");
	tk_set_flg(flgid, 0x01);

	tk_exd_tsk();	/* Exit task */
}

const T_CTSK	ctsk1	= {
	0, (TA_HLNG | TA_RNG1), &tsk1, 10, 1024, 0
};

/* ---------------------------------------------------------
 *
 * User Task-2 Definition
 *
 */
void tsk2(INT stacd, void *exinf)
{
	UINT	flgptn;

	tm_putstring("Start Task-2\n");
	tk_wup_tsk(tskid1);
	tk_wai_flg(flgid, 0x01, TWF_ANDW | TWF_CLR, &flgptn, TMO_FEVR);
	tm_putstring("Wake-up Task-2\n");

	tk_exd_tsk();	/* Exit Task */
}

const T_CTSK	ctsk2	= {
	0, (TA_HLNG | TA_RNG1), &tsk2, 11, 1024, 0
};


/* ----------------------------------------------------------
 *
 * User-Main Definition (Run on initial task)
 *
 */
EXPORT INT usermain( void )
{
	T_RVER	rver;
	T_CFLG	cflg = {
		.flgatr = TA_TFIFO | TA_WMUL,
		.iflgptn = 0
	};


	tm_putstring("Start User-main program.\n");
#if USE_QEMU
	tm_putstring("QEMU option enable.\n");
#endif

	tk_ref_ver(&rver);		/* Get the OS Version. */

	tm_printf("Make Code: %04x  Product ID: %04x\n", rver.maker, rver.prid);
	tm_printf("Product Ver. %04x\nProduct Num. %04x %04x %04x %04x\n", 
			rver.prver, rver.prno[0],rver.prno[1],rver.prno[2],rver.prno[3]);

	flgid = tk_cre_flg(&cflg);

	tskid1 = tk_cre_tsk(&ctsk1);
	tk_sta_tsk(tskid1, 0);

	tskid2 = tk_cre_tsk(&ctsk2);
	tk_sta_tsk(tskid2, 0);

	tk_slp_tsk(TMO_FEVR);
}
