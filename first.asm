;��������� �������������� ����������� ������������������ �����
;� ���������� ���� � �������� �������������.
;����: �������� ����������������� ����� �� ���� ����
;�������� � ����������
;�����: ��������� �������������� ���������� � ������� dl


;������� ��������(�������)
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

;������� ������
data segment para public "data"
    msg db 'Please, input two hex',0dh,0ah,'$'
data ends

;������� �����
stk segment stack
    db 256 dup("?")
stk ends

;������� ����
code segment para public "code"

getNumber proc
	assume cs:code, ds:data, ss:stk

	;���������� ������
	_push_regs <ax, cx>
	xor dl, dl

    ;����� ������ msg
    mov ax, data
    mov ds, ax
    mov dx, offset msg
    mov ah, 09h
    int 21h

    ;���� ������ �����
    xor ax, ax
    mov ah, 01h
    int 21h

    ;�������� - ����� ��� �����
    mov dl, al
    sub dl, 30h
    cmp dl, 09h
    jle M1
    sub dl, 27h
M1:
    mov cl, 04h
    shl dl, cl
    int 21h
    sub al, 30h
    cmp al, 09h
    jle M2
    sub al, 27h
M2:
    add dl, al
	
	;���������� �������� � �������� ���������
	_pop_regs <cx, ax>
	
	ret
getNumber endp

main proc
    assume cs:code, ds:data, ss:stk
	
	call getNumber

    _end_prog
main endp

code ends

end main