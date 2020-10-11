import streamlit as st
import pandas as pd
import numpy as np
import plotly.express as px
from plotly.subplots import make_subplots
import plotly.graph_objects as go
from wordcloud import WordCloud, STOPWORDS
import matplotlib.pyplot as plt


DATA_URL = ("database1234.csv")

st.title("Analysis of Bird Strikes")
st.sidebar.title("Bird Strike analysis")
st.markdown("This application is a Streamlit dashboard used "
            "to analyze the Bird Strike occurence data")
st.sidebar.markdown("This application is a Streamlit dashboard used "
            "to analyze the Bird Strike occurence data")

@st.cache(persist=True)
def load_data():
    data = pd.read_csv(DATA_URL)
    #data['tweet_created'] = pd.to_datetime(data['tweet_created'])
    return data

data = load_data()
'Dataset Preview',data


#st.sidebar.subheader("Filter as per choice")
#cause_damage = st.sidebar.radio('Damage Caused', ('Caused damage', 'No damage'))
#st.sidebar.markdown(data.query("Indicated_Damage == @cause_damage")[["Indicated_Damage"]].sample(n=1).iat[0, 0])



st.sidebar.markdown("### Number of birdstrikes differentiated by damage")

select = st.sidebar.selectbox('Visualization type', ['Bar plot', 'Pie chart'], key='1')
flight_count = data['Indicated_Damage'].value_counts()
flight_count = pd.DataFrame({'Damage Caused':flight_count.index, 'No of flights':flight_count.values})
if not st.sidebar.checkbox("Hide", True):
    st.markdown("## Number of flights by damage")
    st.markdown("The following graph gives information regarding the number of flights in which damage was caused")
    if select == 'Bar plot':
        fig = px.bar(flight_count, x='Damage Caused', y='No of flights', color='No of flights', height=500)
        st.plotly_chart(fig)
    else:
        fig = px.pie(flight_count, values='No of flights', names='Damage Caused')
        st.plotly_chart(fig)


values = st.sidebar.slider("Price", str(data.Year.min()), '2015', ('2005', '2015'))
f = px.histogram(data.query(f"Year.between{values}"), x="Year", nbins=15, title="Price distribution")
f.update_xaxes(title="Price")
f.update_yaxes(title="No. of listings")
st.plotly_chart(f)

















#st.sidebar.subheader("Breakdown airline by phase")
#choice = st.sidebar.multiselect('Pick Damage', ('Caused damage', 'No damage'), key=0)
#if len(choice) > 0:
 #   choice_data = data[data.Indicated_Damage.isin(choice)]
  #  fig_0 = px.histogram(choice_data, x='Indicated_Damage', y='airline_phase',histfunc='count', color='airline_phase',facet_col='airline_phase',labels={'airline_phase':'Phases'}, height=600, width=800)
   # st.plotly_chart(fig_0)


#if st.checkbox('Show raw data'):
    
    
#sentence = st.text_input('Input your sentence here:')
#vidya.premkumarr@gmail.com



