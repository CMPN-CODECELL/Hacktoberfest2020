import os
import numpy as np
from keras.preprocessing.image import ImageDataGenerator, load_img, img_to_array
from keras.models import Sequential, load_model
import time
from keras import backend as K


#Prediction Function
def predict(model1, file):

    img_width, img_height = 300,300
    x = load_img(file, target_size=(img_width,img_height))
    x = img_to_array(x)
    x = np.expand_dims(x, axis=0)
    array = model1.predict(x)
    result = array[0]
    #print(result)
    answer = np.argmax(result)
    return answer


if __name__ == "__predict__":
    predict()
