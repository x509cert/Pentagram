                .model large,c

DelayLen	EQU 5
VideoBuf        EQU 0A000h
Bytes_Across    EQU 27
Top_Pixel       EQU 28
Bot_Pixel       EQU 108
Pixels_Down     EQU (Bot_Pixel-Top_Pixel)+6
Next_Up         EQU 40
Iterations      EQU 100

EXTRN	delay:PROC

				.code

Fscroll_shield   PROC uses ax bx cx dx es ds si di

				 mov cx, Iterations

L3:              push cx

				 cld

				 mov ax,0105h           ; Set EGA
				 mov dx,3CEh            ; Read/Write
				 out dx,ax              ; Modes

				 mov si,110bh           ; Move from a line
				 mov di,1133h           ; to the line below
				 mov bl,Pixels_Down     ; cl->number of lines down


L0:              push si
				 push di

				 mov cx,3
				 mov al,4               ; Set the colour
				 mov ah,ch              ; plane to access
				 out dx,ax              ;

				 mov ax,Videobuf        ; Setup data and extra
				 mov ds,ax              ; segments to be used
				 mov es,ax              ; in the move

				 mov cx,Bytes_Across    ; Set number of bytes to move

				 rep movsb              ; do the move

				 pop di
				 pop si

				 sub si,Next_Up
				 sub di,Next_Up

				 dec bl
				 jnz L0

				 mov ax,DelayLen
				 push ax
				 call delay
				 add sp,2

				 pop cx

				 dec cx
				 jnz L3

exit:            mov ax,0F02h
				 out dx,ax

				 mov dl,0Ceh
				 mov ax,0003
				 out dx,ax

				 mov ax,0005
				 out dx,ax

				 mov ax,0FF08h
				 out dx,ax

                 ret

Fscroll_shield   endp

				 end
