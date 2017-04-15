; Константы
DIGITLENGTH	equ 16
BUFFERSIZE	equ DIGITLENGTH + 48
HEAPSIZE	equ BUFFERSIZE * 16
MAXHEAP		equ HEAPSIZE + heap
endl db	0Dh, 0Ah, '$'

; Ошибки
ms_err db "Error encountered: $"
ms_err_heap db "Heap overflow!$"
ms_err_dig	db "Invalid digit!$"
ms_err_fib	db "Invalid sequence index!$"
ms_err_fib_2 db "Sorry, but this sequence index is too large$"

; Типы
; Строка
type_string struc
	length_ dw 0
	data_	dw ?
type_string ends
; Буффер ввода/вывода
type_buffer struc
	bmax_		db	BUFFERSIZE
	blenght_	db	0
	bdata_		db	BUFFERSIZE dup('#')
type_buffer ends

; Сам буффер
buffer	type_buffer <>
sbuffer type_string <0, buffer.bdata_>
digitstring type_string <>

; Данные процедур
; leonardoBonacci
ms_LB_1	db "Input place in Fibonacci sequence: $"
ms_LB_2 db "Answer is $"
data_LB_number dw ?
; transLate
ms_TS_1 db "Input number: $"
ms_TS_2 db "Input it's size of notation: $"
ms_TS_3 db "Input son to translate into: $"
ms_TS_4 db "Conversion result: $"
data_TS_number	dw ?
data_TS_son		dw ?
data_TS_string	type_string <>
; main
ms_Main_1 db "Press hotkey for a task$"
ms_Main_2 db "Now running Fibonacci calculation$"
ms_Main_3 db "Now running digit translation$"
ms_Main_4 db "Now running array sorting$"
ms_Main_hotkeys db 0Dh, 0Ah
		  db "[1] - Fibonacci calculation",	0Dh, 0Ah
		  db "[2] - Digit translation",		0Dh, 0Ah
		  db "[3] - Array sorting",			0Dh, 0Ah
		  db "[q] - Quit programm",			0Dh, 0Ah
		  db '$'
		  
; Куча
heapptr	dw heap
heap	db HEAPSIZE dup('X')