                .model large,c

VideoBuf        EQU 0A000h
Bytes_Across    EQU 18
Top_Pixel       EQU 8
Bot_Pixel       EQU 103
Pixel_Move      EQU 12
Iterations      EQU (Bot_Pixel-Top_Pixel)+1
Next_Line       EQU 40

				.code

scroll_north     PROC uses ax bx cx dx es ds si di

				 cld

				 mov ax,0105h           ; Set EGA
				 mov dx,3CEh            ; Read/Write
				 out dx,ax              ; Modes

				 mov si,1019h           ; Move from a line
				 mov di,11F9h           ; to the line above
				 mov bl,Iterations     ; bl->number of lines down


L0:              push si
				 push di

				 mov ch,3               ; Plane number
				 mov al,4               ; Set the colour
				 mov ah,ch              ; plane to access
				 out dx,ax              ;

				 mov ax,Videobuf       ; Setup data and extra
				 mov ds,ax              ; segments to be used
				 mov es,ax              ; in the move

				 mov cx,Bytes_Across   ; Set number of bytes to move
				 rep movsb              ; do the move

				 pop di
				 pop si

				 sub si,Next_Line
				 sub di,Next_Line

				 dec bl
				 jnz L0

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

scroll_north     endp

				 end
