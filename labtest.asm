stac segment stack
    dw 100h dup(?)
stac ends
data segment
    error db "Under construction",00h,0Ah,'$'
    message db "enter string",00h,0Ah,'$'
    message2 db 0dh, 0Ah, "you enter", 00h,0Ah,'$'
    message3 db 0dh, 0Ah, "length of string is ",00h,0Ah,'$'
    message4 db 0dh, 0Ah, "------------------------------------",00h,0Ah,'$'
    message5 db 0dh, 0Ah,?,00h,0Ah,'$'
    buf db 42,?,40 dup('$')
    crlf db 0dh, 0Ah,'$'
    r db '0',00h,0Ah,'$'
    
data ends
code segment
my proc far
    assume cs:code, ds:data,ss:stac
    mov ax,data
    mov ds,ax
    ;message show
    mov dx, offset message
    mov ah,9
    int 21h
    ; input string
    mov ah, 0Ah
    lea dx, buf
    int 21h
    ;output string
    mov dx,offset message2
    mov ah,9
    int 21h
    mov ah,9
    lea dx,buf+2
    int 21h
    ;length of string
    mov ax, ds
    mov es, ax
    mov di, offset buf
    mov cx, 0FFh
    xor ax, ax
    repnz cmpsb
      not cx
      inc cx
      add cx,'0'
      mov r,ch
      mov dx,offset r
    mov ah,9
    int 21h
    ;big string
    mov dx,offset message4
    mov ah,9
    int 21h
    ;---------
    LEA SI,message
    LEA DI,message2
        MOV CX,00
        INC SI
        L1:INC SI
        CMP BYTE PTR[SI],"$"
        JNE L1
        ADD DI,2
        MOV BX,0
      L2:      
        MOV BL,BYTE PTR[DI]
        MOV BYTE PTR[SI],BL    
        INC SI
        INC DI
        CMP BYTE PTR[DI],"$"
        JNE L2
     L8:DEC SI
        CMP SI,2
        JNE L8
        MOV AH,09H
        LEA DX,message
        INT 21H
     L6:
        MOV BL,BYTE PTR[SI]
        MOV AH,02H
        MOV DL,BL
        INT 21H
        INC SI
        CMP BYTE PTR[SI],"$"
        JNE L6
    ;reverse
    mov dx,offset message4
    mov ah,9
    int 21h
    ;---------
    xor ax, ax
    mov al, byte ptr [buf+1]
    lea di, [buf+2]
    lea si, [message5]
    add si, ax
    dec si
    mov cx, ax
    next:
      mov al, byte ptr [di]
      mov byte ptr [si], al
      inc di
      dec si 
    loop next
    mov dx,offset message5
    mov ah,9
    int 21h
    ;search understring
    mov dx,offset message4
    mov ah,9
    int 21h
    ;---------
    mov dx,offset error
    mov ah,9
    int 21h
    ;registr
    ;-----Upper Registr----
     mov dx,offset message4
    mov ah,9
    int 21h
    mov si, 0                                           
    mov ax, 0
    metka1:                                   
    mov al, [message+si]                    
      cmp al, 97                              
      jb metka2                                  
      cmp al, 122                              
      ja metka2                                  
      sub al, 32                               
    metka2:      
      mov [message5+si], al                     
      inc si
      cmp al, ah                              
      jne metka1                              
    mov [message5+si], '$'                    
    mov dx,offset message5
    mov ah,9
    int 21h
    ;-----Down Registr-----
    mov si, 0                                            
    mov ax, 0
    mov al, 0
    mov si, 0
    metka3:                                   
      mov al, [message5+si]                     
      cmp al, 65                              
      jb metka4                                  
      cmp al, 90                              
      ja metka4                              
     add al, 32                               
    metka4:      
      mov [message5+si], al                     
      inc si
      cmp al, ah                              
      jne metka3                              
      mov [buf+si], '$'                   
    mov dx,offset buf
    mov ah,9
    int 21h
    
    mov ah,9
    int 21h  
    xor ax,ax
    int 16h
    ret
my endp
code ends
end my