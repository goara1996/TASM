
array=data_AS_array
alength=data_AS_array.length_

arraySorting:
	_save_mem
	_save_regs
l_AS_redo_1:
	_print_msg <ms_AS_1, endl>
	_invoke inputDecimal <alength>
	jcxz l_AS_redo_1
	_print_msg <ms_AS_2, endl>
	_invoke inputArray <array>
	jcxz l_AS_redo_1
l_AS_redo_2:
	_print_msg <ms_AS_3, endl>
	_get_hotkey
	cmp al, '<'
	je l_AS_sort_low
	cmp al, '>'
	je l_AS_sort_high
	jmp l_AS_redo_2

l_AS_sort_low:
	_invoke sortArray <array, sorter_toLow>
	jmp l_AS_output
l_AS_sort_high:
	_invoke sortArray <array, sorter_toHigh>
	jmp l_AS_output
	
l_AS_output:
	_print_msg <ms_AS_4, endl>
	_invoke outputArray <array>
	_load_regs
	_load_mem
	ret; arraySorting