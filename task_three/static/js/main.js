document.getElementById('investment-form').addEventListener('submit', function (e) {
    e.preventDefault();

    const symbol = document.getElementById('symbol').value.toUpperCase();
    const amountSpent = document.getElementById('amount_spent').value;
    const dateBought = document.getElementById('date_bought').value;

    fetch('/calculate', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: `symbol=${symbol}&amount_spent=${amountSpent}&date_bought=${dateBought}`,
    })
    .then(response => response.json())
    .then(data => {
        if (data.success) {
            addStockToPortfolio(
                data.ticker,
                data.purchase_price,
                data.purchase_date,
                data.current_price,
                data.unit,
                data.amount_spent,
                data.current_value,
                data.gain_loss_percentage,
                data.gain_loss_dollar
            );
            updateTotalProfitLoss();
        } else {
            alert(`Error: ${data.error}`);
        }
    })
    .catch(error => {
        alert('Error: Something went wrong!');
    });
});

function addStockToPortfolio(ticker, purchasePrice, purchaseDate, currentPrice, units, amountSpent, currentValue, gainLossPercentage, gainLossDollar) {
    const portfolioTable = document.getElementById('portfolio-table').getElementsByTagName('tbody')[0];
    const newRow = portfolioTable.insertRow();

    newRow.innerHTML = `
        <td>${purchaseDate}</td>
        <td>${ticker}</td>
        <td>${units}</td>
        <td>$${amountSpent}</td>
        <td>$${currentPrice.toFixed(2)}</td>
        <td>$${purchasePrice.toFixed(2)}</td>
        <td>$${currentValue.toFixed(2)}</td>
        <td>${gainLossPercentage.toFixed(2)}%</td>
        <td>$${gainLossDollar.toFixed(2)}</td>
    `;
}
function updateTotalProfitLoss() {
    document.getElementById('total-profit-loss').innerText = `Total Profit/Loss: $${totalProfitOrLoss.toFixed(2)}`;
}

document.getElementById('clear-portfolio').addEventListener('click', function () {
    document.getElementById('portfolio-table').getElementsByTagName('tbody')[0].innerHTML = '';
    totalProfitOrLoss = 0;
    updateTotalProfitLoss();
});
