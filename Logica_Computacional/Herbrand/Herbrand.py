class Constants:
	PREDICATE_TYPE=1
	FUNCTION_TYPE=2
	CONSTANT_TYPE=3
	VARIABLE_TYPE=4
class Atom:
	PREDICATES=[]
	CONSTANTS=[]
	VARS=[]
	def __init__(self,str):
		self.__str=str
		self.__params=[]
		self.fullname=Atom.get_fullname(str)
		self.name=self.fullname[0]
		self.index=int(self.fullname[1:])
		if self.name=='P':
			self.type=Constants.PREDICATE_TYPE
			for i in range(len(self.fullname),len(str)):
				self.params.append(
		elif self.name=='f':
			self.type=Constants.FUNCTION_TYPE
		elif self.name=='c':
			self.type=Constants.CONSTANT_TYPE
		elif self.name=='v':
			self.type=Constants.VARIABLE_TYPE
			
	def get_fullname(str):
		name=''
		l=0
		for i in str:
			if i in ['f','P','v','c']:
				if i>0:
					return name
				l+=1
			name+=i
	def __eq__(self,o):
		return self.__str==o.__str
	def __neg__(self):
		pass
		#self.__str=self.__str.replace('-' if
class UniqueList:
	def __init__(self,list=[]):
		self.__lst=list(set(list))
	def __eq__(self,o):
		return self.__lst==o.__lst
	def __len__(self):
		return len(self.__lst)
	def __getitem__(self,item):
		return self.__lst[item]
	def append(self,i):
		if i not in self.__lst:
			self.__lst.append(i)
	def remove(self,o):
		self.__lst.remove(o)
	def insert(self,i,o):
		if o not in self.__lst:
			self.__lst.insert(i,0)
#{c,¬c,u,...}
class Clause:
	def __init__(self,str=None,preds=None):
		if str is not None:
			p=str.split(' ')
			p=[Atom(i) for i in self.__preds]
			self.__preds=UniqueList(p)
		elif preds is not None:
			self.__preds=UniqueList(preds)
	def __sub__(self,o):
		cl=[it for it in self.__preds if it not in o.__preds]
		return Clause(preds=cl)
		
	def __add__(self,o):
		return Clause(preds=self.__preds+o.__preds)
	def have_empty(self):
		if '' in self.__preds
	def resolve(self,cl):
		to_rem=[]
		res=[]
		for c in self.preds:
			if Clause.negate(c) in cl.__preds:
				to_rem.append(c)
				to_rem.append(Clause.negate(c))
				
		return None
	def negate(c):
		return c*-1
class ErrorCodes:
	pass
class Herbrand:
	#input
	#P1x1x2 f1(
	#
	def get_input(self,input):
		result=[]
		ip=input.split('\n')
		for i in ip:
			result.append(Clause(i))
	def __init__(self,cl):
		self.cl=cl
		self.__domain=0
	def get_domain(self):
		if(self.__domain==0):
			
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
				return ((cl1+cl2)-p)-Clause.negate(p)
	def solve(self):
		for(