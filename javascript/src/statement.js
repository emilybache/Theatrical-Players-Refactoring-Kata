function getAmountByPlayType(playType, audience) {
    switch (playType) {
        case "tragedy":
            return 40000 + (audience > 30 ? 1000 * (audience - 30) : 0)
        case "comedy":
            return 30000 + (300 * audience) + (audience > 20 ? 10000 + 500 * (audience - 20) : 0);

        default:
            throw new Error(`unknown type: ${playType}`);
    }
}

function getVolumeCredits(playType, audience) {
    return Math.max(audience - 30, 0) + ("comedy" === playType ? Math.floor(audience / 5) : 0);
}

function USDFormatting(_number) {
    return new Intl.NumberFormat("en-US",
      {
          style: "currency", currency: "USD",
          minimumFractionDigits: 2
      }).format(_number);
}

function statement (invoice, plays) {
    let totalAmount = 0;
    let volumeCredits = 0;
    let result = `Statement for ${invoice.customer}\n`;

    for (let perf of invoice.performances) {
        const play = plays[perf.playID];
        let thisAmount = 0;
        thisAmount = getAmountByPlayType(play.type, perf.audience);
        // add volume credits
        volumeCredits += getVolumeCredits(play.type, perf.audience);
        // print line for this order
        result += ` ${play.name}: ${USDFormatting(thisAmount/100)} (${perf.audience} seats)\n`;
        totalAmount += thisAmount;
    }

    result += `Amount owed is ${USDFormatting(totalAmount/100)}\n`;
    result += `You earned ${volumeCredits} credits\n`;
    return result;
}

module.exports = statement;
