        TITLE   Noise
        DOSSEG
        .MODEL SMALL
        .STACK 100h

SND_COUNT       EQU   182
COUNT_PORT      EQU   66
INIT_PORT       EQU   67
LOOP_NUM        EQU   1000

        .DATA

        .CODE

start:  mov ax,0
        mov es,ax

        mov cx,LOOP_NUM
        xor bx,bx

l0:     push bx
        push cx

        mov dx,INIT_PORT
        mov al,SND_COUNT
        out dx,al

        mov dx,COUNT_PORT

        mov ax,bx
        out dx,al
        mov ah,al
        out dx,al

        mov dx,97
        in  al,dx

        mov ah,al

        or al,3h
        out dx,al

        mov cx,1800
L1:     push ax
        pop ax
        loop L1

        mov al,ah
        out dx,al

        pop cx
        pop bx

        inc bx
        loop l0

        mov ax,4c00h
        int 21h

        end start
