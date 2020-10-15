
# Welcome to Streamlit :


**Deployment of a Streamlit project on Heroku**

## Pre-requisite

```
pip install pipreqs

```

**Step 1: Open the terminal in your project folder and type**

```
pipreqs
```
A file named requirement.txt would be created

It should contain libraries and their versions in the following format:

streamlit==0.49.0
pandas==0.23.4

 **Step 2: setup.sh and Procfile**

Create the setup.sh file in your project folder using nano command through terminal 

```
nano setup.sh
```
Paste the following code into it 

 mkdir -p ~/.streamlit/ echo " [server]\n headless = true\n enableCORS=false\n port = $PORT\n \n " > ~/.streamlit/config.toml 


Create the Procfile file in your project folder using nano command through terminal 
(Procfile should be written as it is - case sensitive)

```
nano Procfile
```

Paste the following code into it
 web: sh setup.sh && streamlit run your_app.py


This works like a charm.

By running heroku logs --tail you can check any errors that you encounter while deploying
