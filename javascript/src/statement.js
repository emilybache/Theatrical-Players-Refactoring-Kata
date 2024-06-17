const createStatementData = require("./createStatementData");

function statement (invoice, plays) {
    const statementData = createStatementData(invoice, plays);
    return renderPlainText(statementData);
}


function renderPlainText(data) {
    let result = `Statement for ${data.customer}\n`;
    for (let perf of data.performances) {
        // print line for this order
        result += ` ${perf.play.name}: ${(usd(perf.amount))} (${perf.audience} seats)\n`;
    }
    result += `Amount owed is ${usd(data.totalAmount)}\n`;
    result += `You earned ${(data.totalVolumeCredits)} credits\n`;
    return result;

    function usd(number) {
        return new Intl.NumberFormat("en-US",
            {
                style: "currency", currency: "USD",
                minimumFractionDigits: 2
            }).format(number / 100);
    }

}

function renderHtml(data) {
    // TODO
}

module.exports = statement;
