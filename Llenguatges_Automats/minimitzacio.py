# def minimize(self):
	
# class Automate:
	# def __init__(self,states=[],inital=[],final=[]):
		# self.states=states
		# self.ini=initial
		# self.final=final
# class State:
	# def __init__(self,id,in=[],out=[]):
		# self.id=id
		# self.in=in
		# self.out=out
# class FinalState(State):
	# pass
# class StartState(State):
	# pass

# def usr_input():
	# pass
	
	
	
def contains(trans,transLst):
	for i in transLst:
		if trans[0]
class State:
	MAX_GROUP=0
	def __init__(self,name,group=0,transactions=[]):
		self.name=name
		self.transactions=transactions
		self.group=group
		if group>MAX_GROUP:
			MAX_GROUP+=1
	def equals(self,obj,states):
		if self.group=obj.group and len(self.transactions)==len(obj.transactions)
			for i in range(len(self.transactions)):
				if not contains(obj.transactions[i],self.transactions):
					
				# if states[self.transactions[i].name].group==states[obj.transactions[i].name]
	
class AFD:
	
	def __init__(self,start,states,end):
		self.start=start
		self.end=end
		self.states=states
	def minimize(self,groups):
		groups=[]
		diferences=False
		groups.append(self.start)
		groups.append(self.end)
		groups.append(self.stats.keys-(self.end-self.start))
		for g in groups:
			check_group(g,groups-g)
	def get_state_group(self,state):
		return self.states[state].group
	def check_group(self,group,others):
		for i in range(len(group)):
			pass
	def check_states(self,nState1,nState2):
		state1=self.states[nState1]
		state2=self.states[nState2]
		return state1.equals(state2)
			
def parse_sates(string):
	data=string.split(',')
	out={}
	for l in data:
		out[l]=State(l)
	return out
def parse_transitions(states,string):
	data=string.split(',')
	for l in data:
		name,dest,val=l.split(' ')
		states[name].transactions.append((val,dest))#State(dest,val)
	for i in states:
		states[i].transactions.sort(key = lambda x: (-x[0], -x[1]) )
def parse_state_type(string,states):
	data=string.split(',')
	s=data[0].split(' ')
	e=data[1].split(' ')
	for st in s:
		states[st].group=1
	for st in e:
		states[st].group=2
	return s,e
def parse(string):
	data=string.split('\n')
	states=parse_states(data[0])
	parse_transitions(states,data[1])
	s,e=parse_state_type(data[2],states)
	return AFD(s,states,e)