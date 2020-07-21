#include <tk/tkernel.h>
#include <tm/tmonitor.h>

INT test_pattern(UW data) {
  UW ref_data[] = {0x100, 0x80, 0x100, 0x80, 0x1c0, 0x040};
  static int i=0;
  tm_printf("    ref: "); print_bits(ref_data[i]);

  if (data == ref_data[i++]) {
    return 0;
  } else {
    return E_PAR;
  }  
}

void print_bits(UW data) {
  for (INT i=sizeof(data)*8-1; i>=0; i--) {
    tm_printf("%d", ((data & (1<<i)) >> i));
  }
  tm_printf("\n");
}

INT clear_bit8_7(UW* data) {
  //// ***** Write your code here
  *data &= ~(0x01 << 8);
  *data &= ~(0x01 << 7);
  return 0;
}

INT set_bit8_6(W* data) {
  //// ***** Write your code here
  *data |= (0x01<<8);
  *data |= (0x01<<6);
  return 0;
}

INT toggle_bit8_7(UW* data) {
  //// ***** Write your code here
  *data ^= (0x01<<8);
  *data ^= (0x01<<7);
  return 0;
}

EXPORT INT usermain( void )
{
  UW data = 0x80;
  tm_printf("initial: "); print_bits(data);

  INT (*actions[6] )(UW*) = {
    toggle_bit8_7, toggle_bit8_7, toggle_bit8_7, toggle_bit8_7,
    set_bit8_6, clear_bit8_7
  };

  for( INT i=0; i<sizeof(actions)/sizeof(actions[0]); i++ ) {
    /* Call the i-th of the function pointer actions with data as an argument */
    (*actions[i])(&data);
    tm_printf("   main: "); print_bits(data);
    if( test_pattern(data) >= 0 ) {
      tm_printf("*** testcase %d: OK\n", i);
    } else {
      tm_printf("*** testcase %d: NG\n", i);
    }
  }
  
  return 0;
}