

    global outb             ; make the label outb visible outside this file

    ; outb - send a byte to an I/O port
    ; stack: [esp + 8] the data byte
    ;        [esp + 4] the I/O port
    ;        [esp    ] return address
    outb:
        mov al, [esp + 8]    ; move the data to be sent into the al register
        mov dx, [esp + 4]    ; move the address of the I/O port into the dx register
        out dx, al           ; send the data to the I/O port
        ret                  ; return to the calling function



    global inb

    ; inb - returns a byte from the given I/O port
    ; stack: [esp + 4] The address of the I/O port
    ;        [esp    ] The return address
    inb:
        mov dx, [esp + 4]       ; move the address of the I/O port to the dx register
        in  al, dx              ; read a byte from the I/O port and store it in the al register
        ret                     ; return the read byte



	; Load Global Descriptor table
	global init_gdt_asm
	
	init_gdt_asm:
		mov eax, [esp + 4]
		lgdt [eax]				; load global descriptor table
		
		
		; offset(index bit 15:3), ti (0=GDT, 1=LDT), rpl=(requested priviledge level)
		mov eax, 0x20
		mov ds, eax				; reference 4th segement index
		mov ss, eax				; reference 4th segement index
		mov es, eax				; reference 4th segement index
		
		jmp 0x08:switch_cs
	switch_cs:
		ret
