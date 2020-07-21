 #include <tm/tmonitor.h>

ID mbfid;

void led_task_send(INT stacd, void *exinf) {
  INT msg;
  while(1) {
    INT sw3 = 0;
    if (sw3 == 0) {
      msg = 3;
      tk_snd_mbf(mbfid, &msg, sizeof(msg), TMO_FEVR);
    }
    INT sw4 = 0;
    if (sw4 == 0) {
      msg = 4;
      tk_snd_mbf(mbfid, &msg, sizeof(msg), TMO_FEVR);
    }
    tk_rot_rdq(TPRI_RUN);
  }
  tk_ext_tsk();
}

void led_task_recv(INT stacd, void *exinf) {
  while(1) {
    INT msg;
    INT msgsz = tk_rcv_mbf(mbfid, &msg, TMO_FEVR);

    if (msg == 3) {
      tm_printf("Left LED ON\n");
      for (UINT j=0; j<500000; j++);
    } else if (msg == 4) {
      tm_printf("Right LED ON\n");
      for (UINT j=0; j<500000; j++);
    }
  tk_rot_rdq(TPRI_RUN);
  }
  tk_ext_tsk();
}

ID create_task(INT itskpri, void(*ftask)(INT, void *))
{
  T_CTSK ctsk;
  ID tskid;
  ctsk.tskatr = TA_HLNG | TA_RNG3;
  ctsk.task = ftask;
  ctsk.itskpri = itskpri;
  ctsk.stksz = 1024;
  tskid = tk_cre_tsk(&ctsk);
  return tskid;
}
EXPORT INT usermain( void )
{  
  T_CMBF cmbf;
  cmbf.mbfatr = TA_TFIFO;
  cmbf.bufsz = sizeof(INT) * 10;
  cmbf.maxmsz = sizeof(INT);

  mbfid = tk_cre_mbf(&cmbf);

  ID led_tskid_send = create_task(10, &led_task_send);
  ID led_tskid_recv = create_task(10, &led_task_recv);

  ER led_error_send = tk_sta_tsk(led_tskid_send, 0);
  ER led_error_recv = tk_sta_tsk(led_tskid_recv, 0);

  tk_slp_tsk(TMO_FEVR);
  return 0;
}



