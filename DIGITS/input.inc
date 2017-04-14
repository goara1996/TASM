; Динамическое выделение памяти по байтам
; Использует пространство в конце сегмента данных
; Аргументы:
; 1 - Адрес, по которому будет размещен
;     адрес выделенной области
; 2 - Адрес длины выделяемой памяти
allocate:
	_push_regs	<ax, bx>
	
	mov ax, heapptr
	lea bx, heap
	sub ax, bx
	_unref bx, <_arg 2>
	add ax, bx
	cmp ax, HEAPSIZE
	jl l_alloc_noerr
	_print_msg <errmsg, heaperr, endl>
	_end_prog
l_alloc_noerr:
	
	mov bx, [_arg 1]
	mov ax,  heapptr
	mov [bx], ax
	
	_unref bx, <_arg 2>
	add heapptr, bx
	
	_pop_regs	<bx, ax>
	ret ;allocate
;------------------------------------------

; Переводит указатель кучи в
; первоначальное значение
freeheap:
	push ax
	lea ax, heap
	mov heapptr, ax
	pop ax
	ret ;freeheap
;------------------------------------------

; Из буффера в нуль-терминированную строку
; Аргументы:
; 1 - Адрес буффера
; 2 - Адрес адреса строки
; 3 - Адрес длины буффера
bufToNT:
	_push_regs <si, di, bx, dx>
	; Аргументы в регистры
	mov si, [_arg 1]
	mov di, [_arg 2]
	mov bx, [_arg 3] 
	; Запись размера
	xor bh, bh
	mov bl, byte ptr [bx]
	mov [di].length_, bx
	; Запись данных
	mov di, [di].data_
	
l_BTN_1:
	cmp bl, 0
	je l_BTN_2
	push [si]
	pop  [di]
	inc si
	inc di
	dec bl
	jmp l_BTN_1
l_BTN_2:
	mov byte ptr [di], 0
	
	_pop_regs <dx, bx, di, si>
	ret ;bufToNT
;------------------------------------------

; Получение из ввода нуль-терминированной
; строки.
; Память под строку распределяется динамически	
; Аргументы:
; 1 - Строка
	
getNTstring:
	_push_regs	<ax, bx, dx, si>
	
	_print_msg <inputms, endl>
	mov dx, offset bfsize
	mov ah, 0Ah
	int 21h
	_print_msg endl

	mov ax, heapptr
	lea bx, heap
	sub ax, bx
	mov bl, buflen
	mov bh, 0
	inc bx
	add ax, bx
	cmp ax, HEAPSIZE
	jl l_salloc_noerr
	_print_msg <errmsg, heaperr, endl>
	_end_prog
l_salloc_noerr:
	
	mov si, [_arg 1]
	mov ax, heapptr
	mov [si].data_, ax
	
	mov bl, buflen
	mov bh, 0
	inc bx
	add heapptr, bx

	_invoke bufToNT	  <buffer, [si], buflen>  
	
	_pop_regs	<si, dx, bx, ax>
	ret ;getNTstring
;------------------------------------------