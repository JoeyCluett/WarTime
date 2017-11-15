	.file	"main.cpp"
	.section	.text._ZN13ButtonHandler18KeyboardButtonDownER9SDL_Event,"axG",@progbits,_ZN13ButtonHandler18KeyboardButtonDownER9SDL_Event,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN13ButtonHandler18KeyboardButtonDownER9SDL_Event
	.type	_ZN13ButtonHandler18KeyboardButtonDownER9SDL_Event, @function
_ZN13ButtonHandler18KeyboardButtonDownER9SDL_Event:
.LFB1824:
	.cfi_startproc
	movb	$1, quit(%rip)
	ret
	.cfi_endproc
.LFE1824:
	.size	_ZN13ButtonHandler18KeyboardButtonDownER9SDL_Event, .-_ZN13ButtonHandler18KeyboardButtonDownER9SDL_Event
	.section	.text._ZN13ButtonHandler16KeyboardButtonUpER9SDL_Event,"axG",@progbits,_ZN13ButtonHandler16KeyboardButtonUpER9SDL_Event,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN13ButtonHandler16KeyboardButtonUpER9SDL_Event
	.type	_ZN13ButtonHandler16KeyboardButtonUpER9SDL_Event, @function
_ZN13ButtonHandler16KeyboardButtonUpER9SDL_Event:
.LFB1825:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE1825:
	.size	_ZN13ButtonHandler16KeyboardButtonUpER9SDL_Event, .-_ZN13ButtonHandler16KeyboardButtonUpER9SDL_Event
	.section	.text._ZN13ButtonHandler15MouseButtonDownER9SDL_Event,"axG",@progbits,_ZN13ButtonHandler15MouseButtonDownER9SDL_Event,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN13ButtonHandler15MouseButtonDownER9SDL_Event
	.type	_ZN13ButtonHandler15MouseButtonDownER9SDL_Event, @function
_ZN13ButtonHandler15MouseButtonDownER9SDL_Event:
.LFB1826:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE1826:
	.size	_ZN13ButtonHandler15MouseButtonDownER9SDL_Event, .-_ZN13ButtonHandler15MouseButtonDownER9SDL_Event
	.section	.text._ZN13ButtonHandler13MouseButtonUpER9SDL_Event,"axG",@progbits,_ZN13ButtonHandler13MouseButtonUpER9SDL_Event,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN13ButtonHandler13MouseButtonUpER9SDL_Event
	.type	_ZN13ButtonHandler13MouseButtonUpER9SDL_Event, @function
_ZN13ButtonHandler13MouseButtonUpER9SDL_Event:
.LFB1827:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE1827:
	.size	_ZN13ButtonHandler13MouseButtonUpER9SDL_Event, .-_ZN13ButtonHandler13MouseButtonUpER9SDL_Event
	.section	.text._ZN13ButtonHandler15DefaultCallbackER9SDL_Event,"axG",@progbits,_ZN13ButtonHandler15DefaultCallbackER9SDL_Event,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN13ButtonHandler15DefaultCallbackER9SDL_Event
	.type	_ZN13ButtonHandler15DefaultCallbackER9SDL_Event, @function
_ZN13ButtonHandler15DefaultCallbackER9SDL_Event:
.LFB1828:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE1828:
	.size	_ZN13ButtonHandler15DefaultCallbackER9SDL_Event, .-_ZN13ButtonHandler15DefaultCallbackER9SDL_Event
	.text
	.p2align 4,,15
	.globl	_ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack
	.type	_ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack, @function
_ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack:
.LFB1821:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdx, %rax
	movq	%rsi, %rbp
	movl	$255, %r8d
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movzbl	2(%rdx), %ecx
	movzbl	(%rax), %esi
	movzbl	1(%rdx), %edx
	call	SDL_SetRenderDrawColor
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	SDL_RenderFillRect
	.cfi_endproc
.LFE1821:
	.size	_ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack, .-_ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack
	.p2align 4,,15
	.globl	_ZN6Render16axisAlignedImageEP12SDL_RendererP11SDL_TextureR8SDL_Rect
	.type	_ZN6Render16axisAlignedImageEP12SDL_RendererP11SDL_TextureR8SDL_Rect, @function
_ZN6Render16axisAlignedImageEP12SDL_RendererP11SDL_TextureR8SDL_Rect:
.LFB1822:
	.cfi_startproc
	movq	%rdx, %rcx
	xorl	%edx, %edx
	jmp	SDL_RenderCopy
	.cfi_endproc
.LFE1822:
	.size	_ZN6Render16axisAlignedImageEP12SDL_RendererP11SDL_TextureR8SDL_Rect, .-_ZN6Render16axisAlignedImageEP12SDL_RendererP11SDL_TextureR8SDL_Rect
	.p2align 4,,15
	.globl	_ZN6Render26axisAlignedImageFullscreenEP12SDL_RendererP11SDL_Texture
	.type	_ZN6Render26axisAlignedImageFullscreenEP12SDL_RendererP11SDL_Texture, @function
_ZN6Render26axisAlignedImageFullscreenEP12SDL_RendererP11SDL_Texture:
.LFB1823:
	.cfi_startproc
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	jmp	SDL_RenderCopy
	.cfi_endproc
