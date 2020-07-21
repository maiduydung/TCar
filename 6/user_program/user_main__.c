/*
 *		usermian.c
 *		User Main
 */
#include <tk/tkernel.h>
#include <tm/tmonitor.h>

LOCAL   ID    id1, id2;
LOCAL	ID	flgid;

/* ----------------------------------------------------------
 *
 * User Task-1 Definition
 *
 */
void tsk1(INT stacd, void *exinf)
{
	while(1) {
		tm_putstring("SW-3\n");
		tk_set_flg(flgid, (1<<0));
		tm_putstring("SW-4\n");
		tk_set_flg(flgid, (1<<1));
	}
	tk_exd_tsk();	/* Exit task */
}

const T_CTSK	ctsk1	= {
	0, (TA_HLNG | TA_RNG1), &tsk1, 11, 1024, 0
};

/* ---------------------------------------------------------
 *
 * User Task-2 Definition
 *
 */
void tsk2(INT stacd, void *exinf)
{
	UINT	flg;

	while(1) {
		tk_wai_flg(flgid, (1<<0)|(1<<1),(TWF_ORW | TWF_BITCLR), &flg, TMO_FEVR);
		if(flg & (1<<0)) {
			tm_printf("LED-L\n");
		} else {	
			tm_printf("LED-R\n");
		}
	}

	tk_exd_tsk();	/* Exit Task */
}

const T_CTSK	ctsk2	= {
	0, (TA_HLNG | TA_RNG1), &tsk2, 10, 1024, 0
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

	flgid = tk_cre_flg(&cflg);

	id1 = tk_cre_tsk(&ctsk1);
	tk_sta_tsk(id1, 0);

	id2 = tk_cre_tsk(&ctsk2);
	tk_sta_tsk(id2, 0);

	tk_slp_tsk(TMO_FEVR);
}
