  #include <tm/tmonitor.h>
#include <tk/tkernel.h>

T_CFLG flg;
ID     sw_flgid;


        


void led_task(INT stacd, void *exinf){
        UINT flg;
        while(1) 
        {
          tk_wai_flg(sw_flgid, (1<<0)|(1<<1), (TWF_ORW | TWF_BITCLR), &flg, TMO_FEVR);
          if(flg & (1<<0))
            tm_printf("LED3-ON\n");
        }
        tk_ext_tsk();
}


void led_task2(INT stacd, void *exinf){
        UINT flg;
        while(1) 
        {
          tk_wai_flg(sw_flgid, (1<<0)|(1<<1), (TWF_ORW | TWF_BITCLR), &flg, TMO_FEVR);
          if(flg & (1<<1))
            tm_printf("LED4-ON\n");
        }
        tk_ext_tsk();
}


void sw_task(INT stacd, void *exinf){
        while(1)
        {   
          tm_printf("SW3-ON\n");
          tk_set_flg(sw_flgid, (1<<0));
          for (UINT i=0; i<300000; i++);

          tm_printf("SW4-ON\n");
          tk_set_flg(sw_flgid, (1<<1));
          for (UINT j=0; j<300000; j++);
        }
        tk_ext_tsk();
}



EXPORT INT usermain( void )
{
        flg.flgatr   = TA_WMUL | TA_TFIFO;
        flg.iflgptn  = 0;
        sw_flgid = tk_cre_flg( &flg );

        T_CTSK sw_ctsk;
        ID     sw_tskid;

        T_CTSK led_ctsk;
        ID     led_tskid;

        T_CTSK led_ctsk2;
        ID     led_tskid2;

        sw_ctsk.tskatr = TA_HLNG | TA_RNG0;
        sw_ctsk.task   = sw_task;
        sw_ctsk.itskpri = 10;
        sw_ctsk.stksz = 1024;

        led_ctsk.tskatr = TA_HLNG | TA_RNG0;
        led_ctsk.task   = led_task;
        led_ctsk.itskpri = 9;
        led_ctsk.stksz = 1024;

        led_ctsk2.tskatr = TA_HLNG | TA_RNG0;
        led_ctsk2.task   = led_task2;
        led_ctsk2.itskpri = 9;
        led_ctsk2.stksz = 1024;

        led_tskid2 = tk_cre_tsk(&led_ctsk2);
        led_tskid = tk_cre_tsk(&led_ctsk);
        sw_tskid = tk_cre_tsk(&sw_ctsk);

        tk_sta_tsk(sw_tskid, 0);
        tk_sta_tsk(led_tskid, 0);
        tk_sta_tsk(led_tskid2, 0);
        

        tk_slp_tsk(TMO_FEVR);


        ////////////////
	return 0;
}
