masm
model small

.stack 100h

.data

mesg	db	"That program is for TD only", 0dh, 0ah, '$'

var1	dw	0FFh
var2	dd	3A7Fh
var3	dd	0F54D567Ah

mass	db	10	dup (" ")
pole	db	5	dup (?)

adrs	dw	var3
adrf	dd	var3

fins	db	"End of data segment $"

.code

start:
	mov ax, @data
	mov ds, ax
	
	mov ah, 09h
	mov dx, offset mesg
	int 21h
	
	mov ax, 4C00h
	int 21h
	
end start