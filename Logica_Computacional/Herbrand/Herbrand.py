class Clause:
	def __init__(self,str=None,preds=None):
		if str is not None:
			self.preds=str.split(' ')
			self.preds=[int(i) for i in self.preds]
		elif preds is not None:
			self.preds=preds
	def __sub__(self,o):
		cl=[it for it in self.preds if it not in o.preds]
		return Clause(preds=cl)
		
	def __add__(self,o):
		return Clause(preds=self.preds+o.preds)
	
	def resolve(self,cl):
		to_rem=[]
		res=[]
		for c in self.preds:
			if Clause.negate(c) in cl.preds:
				to_rem.append(c)
				to_rem.append(Clause.negate(c))
				
		return None
	def negate(c):
		return c*-1
class ErrorCodes:
	pass
class Herbrand:
	def __init__(self,cl):
		self.cl=cl
		self.i=0
	def get_domain(self):
		pass
	def get_basic_instances(self):
		pass
	def solve(self):
		pass
class Resolution:
	MAX_LOOPS=200
	def __init__(self,cl):
		self.ini_cl=cl
		self.cl=cl
	def resolve(cl1,cl2):
		new=[]
		for p in cl1:
			if Clause.negate(p) in cl2.preds:
				
	def solve(self):
		for(