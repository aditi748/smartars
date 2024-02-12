import pyrebase 
import time
from twilio.rest import Client

firebaseConfig={
  "apiKey": "AIzaSyBoWTjHfXefLrgiDNl6eN5KaHmRjGVn890",
  "authDomain": "smartantiragging.firebaseapp.com",
  "databaseURL": "https://smartantiragging-default-rtdb.firebaseio.com",
  "projectId": "smartantiragging",
  "storageBucket": "smartantiragging.appspot.com",
  "messagingSenderId": "852002737600",
  "appId": "1:852002737600:web:9e207d254bf8df79430c25",
  "measurementId": "G-34Z2H6HVHF"
}
firebase = pyrebase.initialize_app(firebaseConfig)
db = firebase.database()

account_sid = 'AC90776e3ce4c2ba62774f1105de0d3e7a'
auth_token = '0538252225f87ee810af4a7ea234b586'
client = Client(account_sid, auth_token)

def fetch_data_continuously():
    while True:
        data = db.get().val()
        name = data.get('NAME') 
        msg = "Help Me from" + name
        if data.get('POST') == 1:
            message = client.messages.create(
            from_='+17573048829',
            body=msg,
            to='+918100054772'
            )

            print(message.sid)
        print("Data fetched:", data.get('POST'))
        time.sleep(0.3)  

if __name__ == "__main__":
    fetch_data_continuously()









