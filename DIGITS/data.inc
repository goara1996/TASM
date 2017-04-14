; Сообщения
inputms	db	"Input text: $"
msg1	db	"Your input: $"
errmsg	db	"ERROR!: $"
heaperr	db	"Heap depleted$"
zeromsg	db	"$"
endl	db	0Dh, 0Ah, '$'

; Буффер ввода
bfsize	db	BUFFERSIZE
buflen	db	0
buffer	db	BUFFERSIZE dup('B')

dgtbuf	db	20 dup('0')

; Строки
stringST struc
	length_ dw 0 ; Фактическая длина
	data_	dw ? ; Указатель на выделенную память
stringST ends

dgbuf	stringST<0, dgtbuf>
str_1	stringST<>
str_2	stringST<>

; Числа
digit_1	dw	?
digit_2	dw	?

digitbase	dw	10

; Куча
heapptr	dw heap
heap	db HEAPSIZE dup('X')