;;;;;;;;;;;;;;;;;;;;;;;
;;
;;Author: Tailang CAO
;;Date:01/29/2024
;;
;;;;;;;;;;;;;;;;;;;;;	mov rbp, rsp		;;Update bp
	sub rsp, 20		;section .rodata ; read only data
section .text ;this says that we're about to write code
    global print_int,main
;;;;
;Start
;;	void print_int(long x);
;;       1234=> '1' '2' '3' '4'
;;       1234/ 10 = 123 remainder 4
;;       123 /10 = 12 remainder 3
;;       12 / 

