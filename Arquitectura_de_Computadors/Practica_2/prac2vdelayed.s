.data
	res:	.double 0
	rang:	.word32 14
	tmp:	.double 1
.text
	lw r2,rang(r0)
	l.d f9,tmp(r0)
	daddi r1,r0,1
	sum:
		add.d f1,f0,f9
		dadd r3,r0,r2
		fact:
			mtc1 f11,r3
			cvt.l.d F2,F11
			dsub r3,r3,r1
			bne r3,r0,fact
			mul.d f1,f1,f2
		dsub r2,r2,r1
		add.d f6,f6,f3
		; bne r2,r0,sum
		bne f3,f6,sum
		div.d f3,f9,f1
	add.d f6,f6,f9
halt