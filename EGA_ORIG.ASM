		TITLE "EGA Origin"
		NAME EGA_Origin
		.MODEL LARGE,C

;	Usage:
;
;	Callable from C as: EGA_origin(x,y,num_bytes);
;
;	x and y are the coordinates of the origin
;	num_bytes is the horizontal byte count
;
;

CRT_MODE	EQU	49h
ADDR_6845	EQU	63h
POINTS		EQU	85h
BIOS_FLAGS	EQU	89h

.DATA

BYTES_PER_ROW	DW	1 (40)

.CODE


EGA_origin	PROC	ARGx:WORD, ARGy:WORD, ARGn:WORD

		push si
		push di
		
		mov ax,40h
		mov es,ax
		mov cl,es:[CRT_MODE]
		mov ax,ARGx
		mov bx,ARGy

		cmp cl,7
		ja L01
		je L02

		test byte ptr es:[BIOS_FLAGS],1
		jnz L02
		jmp short L03

L01:		mov cx,8
		div cl
		mov cl,ah
		xor ah,ah
		xchg ax,bx
		mul ARGn
		jmp short L05
		
L02:		mov cx,9
		div cl
		dec ah
		jns L04
		mov ah,8
		jmp short L04

L03:		mov cx,8
		div cl
		
L04:		mov cl,ah
		xor ah,ah
		xchg ax,bx
		div byte ptr es:[POINTS]
		xchg ah,ch
		mul ARGn
		shr ax,1
	
L05:		call short SetOrigin
		pop di
		pop si
		ret

EGA_origin	ENDP

SetOrigin	PROC near
		
		add bx,ax
		mov dx,es:[ADDR_6845]
		add dl,6
		
L20:		in al,dx
		test al,8
		jz L20

L21:		in al,dx
		test al,8
		jnz L21
		
		cli		
		sub dl,6

		mov ah,bh
		mov al,0Ch
		out dx,ax

		mov ah,bl
		inc al
		out dx,ax
		sti

		add dl,6

L22:		in al,dx
		test al,8
		jz L22

		cli
		
		sub dl,6
		mov ah,ch
		mov al,8
		out dx,ax
		
		mov dl,0C0h
		mov al,13h OR 20h
		out dx,al
	
		mov al,cl
		out dx,al
	
		sti
		ret

SetOrigin	ENDP		

FFpent_pan  PROC 

		push si
		push di

		mov cx,200

FFL0:           push cx

		mov ax,40       ; Bytes per row
		push ax

		push cx         ; Y position

		xor ax,ax
		push ax         ; X position

		call EGA_origin

		add sp,6        ; Clear stack frame

		pop cx

		dec cx
		jge FFL0

		pop di
		pop si

		ret

FFpent_pan  ENDP


		END
