				.model large,c

EXTRN           delay:PROC

DelayLen        EQU 10h
VideoBuf        EQU 0A000h
MagicNumber     EQU 41
Page0Offset     EQU 00000h
Page1Offset     EQU 02000h
Page2Offset     EQU 04000h
Page3Offset     EQU 06000h
Page4Offset     EQU 08000h
Page5Offset     EQU 0A000h
Page6Offset     EQU 0C000h
Iterations      EQU 1FFFh
; Sweeps        EQU Iterations/MagicNumber

				.code

move_EGA_pages  PROC FAR uses ax bx cx dx es ds si di,ARGfrom:WORD, ARGto:WORD

				mov ax,0105h           ; Set EGA
				mov dx,3CEh            ; Read/Write
				out dx,ax              ; Modes

				mov cx,3
				mov al,4               ; Set the colour
				mov ah,ch              ; plane to access
				out dx,ax              ;

				mov ax,VideoBuf        ; Set ds,es to
				mov ds,ax              ; EGA buffer start
				mov es,ax              ;

				mov ax,ARGfrom
				call FAR PTR set_page_offset
				mov si,ax              ; Move from page ARGfrom

				mov ax,ARGto
				call FAR PTR set_page_offset
				mov di,ax              ; to page ARGto

				mov cx, Iterations
L0:             push cx

				mov bh,ds:[si]
				mov es:[di],bh

				inc si
				inc di

				pop cx
				dec cx
				jnz L0

exit:           mov ax,0F02h           ; Clean up
				out dx,ax              ; EGA CRTC
									   ;
				mov dl,0Ceh            ;
				mov ax,0003            ;
				out dx,ax              ;
									   ;
				mov ax,0005            ;
				out dx,ax              ;
									   ;
				mov ax,0FF08h          ;
				out dx,ax              ;

				ret

move_EGA_pages  ENDP

melt_EGA_pages  PROC FAR uses ax bx cx dx es ds si di, \
				ARGfrom:WORD, ARGto:WORD, ARGMagic:WORD
				LOCAL Sweeps

				xor dx,dx              ; Determine the number of
				mov ax,Iterations      ; 'sweeps' to be made based
				mov cx,ARGMagic        ;
				div cx                 ; on a 'Magic Number' and the
									   ; size of the video buffer-1
				mov Sweeps,ax          ;

				mov ax,0105h           ; Set EGA
				mov dx,3CEh            ; Read/Write
				out dx,ax              ; Modes

				mov cx,3
				mov al,4               ; Set the colour
				mov ah,ch              ; plane to access
				out dx,ax              ;

				mov ax,VideoBuf        ; Set ds,es to
				mov ds,ax              ; EGA buffer start
				mov es,ax              ;

				mov ax,ARGfrom
				call FAR PTR set_page_offset
				mov si,ax              ; Move from page ARGfrom

				mov ax,ARGto
				call FAR PTR set_page_offset
				mov di,ax              ; to page ARGto

				mov cx, ARGMagic
L1:             push cx

				push si
				push di

				mov ax,DelayLen
				push ax

				call delay
				add sp,2

				mov cx, Sweeps
L0:             push cx

				mov bh,ds:[si]
				mov es:[di],bh

				add si,ARGMagic
				add di,ARGMagic

				pop cx
				dec cx
				jnz L0

				pop di
				pop si

				inc si
				inc di

				pop cx

				dec cx
				jnz L1

exit:           mov ax,0F02h           ; Clean up
				out dx,ax              ; EGA CRTC
									   ;
				mov dl,0Ceh            ;
				mov ax,0003            ;
				out dx,ax              ;
									   ;
				mov ax,0005            ;
				out dx,ax              ;
									   ;
				mov ax,0FF08h          ;
				out dx,ax              ;

				ret

melt_EGA_pages  ENDP

set_page_offset PROC FAR

				cmp ax,0             ;   Is it page 0?
				jnz testpage1
				mov ax,Page0Offset
				jmp short pageset

testpage1:      cmp ax,1             ;   Is is page 1?
				jnz testpage2
				mov ax,Page1Offset
				jmp short pageset

testpage2:      cmp ax,2             ;   Is it page 2?
				jnz testpage3
				mov ax,Page2Offset
				jmp short pageset

testpage3:      cmp ax,3             ;   Is it page 3?
				jnz testpage4
				mov ax,Page3Offset
				jmp short pageset

testpage4:      cmp ax,4             ;   Is it page 4?
				jnz testpage5
				mov ax,Page4Offset
				jmp short pageset

testpage5:      cmp ax,5             ;   Is it page 5?
				jnz ispage6
				mov ax,Page5Offset
				jmp short pageset

ispage6:        mov ax,Page6Offset   ;   set to page 6

pageset:        ret

set_page_offset ENDP

				END