.LFE1823:
	.size	_ZN6Render26axisAlignedImageFullscreenEP12SDL_RendererP11SDL_Texture, .-_ZN6Render26axisAlignedImageFullscreenEP12SDL_RendererP11SDL_Texture
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Could not load image file: "
.LC1:
	.string	"    "
	.text
	.p2align 4,,15
	.globl	_Z17loadImageFromFileRKSsP12SDL_Renderer
	.type	_Z17loadImageFromFileRKSsP12SDL_Renderer, @function
_Z17loadImageFromFileRKSsP12SDL_Renderer:
.LFB1836:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	(%rdi), %rdi
	call	IMG_Load
	movq	%rbp, %rdi
	movq	%rax, %rbx
	movq	%rax, %rsi
	call	SDL_CreateTextureFromSurface
	movq	%rbx, %rdi
	movq	%rax, %rbp
	call	SDL_FreeSurface
	testq	%rbp, %rbp
	je	.L14
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rax
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L14:
	.cfi_restore_state
	movl	$.LC0, %esi
	movl	$_ZSt4cerr, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	(%r12), %rsi
	movq	%rax, %rdi
	movq	-24(%rsi), %rdx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	call	SDL_GetError
	movl	$.LC1, %esi
	movq	%rax, %rbx
	movl	$_ZSt4cerr, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE1836:
	.size	_Z17loadImageFromFileRKSsP12SDL_Renderer, .-_Z17loadImageFromFileRKSsP12SDL_Renderer
	.section	.rodata.str1.1
.LC2:
	.string	"Error intializing SDL2\n    "
.LC3:
	.string	"Hello World"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC4:
	.string	"Error creating SDL window\n    "
	.align 8
.LC5:
	.string	"Error creating SDL renderer\n    "
	.section	.rodata.str1.1
.LC6:
	.string	"computer-engineer.jpg"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1829:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1829
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	$29233, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$96, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
.LEHB0:
	call	SDL_Init
	testl	%eax, %eax
	movl	%eax, %r12d
	jne	.L33
	movl	$3, %edi
	call	IMG_Init
	movl	$4103, %r9d
	movl	$480, %r8d
	movl	$640, %ecx
	movl	$100, %edx
	movl	$100, %esi
	movl	$.LC3, %edi
	call	SDL_CreateWindow
	testq	%rax, %rax
	je	.L34
	movl	$6, %edx
	movl	$-1, %esi
	movq	%rax, %rdi
	call	SDL_CreateRenderer
	testq	%rax, %rax
	movq	%rax, %rbx
	je	.L35
	leaq	16(%rsp), %rdi
	leaq	14(%rsp), %rdx
	movl	$.LC6, %esi
	call	_ZNSsC1EPKcRKSaIcE
.LEHE0:
	leaq	16(%rsp), %rdi
	movq	%rbx, %rsi
.LEHB1:
	call	_Z17loadImageFromFileRKSsP12SDL_Renderer
.LEHE1:
	movq	%rax, %rbp
	movq	16(%rsp), %rax
	leaq	15(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	cmpb	$0, quit(%rip)
	jne	.L20
	.p2align 4,,10
	.p2align 3
.L24:
	leaq	32(%rsp), %rdi
.LEHB2:
	call	SDL_PollEvent
	testl	%eax, %eax
	je	.L36
.L25:
	cmpl	$768, 32(%rsp)
	jne	.L24
	leaq	32(%rsp), %rdi
	movb	$1, quit(%rip)
	call	SDL_PollEvent
	testl	%eax, %eax
	jne	.L25
	.p2align 4,,10
	.p2align 3
.L36:
	movq	%rbx, %rdi
	call	SDL_RenderClear
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	SDL_RenderCopy
	movq	%rbx, %rdi
	call	SDL_RenderPresent
	cmpb	$0, quit(%rip)
	je	.L24
.L20:
	call	IMG_Quit
	call	SDL_Quit
.L17:
	movq	88(%rsp), %rcx
	xorq	%fs:40, %rcx
	movl	%r12d, %eax
	jne	.L37
	addq	$96, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L33:
	.cfi_restore_state
	call	SDL_GetError
	movl	$.LC2, %esi
	movq	%rax, %rbx
.L32:
	movl	$_ZSt4cerr, %edi
	orl	$-1, %r12d
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	jmp	.L17
.L34:
	.p2align 4,,5
	call	SDL_GetError
	movl	$.LC4, %esi
	movq	%rax, %rbx
	jmp	.L32
.L35:
	call	SDL_GetError
	movl	$.LC5, %esi
	movq	%rax, %rbx
	jmp	.L32
.L37:
	call	__stack_chk_fail
.L29:
	movq	%rax, %rbx
	movq	16(%rsp), %rax
	leaq	15(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE2:
	.cfi_endproc
.LFE1829:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1829:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1829-.LLSDACSB1829
.LLSDACSB1829:
	.uleb128 .LEHB0-.LFB1829
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1829
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L29-.LFB1829
	.uleb128 0
	.uleb128 .LEHB2-.LFB1829
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1829:
	.section	.text.startup
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I__ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack, @function
_GLOBAL__sub_I__ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack:
.LFB1994:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE1994:
	.size	_GLOBAL__sub_I__ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack, .-_GLOBAL__sub_I__ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN6Render14axisAlignedBoxEP12SDL_RendererR8SDL_RectR9ColorPack
	.globl	quit
	.bss
	.align 16
	.type	quit, @object
	.size	quit, 1
quit:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
