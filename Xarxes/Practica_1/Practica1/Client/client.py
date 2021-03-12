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
	def __init__(self,id,mac,server,port):
		self.id=id
		self.mac=mac
		self.server=server
		self.port=port
	@staticmethod
	def parseConfig(file):
		with open(file) as f:
			linesin = f.readlines()
			lines={}
			for l in linesin:
				tmp=l.split(' ')
				lines[upper(tmp[0])]=tmp[1]
			return Config(lines['ID'],lines['MAC'],lines['SERVER'],lines['SRV-PORT'])	
class TCP:
	def __init__(self):
		pass
	def connect(self):
		pass
	def send(self):
		pass
	def recive(self):
		pass
	def close(self):
		pass
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
	def parse_str(str):
		st=''
		j=4
		data=[]
		data.append(str[0:4])
		str=str[4:]
		for i in range(0,len(str)):
			if j==0:
				break
			if(str[i]=='\0'):
				data.append(st)
				j-=1
				st=''
			else:
				st+=str[i]
		# print(data)
		return PDU(data[0],data[1],data[2],data[3],data[4])
class UDP:
	def __init__(self,config):
		self.config=config
	def connect(self):
		self.socket=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		debug('Connected to UDP server')
	def send(self,pdu):
		self.socket.sendto(pdu.get_str().encode(), (self.config.server,self.config.port))
		debug('UDP message sent')
	def recive(self):
		data,addr=self.socket.recvfrom(self.config.port)
		debug('UDP message recived')
		# maybe decode???
		return PDU.parse_str(data)
	def close(self):
		self.socket.close()
		debug('UDP server closed')
	def reg_req(self):
		pass
class Comands:
	# sned a config file to the server
	def put_cfg():
		pass
	# read config file from the server
	def get_cfg():
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
	args = parser.parse_args()
	config=parseConfig(args.c)

# TODO:add a fork for udp client and a fork for tcp
# init()
u=UDP(Config("000001","111111111111",'127.0.0.1',5055))
u.connect()
u.send(PDU(PDU.get_type('REGISTER_ACK'),u.config.id,u.config.mac,'00000','adeu puta'))
a=u.recive()