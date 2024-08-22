import yfinance as yf
from datetime import datetime
import json
import pprint
import matplotlib.pyplot as plt

class Stock():
    def __init__(self, ticker, username, amount_spend,purchase_date):
        self.ticker = ticker
        self.current_price = None
        self.unit = None
        self.amount_spend = amount_spend
        self.current_value = None
        self.purchase_date = purchase_date
        self.gain_loss_dollar = None
        self.gain_loss_percentage = None
        self.purchase_price = None

    def fetch_purchase_price(self):
        stock = yf.Ticker(self.ticker)
        purchase_date = datetime.strptime(self.purchase_date.strip(), '%Y-%m-%d %H:%M:%S')
        historical_data = stock.history(start= purchase_date)
        purchase_price = historical_data['Close'].iloc[0]
        self.purchase_price = purchase_price
        print(purchase_price)
        self.unit = float(self.amount_spend) / float(purchase_price)
        return self.unit

    def fetch_current_price(self):#fetch current
        stock = yf.Ticker(self.ticker)
        self.current_price = stock.history(period = '1d')['Close']
        return self.current_price

    def get_current_value(self): #get the current value of the stock
        self.fetch_current_price()
        self.fetch_purchase_price()
        self.current_value = self.unit * self.current_price
        return self.current_value

    def profit_loss(self):
        self.get_current_value()
        gain_loss = float(self.current_value.iloc[0]) - float(self.amount_spend)
        gain_loss_percentage = float(self.current_price.iloc[0]) /float(self.amount_spend)
        self.gain_loss_dollar = round(gain_loss,2)
        self.gain_loss_percentage = round(gain_loss_percentage,2)
        return self.gain_loss_dollar, gain_loss_percentage


    def process(self):
        self.fetch_purchase_price()
        self.fetch_current_price()
        self.get_current_value()
        self.profit_loss()
        return self.unit, self.purchase_price, self.purchase_date, self.ticker, self.current_price, self.unit, self.amount_spend, self.current_value, self.gain_loss_percentage,self.gain_loss_dollar


    def test(self):
        stock = yf.Ticker(self.ticker)
        purchase_date = datetime.strptime(self.purchase_date, '%Y-%m-%d %H:%M:%S')
        historical_data = stock.history(start= purchase_date)
        data_dict = historical_data.reset_index().to_dict(orient='records')
         #Convert the dictionary to a JSON string
        json_data = json.dumps(data_dict, indent=4, default=str)
        print(json_data)
        plt.figure(figsize=(10, 6))
        plt.plot(historical_data.index, historical_data['Close'], label='Close Price', color='blue', marker='o')
        filename  = 'C:/Users/yokong01/OneDrive - Arm/Desktop/hackathon/data.json'





stock = Stock('SNOW','Yok', '1231','2024-08-05 08:15:30')

stock.test()


