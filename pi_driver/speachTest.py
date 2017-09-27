import pyttsx3
engine = pyttsx3.init()
engine.say("I am Talking now ")
engine.setProperty('rate',100)
engine.runAndWait()
