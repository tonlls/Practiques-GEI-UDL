.data
	res:	.double 0.0
	rang:	.double 40.0
	tmp:	.double 1.0
.text
	l.d f4,rang(r0)		; r1=rang
	add.d f3,f3,f0
	l.d f9,tmp(r0)
	sumatori:
		add.d f2,f2,f9
		add.d f1,f4,f0
		facts:
			mul.d f2,f2,f1
			sub.d f1,f1,f9
			beq f1,f9,facts
		div.d f2,f9,f2
		add.d f3,f3,f2
		sub.d f4,f4,f9
		beq f4,f9,sumatori
;	store
