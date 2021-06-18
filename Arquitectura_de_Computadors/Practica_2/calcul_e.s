.data
	res:	.double 0
	rang:	.word32 11
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
			mul.d f1,f1,f2
			bne r3,r0,fact
		dsub r2,r2,r1
		div.d f3,f9,f1
		add.d f6,f6,f3
		bne r2,r0,sum
	add.d f6,f6,f9
	s.d f6,res(r0)
halt