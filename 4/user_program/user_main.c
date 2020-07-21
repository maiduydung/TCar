 #include <tm/tmonitor.h>
#include <tk/tkernel.h>

void bz_task(INT stacd, void *exinf){
        tm_printf("Start Bz-Task\n");
        tk_ext_tsk();
}

void led_task(INT stacd, void *exinf){
        tm_printf("Start Led-Task\n");
        tk_ext_tsk();
}

void third_task(INT stacd, void *exinf){
        tm_printf("Start third-Task\n");
        tk_ext_tsk();
}


EXPORT INT usermain( void )
{

        //buzzer
        T_CTSK bz_ctsk;
        ID     bz_tskid;

        T_CTSK led_ctsk;
        ID     led_tskid;

        T_CTSK third_ctsk;
        ID     third_tskid;

        bz_ctsk.tskatr = TA_HLNG | TA_RNG0;
        bz_ctsk.task   = bz_task;
        bz_ctsk.itskpri = 10;
        bz_ctsk.stksz = 1024;

        led_ctsk.tskatr = TA_HLNG | TA_RNG0;
        led_ctsk.task   = led_task;
        led_ctsk.itskpri = 10;
        led_ctsk.stksz = 1024;

        
        third_ctsk.tskatr = TA_HLNG | TA_RNG0;
        third_ctsk.task   = third_task;
        third_ctsk.itskpri = 10;
        third_ctsk.stksz = 1024;


        bz_tskid = tk_cre_tsk(&bz_ctsk);
        tk_sta_tsk(bz_tskid, 0);

        led_tskid = tk_cre_tsk(&led_ctsk);
        tk_sta_tsk(led_tskid, 0);

        third_tskid = tk_cre_tsk(&third_ctsk);
        tk_sta_tsk(third_tskid, 0);

        tk_slp_tsk(TMO_FEVR);


        ////////////////
	return 0;
}