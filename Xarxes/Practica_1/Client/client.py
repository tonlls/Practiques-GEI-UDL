import argparse
import socket

DEBUG = True
def debug(text,error=False):
	if DEBUG:
		if error:
			print('ERROR: '+text)
		else:
			print('DEBUG: '+text)

class Config:
	def __init__(self,id,mac,server,udp_port,cfg_file='boot.cfg'):
		self.id=id
		self.mac=mac
		self.server=server
		self.udp_port=udp_port
		self.tcp_port=None
		self.cfg_file=cfg_file
	@staticmethod
	def parseConfig(file):
		with open(file) as f:
			linesin = f.readlines()
			lines={}
			for l in linesin:
				tmp=l.split(' ')
				lines[upper(tmp[0])]=tmp[1]
			return Config(lines['ID'],lines['MAC'],lines['SERVER'],lines['SRV-PORT'])	

class PDU:		
	types={
		'REGISTER_REQ': '0x10',
		'REGISTER_ACK': '0x11',
		'REGISTER_NACK':'0x12',
		'REGISTER_REJ': '0x13',
		'ERROR':        '0x19',
		'ALIVE_INF':    '0x20',
		'ALIVE_ACK':    '0x21',
		'ALIVE_NACK':   '0x22',
		'ALIVE_REJ':    '0x23',
		'PUT_FILE':     '0x30',
		'PUT_DATA':     '0x31',
		'PUT_ACK':      '0x32',
		'PUT_NACK':     '0x33',
		'PUT_REJ':      '0x34',
		'PUT_END':      '0x35',
		'GET_FILE':     '0x40',
		'GET_DATA':     '0x41',
		'GET_ACK':      '0x42',
		'GET_NACK':     '0x43',
		'GET_REJ':      '0x44',
		'GET_END':      '0x45'
	}
	@staticmethod
	def get_type(str,value=True):
		if value:
			return PDU.types[str]
		else :
			return PDU.types.keys()[PDU.types.values().index(str)]
	def __init__(self,type,id,mac,num,data):
		self.type=type
		self.id=id
		self.mac=mac
		self.num=num
		self.data=data
	def get_str(self):
		return self.type+self.id+'\0'+self.mac+'\0'+self.num+'\0'+self.data+'\0'
	@staticmethod
	def from_conf(conf,type,num,data):
		return PDU(type,conf.id,conf.mac,num,data)
	@staticmethod
	def parse_str(str):#########################################################
		st=''
		j=4
		data=[]
		data.append(str[0:4])
		str=str[4:]
		data+=str.split('\0')
		'''for i in range(0,len(str)):
			if j==0:
				break
			if(str[i]=='\0'):
				data.append(st)
				j-=1
				st=''
			else:
				st+=str[i]'''
		# print(data)
		return PDU(data[0],data[1],data[2],data[3],data[4])
class TCP:
	# TODO:repair size
	MSG_SIZE=20
	# TODO:make config global var
	def __init__(self,config):
		self.config=config
	def connect(self):###############################################################################################
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		# Connect the socket to the port where the server is listening
		self.server_address = (config.tcp_server, 10000)
		print('connecting to {} port {}'.format(*server_address))
		self.sock.connect(server_address)
	def send_file(self,filename):
		lines=None
		with f=open(filename,'r'):
			lines=f.readlines()
		p=PDU.from_conf(self.config,)
		for l in lines:
			p.data=l
			self.send(p)
		p.data=''
		p.type=PDU.get_type('PUT_END')
		self.send(p)
	def recive_file(self,filename):
		end=False
		with f=open(filename,'w'):
			while(not end):
				p=self.recive()
				if p.type==PDU.get_type(''):
					end=True
				else:
					f.write(p.data)
		# //TODO:to end
		self.send(PDU.from_conf(self.conf,PDU.get_type('END'),))
		pass
	def send(self,pdu):
		self.sock.send(pdu.get_str().encode())
		debug('TCP message sent')
	def recive(self):
		r=self.sock.recv(MSG_SIZE)
		debug('TCP message recived')
		return PDU.parse_str(r)
	def close(self):
		self.sock.close()
class UDP:
	# TODO:repair size
	MSG_SIZE=10
	n=3
	t=1
	m=3
	p=7
	s=2
	q=2
	def __init__(self,config):
		self.config=config
	def connect(self):
		self.socket=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		debug('Connected to UDP server')
	def send(self,pdu):
		#maybe port =0????
		self.socket.sendto(pdu.get_str().encode(), (self.config.server,self.config.port))
		debug('UDP message sent')
	def recive(self,timeout=None):
		if timeout!=None:
			self.socket.settimeout(timeout)
		data,addr=self.socket.recvfrom(self.config.port)
		if timeout!=None:
			self.socket.settimeout(None)
		debug('UDP message recived')
		# maybe decode???
		if data==None:
			return None
		return PDU.parse_str(data)
	def close(self):
		self.socket.close()
		debug('UDP server closed')
	def reg_req(self):
		p=PDU(PDU.get_type('REGISTER_REQ'),self.config.id,self.config.mac,000000,"")
		data=None
		n=0
		m=UDP.m
		t=UDP.t
		while  and data==None 
			while n<UDP.p and data==None:
				self.send(p)
				data=self.recive(t)
				if n>=PDU.n and t<UDP.t*UDP.m:
					t+=t
				else:
					n+=1
		pass
class Comands:
	# sned a config file to the server
	def put_cfg(conn,config):
		len=os.path.getsize(config.cfg_file)
		s=config.cfg_file+','+str(len)
		conn.send(PDU(PDU.get_type('PUT_FILE'),config.id,config.mac,'00000',s))
		pass
	# read config file from the server
	def get_cfg():
		conn.read()
		pass
	# 
	def quit(u,t):
		pass

def pprint(stri):
	st=''
	j=4
	for i in range(len(stri)):
		if j==0:
			break
		if(chr(stri[i])=='\0'):
			print(st)
			j-=1
			st=''
		else:
			st+=chr(stri[i])

def init():
	parser = argparse.ArgumentParser()
	parser.add_argument('-c',default='client.cfg',type=str)
	# parser.add_argument('-d',default='client.cfg',type=str)
	args = parser.parse_args()
	config=Config.parseConfig(args.c)

# TODO:add a fork for udp client and a fork for tcp
# init()
u=UDP(Config("000001","111111111111",'127.0.0.1',5055))
u.connect()
u.send(PDU(PDU.get_type('REGISTER_ACK'),u.config.id,u.config.mac,'000000','adeu puta'))
a=u.recive()