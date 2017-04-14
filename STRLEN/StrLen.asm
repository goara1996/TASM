masm
model small

;Макросы
include macro.inc

;Сегмент данных
.data
include data.inc

;Сегмент стека
.stack 256

;Сегмент кода
.code
include input.inc
include strops.inc
include output.inc

main:
	_initds
	
	; Проверка целостности регистров
	mov ax, 12h
	mov bx, 34h
	mov cx, 56h
	mov dx, 78h
	mov si, 90h
	mov di, 69h
	
	; Ввод первой строки
	_invoke	inLine	<maxbf>
	_invoke	bufToNF	<buffer, str_1,	bflen>
	_invoke	strLen 	<str_1,  len_1>
	
	; Ввод второй строки
	_invoke	inLine	<maxbf>
	_invoke	bufToNF	<buffer, str_2, bflen>
	_invoke	strLen 	<str_2,  len_2>
	
	; Конкатенация строк
	_invoke strCat	<str_1,	str_2, constr>
	_invoke strLen	<constr, conlen>
	
	; Переворот строки
	_invoke	strRev	<str_1,  revstr, len_1>
	_invoke	strLen	<revstr, revlen>
	
	; Нижний регистр
	_invoke	strCpy	<str_2,	 lowers>
	_invoke	strLen 	<lowers, lowlen>
	_invoke toLower	<lowers>
	
	; Верхний регистр
	_invoke	strCpy	<str_2,	 uppers>
	_invoke	strLen 	<uppers, upplen>
	_invoke	toUpper	<uppers>
	
	; Вывод всех строк
	_invoke outLine	<str_1,	 len_1>
	_invoke outLine	<str_2,	 len_2>
	_invoke	findSub	<str_1,	 len_1, str_2, len_2>
	_invoke outStr	<cat_Res, constr, conlen>
	_invoke outStr	<rev_Res, revstr, revlen>
	_invoke outStr	<low_Res, lowers, lowlen>
	_invoke outStr	<upp_Res, uppers, upplen>
	
	; Конец программы
	_end_prog
;------------------------------------------

end main