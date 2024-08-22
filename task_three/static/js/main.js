document.getElementById('investment-form').addEventListener('submit', function (e) {
    e.preventDefault();

    const symbol = document.getElementById('symbol').value.toUpperCase();
    const amountSpent = parseFloat(document.getElementById('amount_spent').value);
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
            fetchCurrentPriceAndAddToPortfolio(symbol, amountSpent, dateBought, data.amount_gained);
        } else {
            alert(`Error: ${data.error}`);
        }
    })
    .catch(error => {
        alert('Error: Something went wrong!');
    });
});

let totalProfitOrLoss = 0;

function fetchCurrentPriceAndAddToPortfolio(symbol, amountSpent, dateBought, profitOrLoss) {
    fetch(`/current-price?symbol=${symbol}`)
    .then(response => response.json())
    .then(data => {
        if (data.success) {
            const currentPrice = data.current_price;
            const amountGained = currentPrice - amountSpent;
            totalProfitOrLoss += amountGained;

            addStockToPortfolio(symbol, amountSpent, dateBought, currentPrice, amountGained);
            updateTotalProfitLoss();
        } else {
            alert(`Error: ${data.error}`);
        }
    })
    .catch(error => {
        alert('Error fetching current price.');
    });
}

function addStockToPortfolio(symbol, amountSpent, dateBought, currentPrice, profitOrLoss) {
    const portfolioTable = document.getElementById('portfolio-table').getElementsByTagName('tbody')[0];
    const newRow = portfolioTable.insertRow();

    newRow.innerHTML = `
        <td>${symbol}</td>
        <td>$${amountSpent.toFixed(2)}</td>
        <td>${dateBought}</td>
        <td>$${currentPrice.toFixed(2)}</td>
        <td>$${profitOrLoss.toFixed(2)}</td>
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
