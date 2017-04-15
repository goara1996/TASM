string=data_TS_string
base=data_TS_son
number=data_TS_number

transLate:
	_save_regs
l_TS_redo_1:
	_print_msg ms_TS_1
	_invoke inputString <string>
	_print_msg ms_TS_2
	_invoke inputDecimal <base>
	_invoke stringToDigit <string, number, dw, base>
	jcxz l_TS_redo_1
l_TS_redo_2:
	_print_msg ms_TS_3
	_invoke inputDecimal <base>
	jcxz l_TS_redo_2
	_invoke digitToString <dw, number, string, dw, base>
	_print_msg ms_TS_4
	_invoke outputString <string>
	_print_msg endl
	_load_regs
	ret; transLate