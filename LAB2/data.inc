; Константы
BUFFERSIZE	equ 32
HEAPSIZE	equ BUFFERSIZE * 2
MAXHEAP		equ HEAPSIZE + heap
endl db	0Dh, 0Ah, '$'
ms_array_start		db "{ ", '$'
ms_array_separator	db ", ", '$'
ms_array_end		db " }", '$'
ms_array_index_start 	db " ["		, '$'
ms_array_index_end		db "] = " 	, '$'

; Ошибки
ms_err db "Error encountered: ", '$'
ms_err_heap db "Heap overflow!", '$'
ms_err_dig	db "Invalid digit!", '$'
ms_err_fib	db "Invalid sequence index!", '$'
ms_err_fib_2 db "Sorry, but this sequence index is too large", '$'
ms_err_array 	db "Array size must be higher than zero", '$'
ms_err_array_1	db "Sorry, but array of this size can't fit in memory", '$'

; Типы
; Строка
type_array struc
	length_ dw 0
	data_	dw ?
type_array ends
; Буффер ввода/вывода
type_buffer struc
	bmax_		db	BUFFERSIZE
	blenght_	db	0
	bdata_		db	BUFFERSIZE dup('#')
type_buffer ends

; Разные промежуточные переменные
buffer	type_buffer <>
sbuffer type_array <0, buffer.bdata_>
digitstring type_array <>
digitbuffer dw ?

; Данные процедур
; leonardoBonacci
ms_LB_1	db "Input place in Fibonacci sequence: ", '$'
ms_LB_2 db "Answer is ", '$'
data_LB_number dw ?
; transLate
ms_TS_1 db "Input number: "					, '$'
ms_TS_2 db "Input it's size of notation: "	, '$'
ms_TS_3 db "Input son to translate into: "	, '$'
ms_TS_4 db "Conversion result: "			, '$'
data_TS_number	dw ?
data_TS_son		dw ?
data_TS_string	type_array <>
; arraySortings
ms_AS_1	db "Input array size:"					, '$'
ms_AS_2 db "Input array:"						, '$'
ms_AS_3 db "Choose sorting method. [<] or [>]"	, '$'
ms_AS_4 db "Sorted array:"						, '$'
data_AS_array type_array <>
; main
ms_Main_1 db "Press hotkey for a task"				, '$'
ms_Main_2 db "Now running Fibonacci calculation"	, '$'
ms_Main_3 db "Now running digit translation"		, '$'
ms_Main_4 db "Now running array sorting"			, '$'
ms_Main_hotkeys db 0Dh, 0Ah
		  db "[1] - Fibonacci calculation",	0Dh, 0Ah
		  db "[2] - Digit translation",		0Dh, 0Ah
		  db "[3] - Array sorting",			0Dh, 0Ah
		  db "[q] - Quit programm",			0Dh, 0Ah
		  db '$'
		  
; Куча
heapptr		dw heap
heap	db HEAPSIZE dup('X')