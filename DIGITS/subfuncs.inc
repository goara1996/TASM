; Символ в число
; [dl]
charToNum:
	sub dl, '0'
	cmp dl, 9
	jle l_CTN_end
	sub dl, 'A'-'0'-10
l_CTN_end:
	ret ;charToNum
;-------------------
	
; Число в символ
; [dl]
numToChar:
	add dl, '0'
    cmp dl, '9'
    jle l_NTC_end
    add dl, 'A'-'0'-10
l_NTC_end:
	ret ;numToChar
;-------------------

; В нижний регистр
; [al] [si]
low_Char:
	mov al, byte ptr [si]                   
    cmp al, 'A'                            
    jb l_LC_end                                 
    cmp al, 'Z'                            
    ja l_LC_end                               
    add byte ptr [si], 'a' - 'A'
l_LC_end:
	ret ;low_Char
;-------------------

; В верхний регистр
; [al] [si]
up_Char:
	mov al, byte ptr [si]                   
    cmp al, 'a'                             
    jb l_UC_end                                 
    cmp al, 'z'                            
    ja l_UC_end                               
    sub byte ptr [si], 'a' - 'A'
l_UC_end:
	ret ;up_Char
;-------------------

; Удалить все кроме цифр и букв
; [al] [si]
clean_Up:
	mov al, byte ptr [si]
	cmp al, 'a'                             
    jb l_CU_1                                
    cmp al, 'z'                            
    ja l_CU_1                              
    sub byte ptr [si], 'a' - 'A'
	jmp l_CU_end
l_CU_1:
    cmp al, 'A'
    jb l_CU_2
    cmp al, 'Z'
    ja l_CU_2
	jmp l_CU_end
l_CU_2:
	cmp al, '0'
    jb l_CU_del
    cmp al, '9'
    ja l_CU_del
	jmp l_CU_end
l_CU_del:
	mov byte ptr [si], ' '
l_CU_end:
	ret ;up_Char
;-------------------