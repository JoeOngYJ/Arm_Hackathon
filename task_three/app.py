from flask import Flask, render_template, request, jsonify
import yfinance as yf
from datetime import datetime

app = Flask(__name__)

class Stock():
    def __init__(self, ticker, username, amount_spend, purchase_date):
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
        if isinstance(self.purchase_date, str):
            purchase_date = datetime.strptime(self.purchase_date.strip(), '%Y-%m-%d %H:%M:%S')
        else:
            purchase_date = self.purchase_date
        historical_data = stock.history(start=purchase_date)
        purchase_price = historical_data['Close'].iloc[0]
        self.purchase_price = float(purchase_price)
        self.unit = float(self.amount_spend) / float(purchase_price)
        return self.unit

    def fetch_current_price(self):
        stock = yf.Ticker(self.ticker)
        current_data = stock.history(period="1d")
        self.current_price = float(current_data['Close'].iloc[-1])
        return self.current_price
    
    def get_current_value(self):
        self.fetch_current_price()
        self.fetch_purchase_price()
        self.current_value = self.unit * self.current_price
        return self.current_value
    
    def profit_loss(self):
        self.get_current_value()
        gain_loss = float(self.current_value) - float(self.amount_spend)
        gain_loss_percentage = (gain_loss / float(self.amount_spend)) * 100
        self.gain_loss_dollar = round(gain_loss, 2)
        self.gain_loss_percentage = round(gain_loss_percentage, 2)
        return self.gain_loss_dollar, self.gain_loss_percentage
    
    def process(self):
        self.fetch_purchase_price()
        self.fetch_current_price()
        self.get_current_value()
        self.profit_loss()
        self.unit = round(self.unit, 2)
        self.purchase_price = round(self.purchase_price, 2)
        self.current_price = round(self.current_price, 2)
        self.current_value = round(self.current_value, 2)
        return self.unit, self.purchase_price, self.purchase_date, self.ticker, self.current_price, self.unit, self.amount_spend, self.current_value, self.gain_loss_percentage, self.gain_loss_dollar

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/calculate', methods=['POST'])
def calculate():
    symbol = request.form['symbol'].upper()
    amount_spent = request.form['amount_spent']
    date_bought = request.form['date_bought']
    time_bought = request.form['time_bought']

    datetime_bought = datetime.strptime(f"{date_bought} {time_bought}", '%Y-%m-%d %H:%M')
    time_bought = f"{time_bought}:00"
    datetime_bought = datetime.strptime(f"{date_bought} {time_bought}", '%Y-%m-%d %H:%M:%S')
    print('----------i',datetime_bought )
    stock = Stock(symbol, 'user', amount_spent, datetime_bought)
    unit, purchase_price, purchase_date, ticker, current_price, unit, amount_spent, current_value, gain_loss_percentage, gain_loss_dollar = stock.process()

    return jsonify({
        'success': True,
        'unit': unit,
        'purchase_price': purchase_price,
        'purchase_date': purchase_date,
        'ticker': ticker,
        'current_price': current_price,
        'amount_spent': amount_spent,
        'current_value': current_value,
        'gain_loss_percentage': gain_loss_percentage,
        'gain_loss_dollar': gain_loss_dollar
    })

if __name__ == '__main__':
    app.run(debug=True)