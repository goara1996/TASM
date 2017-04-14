transLate:
	_save_regs
	_print_msg ms_TS_1
	_invoke inputString <data_TS_string>
	_print_msg ms_TS_2
	_invoke inputDecimal <data_TS_son>
	_invoke stringToDigit <data_TS_string, data_TS_number, dw, data_TS_son>
	_print_msg ms_TS_3
	_invoke inputDecimal <data_TS_son>
	_invoke digitToString <dw, data_TS_number, data_TS_string, dw, data_TS_son>
	_print_msg ms_TS_4
	_invoke outputString <data_TS_string>
	_print_msg endl
	_load_regs
	ret; transLate