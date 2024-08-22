from flask import Flask, render_template, request, jsonify
import yfinance as yf
from datetime import datetime

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/current-price')
def current_price():
    symbol = request.args.get('symbol').upper()
    stock = yf.Ticker(symbol)
    current_data = stock.history(period="1d")
    
    if current_data.empty:
        return jsonify({'success': False, 'error': 'Current price not available for the symbol'})

    current_price = current_data['Close'].iloc[0]
    return jsonify({'success': True, 'current_price': current_price})

@app.route('/calculate', methods=['POST'])
def calculate():
    symbol = request.form['symbol'].upper()
    amount_spent = float(request.form['amount_spent'])
    date_bought = request.form['date_bought']

    # Fetch historical stock data using yfinance
    stock = yf.Ticker(symbol)
    historical_data = stock.history(start=date_bought)

    print(f"Fetching data for symbol: {symbol} on date: {date_bought}")
    print(f"Data received: {historical_data}")

    if historical_data.empty:
        return jsonify({'success': False, 'error': 'Data not available for the given date or symbol'})

    close_price = historical_data['Close'].iloc[0]

    # Assuming the user bought 1 share
    amount_gained = close_price - amount_spent
    return jsonify({'success': True, 'amount_gained': amount_gained})

if __name__ == '__main__':
    app.run(debug=True)