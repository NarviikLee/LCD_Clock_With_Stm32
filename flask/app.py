from flask import Flask,render_template
from flask_pymongo import PyMongo

app = Flask(__name__)
app.config["MONGO_URI"] = "Monggo_URI"
mongo = PyMongo(app)

@app.route('/')
def home():
    return "Hello, Flask with Nginx!"

@app.route('/about')
def about():
    devices = mongo.db.iot_devices.find({}, {"device_name": 1, "_id": 0})
    device_names = [device["device_name"] for device in devices]
    return render_template('device.html',device_names=device_names)

@app.route('/device/<device_name>')
def device_records(device_name):
    records = mongo.db.iot_devices.find_one({"device_name": device_name}, {"records": 1, "_id": 0})
    if records:
        return render_template('device_records.html', device_name=device_name, records=records['records'])
    else:
        return "Device not found", 404

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)

