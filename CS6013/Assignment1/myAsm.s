extern puts



section .text			  ; this says that we're about to write code (as opposed to data)

global sayHello ; this says that "sayHello" is a symbol that the linker needs to know about
global myPuts ; this says that "myPuts" is a symbol that the linker needs to know about
global myGTOD ; this says that "myGTOD is a symbol that the linker needs to know about


section .rodata  ; this is the read only data (hello is a constant) 
helloString: db "hello",0 ; hellostring is the name of our symbol
; db is the directive to put data in our object file
; the 0 is the null terminator that puts is expecting.  
; nasm does NOT null terminate our string automatically


sayHello:          	 	  ; and here we go.

	push rbp		  ; push rbp onto the stack, make room for 8 bytes of space
	mov edi, helloString	  ; move the string in edi
	call puts		  ; call the puts function, print the string at edi
	pop rbp 		  ; restore rbp
  	ret                 	  


myPuts: 
  
  mov rax, 1 			  ; syscall number corresponding to write 
  mov rdx, rsi 			  ; move rsi value (length) into rdx 
  mov rsi, rdi  		  ; move rdi value (string) into rsi
  mov rdi, 1 			  ; move file descriptor into rdi corresponding to stdout 
  syscall 			  
  ret 				  ; return value already in rax 


myGTOD: 
  
  sub rsp, 16 			  ; make 16 bytes of space on stack to store timeval struct 
  mov rdi, rsp			  ; load first argument from timeval struct
  mov rsi, 0 			  ; pass a null pointer disregarding timezone
  mov rax, 96 			  ; syscall number corresponding to get time of day  
  syscall 			   
  mov rdx, [rsp + 8] 		  ; putting microseconds into rdx register   
  mov rax, [rsp] 		  ; putting seconds into rax 
  add rsp, 16 			  ; re-align stack 
  ret 				  ; return value in rax  


	

