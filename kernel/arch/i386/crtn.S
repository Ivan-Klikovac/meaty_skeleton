.section .init
	// gcc will nicely put the contents of crtend.o's .init section here
	popl %ebp
	ret

.section .fini
	// and .fini section here
	popl %ebp
	ret
