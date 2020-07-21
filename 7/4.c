 #include <tm/tmonitor.h>

ID mbfid;
ID mplid;

void led_task_send(INT stacd, void *exinf) {
  T_RMPL rmpl;
  void *blk;
  while(1) {
      tk_get_mpl(mplid, 100, &blk, TMO_FEVR);

      tk_snd_mbf(mbfid, &blk, sizeof(blk), TMO_FEVR);
      tk_ref_mpl(mplid, &rmpl);
      tm_printf("free memory at transmission time\n");
      tm_printf("maxsz: %d\n", rmpl.maxsz);
      tm_printf("frsz: %d\n", rmpl.frsz);
      for (UINT j=0; j<1000000; j++);
      tk_rot_rdq(TPRI_RUN);
    }
}

void led_task_recv(INT stacd, void *exinf) {
  T_RMPL rmpl;
  void *blk;
  while(1) {
    INT sz = tk_rcv_mbf(mbfid, &blk, TMO_FEVR);

    tk_ref_mpl(mplid, &rmpl);
    tm_printf("free memory at reception time\n");
    tm_printf("maxsz: %d\n", rmpl.maxsz);
    tm_printf("frsz: %d\n", rmpl.frsz);
    for (UINT j=0; j<1000000; j++);

    tk_rot_rdq(TPRI_RUN);
  }
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
  cmbf.bufsz = 1024 * 10;
  cmbf.maxmsz = 1024;

  mbfid = tk_cre_mbf(&cmbf);
  
  T_CMPL cmpl;
  cmpl.mplatr = TA_TFIFO | TA_RNG3;
  cmpl.mplsz = 1024;
  mplid = tk_cre_mpl(&cmpl);

  ID led_tskid_send = create_task(10, &led_task_send);
  ID led_tskid_recv = create_task(10, &led_task_recv);

  ER led_error_send = tk_sta_tsk(led_tskid_send, 0);
  ER led_error_recv = tk_sta_tsk(led_tskid_recv, 0);

  tk_slp_tsk(TMO_FEVR);
  return 0;
}



