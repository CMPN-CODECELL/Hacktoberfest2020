import pandas as pd
import numpy as np
import streamlit as st
from os import listdir
from os.path import isfile, join
from PIL import Image
import Training
import Testing
from keras.models import load_model
from keras import backend as K

showpred = 0
try:
	model_path = 'models/model.h5'
	model_weights_path = 'models/weights.h5'
except: 
	print("Need to train model")
test_path = 'Data/Test/'

#Load the pre-trained models
model = load_model(model_path)
model.load_weights(model_weights_path)
st.sidebar.title("About")

st.sidebar.info(
    "This is a demo application written to help you understand our idea. The application identifies the food with its quality in the picture. It is built using a Convolution Neural Network (CNN).")

onlyfiles = [f for f in listdir("Data/Test") if isfile(join("Data/Test", f))]

st.sidebar.title("Train Neural Network")
if st.sidebar.button('Train CNN'):
	Training.train()

st.sidebar.title("Predict New Images")
imageselect = st.sidebar.selectbox("Pick an image.", onlyfiles)
if st.sidebar.button('Predict Quality'):
    showpred = 1
    prediction = Testing.predict((model),"Data/Test/" + imageselect)


st.title('Food Quality Identification')
st.write("Pick an image from the left. You'll be able to view the image.")
st.write("When you're ready, submit a prediction on the left.")

st.write("")
image = Image.open("Data/Test/" + imageselect)
st.image(image, caption="Let's predict the food and its quality!", use_column_width=True)

if showpred == 1:
    if prediction == 0:
        st.write("This is a **Bread-Fresh!**")
    if prediction == 1:
        st.write("This is an **horse!**")
    if prediction == 2:
        st.write("This is a **elephant!**")
    if prediction == 3:
        st.write("This is a **butterfly!**")
    if prediction == 4:
        st.write("This is a **Carrot-Mouldy!**")
    if prediction == 5:
        st.write("This is a **cat!**")
    if prediction == 6:
        st.write("This is a **buffalo!**")
    if prediction == 7:
        st.write("This is a **Potato-Stale**")
    if prediction == 8:
        st.write("This is a **spider!**")
    if prediction == 9:
        st.write("This is a **squirrel!**")
    
