                .model large,c

VideoBuf        EQU 0A000h
Bytes_Across    EQU 13
Top_Pixel       EQU 39
Bot_Pixel       EQU 184
Pixels_Down     EQU (Bot_Pixel-Top_Pixel)+6
Next_Down       EQU 40
Iterations      EQU 9

				.code

Fscroll_combat PROC uses ax bx cx dx es ds si di, loop_num:WORD

				 mov cx, loop_num

L3:              push cx

				 cld

				 mov ax,0105h           ; Set EGA
				 mov dx,3CEh            ; Read/Write
				 out dx,ax              ; Modes

				 mov si,0632h           ; Move from a line
				 mov di,060Ah           ; to the line above
				 mov bh,Pixels_Down     ; cl->number of lines down


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

				 add si,Next_Down
				 add di,Next_Down

				 dec bh
				 jnz L0

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

Fscroll_combat  endp

				 end
