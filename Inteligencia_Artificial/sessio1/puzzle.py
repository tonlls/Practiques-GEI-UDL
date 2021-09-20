import random,copy
from enum import Enum
class Grid:
	def __init__(self, values):
		self.grid=values


	def _get_index(self, x, y):
		"""Return the offset in the internal array for the x,y position"""
		return x+(y*3)
		# raise NotImplementedError

	def get_value(self, x, y):
		"""Return the value for the cell x,y"""
		return self.grid[self._get_index(x, y)]

	def set_value(self, x, y, value):
		"""Update the value for the cell x,y"""
		self.grid[self._get_index(x, y)] = value

	def print_grid(self):
		print("-------")
		for y in range(3):
			for x in range(3):
				print("|" + str(self.get_value(x, y)), end="")
			print("|")
			print("-------")

	def find_value(self, value):
		"""
		Return the x,y coordinates for the first cell
		with the desired value
		"""
		index=self.grid.index(value)
		if index is not None:
			x=index%3
			y=int(index/3)
			return x,y
		return None
		# raise NotImplementedError

	def iterate_by_rows(self):
		"""
		Return all the values in the grid from left to right
		and top to bottom
		"""
		return iter([[self.grid[:3]],
					 [self.grid[2:6]],
					 [self.grid[5:]]])
		# raise NotImplementedError
	
	def deep_copy(self):
		return Grid([i for i in self.grid])

class Actions(Enum):
	def __str__(self):
		return self.name
	LEFT=1
	UP=2
	DOWN=3
	RIGHT=4

class Environment:
	"""
	Represent the 8-puzzle problem
	"""
	EMPTY=' '
	def __init__(self):
		grid=list(range(1,9))+[self.EMPTY]
		random.shuffle(grid)
		self.state = Grid(grid)
		# self.state = Grid([1,2,3,4,5,8,6,7,self.EMPTY])

	def get_available_actions(self):
		"""Return the available actions depending on the current state"""
		# return Actions
		actions=[a for a in Actions]
		ix,iy=self.state.find_value(self.EMPTY)
		if ix==0:
			actions.remove(Actions.LEFT)
		if ix==2:
			actions.remove(Actions.RIGHT)
		if iy==0:
			actions.remove(Actions.UP)
		if iy==2:
			actions.remove(Actions.DOWN)
		return actions

	def get_state(self):
		"""Return the current state of the problem"""
		# TODO: ensure that we return an inmutable object or a copy
		#  of the state to avoid future problems.
		# return copy.deepcopy(self.state)
		return self.state.deep_copy()

	def step(self, action):
		"""
		Apply a time step. This is apply an action
		and update the state accordingly
		"""
		ox,oy=self.state.find_value(self.EMPTY)
		if action == Actions.UP:
			nx,ny=ox,oy-1
		elif action == Actions.DOWN:
			nx,ny=ox,oy+1
		elif action == Actions.LEFT:
			nx,ny=ox-1,oy
		elif action == Actions.RIGHT:
			nx,ny=ox+1,oy
		old=self.state.get_value(nx,ny)
		self.state.set_value(ox,oy,old)
		self.state.set_value(nx,ny,self.EMPTY)

	def is_finished(self):
		"""
		Check if the puzzle is solved.
		Consider it solved when, going from left to right and from top
		to bottom, the values we find in the cells are increasing. The
		empty cell is ignored.
		"""
		state=self.get_state().grid
		state.remove(self.EMPTY)
		return state==list(range(1,9))
		
	def render(self):
		self.state.print_grid()


def get_action_from_stdin(available_actions):
	"""
	Asks for user input to enter a number that represents the action to take
	in the next step.
	"""
	actions = {a.value: a for a in available_actions}
	while True:
		try:
			action = int(input("Enter action: "))
		except ValueError as e:
			continue

		try:
			return actions[action]
		except KeyError:
			continue


def main():
	env = Environment()

	while not env.is_finished():
		env.render()

		# Agent behaviour:
		state = env.get_state()
		actions = env.get_available_actions()
		print(actions)

		action = get_action_from_stdin(actions)
		print(action)
		env.step(action)
		# End agent behaviour

	print("FINISHED")
	env.render()


if __name__ == "__main__":
	main()