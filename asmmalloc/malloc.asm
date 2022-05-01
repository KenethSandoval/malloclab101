section .text
	global _start

_start:
	mov eax, 45 	;sys_brk	
	xor ebx, ebx
	int 80h

	add eax, 16384  ;number of bytes to be reserved
	mov ebx, eax
	mov eax, 45  	;sys_brk
	int 80h

	cmp eax, 0
	jl exit
	mov edi, eax
	sub edi, 4
	mov ecx, 4096
	xor eax, eax
	std
	rep stosd
	cld

	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, len
	int 80h 		;print a message

exit:
	mov eax, 1
	xor ebx, ebx
	int 80h

section .data
msg     db      "Allocated 16kb of memory!", 10
len     equ     $ - msg

