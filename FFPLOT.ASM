				TITLE   'High Speed EGA Plot'
				NAME    Plot
				.MODEL  large,pascal

MODE13          EQU     1
BytesPerLine    EQU     40
OriginOffset    EQU     0           /* 320x200 */
VideoBufferSeg  EQU     0A000h
RMWbits         EQU     00h         /* 320x200 */

.code

FFPLOT          PROC ARGx:WORD, ARGy:WORD, ARGn:BYTE

                mov ax,ARGy
                mov bx,ARGx

				mov cl,bl    ; Pixel Address Routine Inline for High Speed

				mov dx,ax    ; This is an extremely high speed
				shl ax,1     ; multiply equivalent.
				shl ax,1     ;
				shl ax,1     ; On exit, AX -> AX*40
				shl ax,1     ; This replaces a MUL 40
				shl ax,1     ; and takes 25 clock cycles
							 ; rather than 130!
				shl dx,1     ;
				shl dx,1     ;
				shl dx,1     ;
							 ;
				add ax,dx    ;

				shr bx,1
				shr bx,1
				shr bx,1

				add bx,ax

				IFNDEF MODE13
				add bx,OriginOffset
				ENDIF

				mov ax,VideoBufferSeg
				mov es,ax
				and cl,7
				xor cl,7
				mov ah,1    ; End of Address Routine

				shl ah,cl
                mov dx,3ceh
                mov al,8
                out dx,ax

				mov ax,0205h
				out dx,ax

				IFNDEF MODE13
				mov ah,RMWbits
				ELSE
				xor ah,ah
				ENDIF

				mov al,3
				out dx,ax

				mov al,es:[bx]
                mov al,ARGn
				mov es:[bx],al

                mov ax,0FF08h		; Set defaults
                out dx,ax

                mov ax,0005
                out dx,ax

                mov ax,0003
                out dx,ax

				ret

FFPLOT          ENDP

                END

