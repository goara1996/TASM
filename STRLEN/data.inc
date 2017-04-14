;Сообщения
msg		db	'Please, input line:'
endl	db	0dh, 0ah, '$'
msg1	db	'String "$'
msg2	db	'" has size $'
msg3	db	'h$'
rev_Res	db	'Reversed: "$'
cat_Res	db	'Concatenation: "$'
upp_Res	db	'Upper case: "$'
low_Res	db	'Lower case: "$'
msg6	db	'"', 0dh, 0ah, '$'
msg_Found		db	'" is substring of "$'
msg_Not_Found	db	'" is not a substring of "$'

;Буффер ввода
maxbf	db	MAXSIZE
bflen	db	0
buffer	db	MAXSIZE dup('b')

;Строки
str_1	db	MAXSIZE		dup('x')
len_1	db	?
str_2	db	MAXSIZE		dup('x')
len_2	db	?
constr	db	MAXSIZE * 2	dup('c')
conlen	db	?
revstr	db	MAXSIZE		dup('r')
revlen	db	?
lowers	db	MAXSIZE		dup('l')
lowlen	db	?
uppers	db	MAXSIZE		dup('u')
upplen	db	?