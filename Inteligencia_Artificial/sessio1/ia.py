from keras.models import Sequential
from keras.layers import Dense
import tensorflow as tf
import puzzle
from sklearn.preprocessing import StandardScaler
class Ia:
    def __init__(self) -> None:
        self.env=puzzle.Environment()
        self.model = Sequential()
        self.model.add(Dense(12, input_dim=9, activation='relu',input_shape=(9,1)))
        # self.model.add(Dense(9, activation='relu'))
        self.model.add(Dense(1, activation='sigmoid'))
        self.model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
        self.x=[[1,2,3,4,5,0,7,8,6],[0,2,3,1,4,5,6,7,8]]
        self.y=[[3],[3]]
        #Normalizing the data
        # sc = StandardScaler()
        # self.x = sc.fit_transform(self.x)
        # self.y = sc.fit_transform(self.y)
        # train_data = tf.data.Dataset.from_tensor_slices((self.x, self.y))
        self.model.fit(self.x,self.y, epochs=150, batch_size=10)
        _, accuracy = self.model.evaluate(self.x, self.y)
        print('Accuracy: %.2f' % (accuracy*100))
    def run(self):
        while(not self.env.is_finished()):
            out=self.model.predict(self.env.get_state().grid)
            self.env.get_state().print_grid()
            print(out)
            break
if __name__=="__main__":
    Ia().run()