#include "logPrint.h"
#include "uart.h"
#include <stddef.h>

/* sec_sum, s_call_ns functions
extern int sec_func(void);
extern void sec_sum(int a, int b);

extern void s_call_ns(void(*cb)(void));
static void ns_hello(void)
{
	int a = 1;
	a+=1;
}
*/
extern void sec_sum_callback(int a, int b, int(*cb_ns)(int));

static int ns_callback_add10(int sum)
{
	int result = sum+10;
	return result;
}

/* Non Secure main() */
int main(void) {

/*
    sec_sum(3,4);
    s_call_ns(ns_hello);
*/
    sec_sum_callback(1,2,ns_callback_add10);
    while(1);
    return 0;
}
