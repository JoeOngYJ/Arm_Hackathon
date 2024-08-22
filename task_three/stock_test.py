import yfinance as yf
from datetime import datetime

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
        purchase_date = datetime.strptime(self.purchase_date.strip(), '%Y-%m-%d')
        historical_data = stock.history(start= purchase_date)
        purchase_price = historical_data['Close'].iloc[0]
        self.purchase_price = float(purchase_price)
        self.unit = float(self.amount_spend) / float(purchase_price)
        return self.unit
    def fetch_current_price(self):#fetch current
        stock = yf.Ticker(self.ticker)
        purchase_date = datetime.strptime(self.purchase_date.strip(), '%Y-%m-%d')
        current_price = stock.history(start= purchase_date)
        self.current_price = float(current_price['Close'].iloc[-1])
        return self.current_price
    def get_current_value(self): #get the current value of the stock
        self.fetch_current_price()
        self.fetch_purchase_price()
        self.current_value = self.unit * self.current_price
        return self.current_value
    def profit_loss(self):
        self.get_current_value()
        gain_loss = float(self.current_value) - float(self.amount_spend)
        gain_loss_percentage = float(self.current_price) /float(self.amount_spend)
        self.gain_loss_dollar = round(gain_loss,2)
        self.gain_loss_percentage = round(gain_loss_percentage,2)
        return self.gain_loss_dollar, gain_loss_percentage
    def process(self):
        self.fetch_purchase_price()
        self.fetch_current_price()
        self.get_current_value()
        self.profit_loss()
        self.unit = round(self.unit,2)
        self.purchase_price = round(self.purchase_price, 2)
        self.current_price = round(self.current_price,2)
        self.current_value = round(self.current_value,2)
        return self.unit, self.purchase_price, self.purchase_date, self.ticker, self.current_price, self.unit, self.amount_spend, self.current_value, self.gain_loss_percentage,self.gain_loss_dollar


stock = Stock('SNOW','kjsahd', '1233','2021-08-21')
unit, purchase_price, purchase_date, ticker, current_price, unit, amount_spend, current_value, gain_loss_percentage, gain_loss_dollar = stock.process()

print(unit, purchase_price, purchase_date, ticker, current_price, unit, amount_spend, current_value, gain_loss_percentage, gain_loss_dollar)