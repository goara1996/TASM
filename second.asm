;Программа преобразования двузначного шестнадцатеричного числа
;в символьном виде в двоичное представление.
;При помощи команды xlat
;Вход: Исходное шестнадцатеричное число из двух цифр
;вводится с клавиатуры
;Выход: Результат преобразования помещается в регистр dl

masm
model small

;Сегмент макросов(условно)
_push_regs macro list
	irp reg, <list>
		push reg
	endm
endm

_pop_regs macro list
	irp reg, <list>
		pop reg
	endm
endm

_end_prog macro
	mov ax,4c00h
    int 21h
endm

;Сегмент данных
.data
msg		db	'Please, input two hex: ', '$'
tabl	db	48 dup ('x') ;Часть таблицы ASCII, размещенная в памяти
		db	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 	7 dup('x')
		db	0Ah, 0Bh, 0Ch, 0Dh, 0Eh, 0Fh,  26 dup('x')
		db	0Ah, 0Bh, 0Ch, 0Dh, 0Eh, 0Fh, 153 dup('x')
endl	db	0dh, 0ah, '$'

;Сегмент стека
.stack 256

;Сегмент кода
.code

getNum:

	;Подготовка данных
	_push_regs <ax, bx, cx>
	xor dl, dl
	
	mov ax, @data	
	mov ds, ax
	
	lea bx, tabl
	
	mov dx, offset msg
	mov ah, 09h
	int 21h
	
	xor ax, ax
	
	;Ввод первого символа
	mov ah, 1h
m_wrong_1:
	int 21h
	
	xlat
	cmp al, 'x'
	je m_wrong_1
	
	mov dl, al
	mov cl, 04h
	shl dl, cl
	
	;Ввод второго символа
m_wrong_2:
	int 21h
	cmp al, 'x'
	je m_wrong_1
	
	xlat
	
	add dl, al
	
	;Возвращаем регистры в исходное состояние
	_pop_regs <cx, bx, ax>
	
	ret

main:
	call getNum
	
	mov dx, offset endl
	mov ah, 09h
	int 21h
	
    _end_prog

end main