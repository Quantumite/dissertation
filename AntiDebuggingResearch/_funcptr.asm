.code


; fastcall calling convention, 
_funcptr PROC
	push rbp
	mov rbp, rsp
	sub rsp, 28h
	push rcx
	sub rdx, rcx
	pop rax
	add rax, rdx
	add rsp, 28h
	pop rbp
	ret

_funcptr ENDP


END