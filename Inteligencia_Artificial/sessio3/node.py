class Node:
    def __init__(self, _state, _parent=None, _action=None, _cost=0):
        self.state = _state
        self.parent = _parent
        self.action = _action
        self.cost = _cost

    def total_path(self):

        o=self.parent
        out=[self.action]
        while o.parent is not None:
            out.append(o.action)
            o=o.parent
        return out[::-1]
        # if self.parent is None:
            # return []
        # return self.parent.total_path()+[self.action]
    
    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return f'Node[{self.state,self.action,self.cost}]'
        return 'Node[{},{},{}]'.format(self.state,self.action,self.cost)


def test_robot():
    # For the problem of the robot cleaning two cells
    from collections import namedtuple
    State = namedtuple("State", "cell clean0 clean1")
    
    root = Node(State(0, False, False))
    step1 = Node(
        State(0, True, False),
        root, "SWEEP"
    )
    step2 = Node(
        State(1, True, False),
        step1, "MOVE"
    )
    step3_1 = Node(
        State(0, True, False),
        step2, "MOVE"
    )
    step3_2 = Node(
        State(1, True, True),
        step2, "SWEEP"
    )

    # print([root,step1])
    # print(step1)
    print(step3_1.total_path())
    print(step3_2.total_path())


if __name__ == "__main__":
    test_robot()
