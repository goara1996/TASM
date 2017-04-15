
Errors_Heap_Overflow:
_print_msg <ms_err, ms_err_heap, endl>
jmp Errors_crash

Errors_Digit_Invalid:
_print_msg <ms_err, ms_err_dig, endl>
jmp Errors_crash

Errors_crash:
_exit_prog