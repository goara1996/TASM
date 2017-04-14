; Вычисление длины нуль-терминированной строки
; Аргументы:
; 1 - Адрес строки
; 2 - Адрес длины строки
strLen:
	_push_regs <ax, si>
	mov si, [_arg 1]
l_SL_1:
	cmp byte ptr [si], 0
	je l_SL_2
	inc si
	jmp l_SL_1
l_SL_2:
	sub si, [_arg 1]
	mov ax, si
	mov si, [_arg 2]
	mov byte ptr [si], al
	
	_pop_regs <si, ax>
	ret ;strLen
;------------------------------------------

; Конкатенация строк
; Аргументы:
; 1 - Адрес первой строки
; 2 - Адрес второй строки
; 3 - Длина второй строки
catPurse:
	;SI - строка ввода
	;DI - строка вывода
l_CP_1:
	cmp byte ptr [si], 0
	je l_CP_2
	push [si]
	pop	 [di]
	inc si
	inc di
	jmp l_CP_1
l_CP_2:
	ret ;catPurse

strCat:
	_push_regs	<si, di>
	
	mov si, [_arg 1]
	mov di, [_arg 3]	
	call catPurse
	
	mov si, [_arg 2]
	call catPurse
	
	mov byte ptr [di], 0
	
	_pop_regs	<di, si>
	ret ;strCat
;------------------------------------------

; Копирование одной строки в другую
; Аргументы:
; 1 - Первая строка
; 2 - Вторая строка
strCpy:
	_push_regs	<si, di>
	
	mov si, [_arg 1]
	mov di, [_arg 2]	
	
l_SC_1:
	push [si]
	pop	 [di]
	inc si
	inc di
	cmp byte ptr [si - 1], 0
	jne l_SC_1
	
	_pop_regs	<di, si>
	ret ;strCpy

;------------------------------------------

; Переворот строки(с копированием в новую)
; Аргументы:
; 1 - Первая строка
; 2 - Вторая строка
; 3 - Длина второй строки
strRev:
	_push_regs	<bx, si, di>
	
	mov si, [_arg 1]
	mov di, [_arg 2]
	mov bx, [_arg 3]
	mov bl, byte ptr [bx]
	mov bh, 0
	add di, bx
	dec di
	
l_SR_1:
	cmp byte ptr [si], 0
	je l_SR_2
	mov bh, byte ptr [si]
	mov byte ptr [di], bh
	inc si
	dec di
	jmp l_SR_1
l_SR_2:

	mov bh, 0
	inc di
	add di, bx
	mov byte ptr [di], 0
	
	_pop_regs	<si, di, bx>
	ret ;strRev

;------------------------------------------

; Замена всех букв указанной строки на 
; заглавные или прописные
; Аргументы:
; 1 - Изменяемая строка
low_Char:
	mov al, byte ptr [si]                   
    cmp al, 65                              
    jb l_LC_end                                 
    cmp al, 90                              
    ja l_LC_end                               
    add byte ptr [si], 32
l_LC_end:
	ret ;low_Char
	
up_Char:
	mov al, byte ptr [si]                   
    cmp al, 97                             
    jb l_UC_end                                 
    cmp al, 122                            
    ja l_UC_end                               
    sub byte ptr [si], 32
l_UC_end:
	ret ;up_Char

mod_Pattern macro fun
	local l_MP_1, l_MP_2
	_push_regs	<ax, si>
	
	mov si, [_arg 1]
l_MP_2:
	cmp byte ptr [si], 0
	je l_MP_1
	call fun
	inc si
	jmp l_MP_2
l_MP_1:

	_pop_regs	<si, ax>
endm ;mod_Pattern

toLower:	
	mod_Pattern low_Char
	ret ;toLower
	
toUpper:
	mod_Pattern up_Char
	ret ;toUpper

;------------------------------------------

; Поиск подстроки
; Аргументы:
; 1 - Первая строка
; 2 - Длина первой строки
; 3 - Вторая строка
; 4 - Длина второй строки
findSub:
	_push_regs <ax, bx, cx, dx, si, di>
	
	_print_msg msg1
	
	mov dx, [_arg 1]
	mov bx, [_arg 2]
	xor cx, cx
	mov cl, byte ptr [bx]
	_print_str dx, cx
	
	mov bx, [_arg 2]
	mov ah, byte ptr [bx]
	mov bx, [_arg 4]
	mov al, byte ptr [bx]
	
	cmp al, ah
	jle l_FS_Not_Found
	cmp ah, 0
	jle l_FS_Not_Found
	
	mov si, [_arg 1]
	mov di, [_arg 3]
	mov bx, si
	
l_FS_1:
	cmp byte ptr [si], 0
	je l_FS_Found
	cmp byte ptr [di], 0
	je l_FS_Not_Found
	
	mov dh, byte ptr [si]
	mov dl, byte ptr [di]
	cmp dh, dl
	jne l_FS_3
	inc si
	jmp l_FS_4
l_FS_3:
	mov si, bx
l_FS_4:
	inc di
	jmp l_FS_1
	
l_FS_Found:
	_print_msg msg_Found
	je l_FS_end
	
l_FS_Not_Found:
	_print_msg msg_Not_Found
	
l_FS_end:

	mov dx, [_arg 3]
	mov bx, [_arg 4]
	xor cx, cx
	mov cl, byte ptr [bx]
	_print_str dx, cx
	
	_print_msg msg6
	
	_pop_regs <di, si, dx, cx, bx, ax>
	ret ;findSub

;------------------------------------------