#include <tm/tmonitor.h>
#include <tk/tkernel.h>

ID mtxid;
ID     msg_1tskid;
ID     msg_2tskid;
ID     msg_3tskid;


void msg_1(INT stacd, void *exinf){
  while(1)
  {
    tk_loc_mtx(mtxid, TMO_FEVR);
    T_RTSK rtsk;
    tk_ref_tsk(msg_1tskid, &rtsk);
    tm_printf("msg_1 priority after lock: %d\n", rtsk.tskpri);
    tm_printf("msg_1\n");
    tk_ref_tsk(msg_1tskid, &rtsk);
    tm_printf("msg_1 priority before lock: %d\n", rtsk.tskpri);
    tk_unl_mtx(mtxid);
  }
  tk_ext_tsk();
    
}


void msg_2(INT stacd, void *exinf){
  while(1)
  {
    tk_loc_mtx(mtxid, TMO_FEVR);
    T_RTSK rtsk;
    tk_ref_tsk(msg_1tskid, &rtsk);
    tm_printf("msg_2 priority after lock: %d\n", rtsk.tskpri);
    tm_printf("msg_2\n");
    tk_ref_tsk(msg_2tskid, &rtsk);
    tm_printf("msg_2 priority before lock: %d\n", rtsk.tskpri);
    tk_unl_mtx(mtxid);
  }
  tk_ext_tsk();

}

void msg_3(INT stacd, void *exinf){
  while(1)
  {
    tk_loc_mtx(mtxid, TMO_FEVR);
    T_RTSK rtsk;
    tk_ref_tsk(msg_3tskid, &rtsk);
    tm_printf("msg_3 priority after lock: %d\n", rtsk.tskpri);
    tm_printf("msg_3\n");
    tk_ref_tsk(msg_1tskid, &rtsk);
    tm_printf("msg_3 priority before lock: %d\n", rtsk.tskpri);
    tk_unl_mtx(mtxid);
  }
  tk_ext_tsk();

}



EXPORT INT usermain( void )
{
        T_CMTX mtx;
        mtx.mtxatr = TA_TFIFO | TA_CEILING;
        mtx.ceilpri = 8;
        mtxid = tk_cre_mtx(&mtx);


        T_CTSK msg_3tsk;


        T_CTSK msg_2tsk;


        T_CTSK msg_1tsk;


        msg_3tsk.tskatr = TA_HLNG | TA_RNG3;
        msg_3tsk.task   = msg_3;
        msg_3tsk.itskpri = 10;
        msg_3tsk.stksz = 1024;

        msg_2tsk.tskatr = TA_HLNG | TA_RNG3;
        msg_2tsk.task   = msg_2;
        msg_2tsk.itskpri = 10;
        msg_2tsk.stksz = 1024;

        msg_1tsk.tskatr = TA_HLNG | TA_RNG3;
        msg_1tsk.task   = msg_1;
        msg_1tsk.itskpri = 10;
        msg_1tsk.stksz = 1024;

        msg_1tskid = tk_cre_tsk(&msg_1tsk);
        msg_2tskid = tk_cre_tsk(&msg_2tsk);
        msg_3tskid = tk_cre_tsk(&msg_3tsk);

        
        
        tk_sta_tsk(msg_1tskid, 0);
        tk_sta_tsk(msg_2tskid, 0);
        tk_sta_tsk(msg_3tskid, 0);
        
        tk_slp_tsk(TMO_FEVR);


        ////////////////
	return 0;
}
