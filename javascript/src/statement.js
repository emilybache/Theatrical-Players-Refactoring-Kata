
function statement (invoice, plays) {
    const statementData = {};
    statementData.customer = invoice.customer;
    return renderPlainText(statementData, invoice, plays);
}


function renderPlainText(data, invoice, plays) {
    let result = `Statement for ${data.customer}\n`;
    for (let perf of invoice.performances) {
        // print line for this order
        result += ` ${playFor(perf).name}: ${(usd(amountFor(perf)))} (${perf.audience} seats)\n`;
    }
    result += `Amount owed is ${usd(totalAmount())}\n`;
    result += `You earned ${(totalVolumeCredits())} credits\n`;
    return result;

    function amountFor(aPerformance) {
        let result = 0;
        switch (playFor(aPerformance).type) {
            case "tragedy":
                result = 40000;
                if (aPerformance.audience > 30) {
                    result += 1000 * (aPerformance.audience - 30);
                }
                break;
            case "comedy":
                result = 30000;
                if (aPerformance.audience > 20) {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }
                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Error(`unknown type: ${playFor(aPerformance).type}`);
        }
        return result;
    }

    function playFor(perf) {
        return plays[perf.playID];
    }

    function volumeCreditsFor(perf) {
        let volumeCredits = 0;
        volumeCredits += Math.max(perf.audience - 30, 0);
        if ("comedy" === playFor(perf).type) {
            volumeCredits += Math.floor(perf.audience / 5);
        }
        return volumeCredits;
    }

    function usd(number) {
        return new Intl.NumberFormat("en-US",
            {
                style: "currency", currency: "USD",
                minimumFractionDigits: 2
            }).format(number / 100);
    }

    function totalVolumeCredits() {
        let volumeCredits = 0;
        for (let perf of invoice.performances) {
            volumeCredits += volumeCreditsFor(perf);
        }
        return volumeCredits;
    }

    function totalAmount() {
        let totalAmount = 0;
        for (let perf of invoice.performances) {
            totalAmount += amountFor(perf);
        }
        return totalAmount;
    }
}


module.exports = statement;
