

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

function createResultStatement(_invoice, _plays, _calculatedObject) {
    let result = `Statement for ${_invoice.customer}\n`;
    result += createPlayDescriptionStatement(_invoice.performances, _plays);
    result += `Amount owed is ${USDFormatting(_calculatedObject.totalAmount/100)}\n`;
    result += `You earned ${_calculatedObject.volumeCredits} credits\n`;
    return result;
}

function createPlayDescriptionStatement(performances, plays) {
    let playDescriptionStatement = '';
    for (let performance of performances) {
        const play = plays[performance.playID];
        playDescriptionStatement += ` ${play.name}: ${USDFormatting(getAmountByPlayType(play.type, performance.audience) / 100)} (${performance.audience} seats)\n`;
    }
    return playDescriptionStatement;
}

function createCalculatedObject(invoice, plays) {
    /* Block scoped variables cannot share name with 'var' variables or parameters in the same block scope */
    let totalAmount = 0;
    let volumeCredits = 0
    for (let perf of invoice.performances) {
        const play = plays[perf.playID];
        volumeCredits += getVolumeCredits(play.type, perf.audience);
        totalAmount += getAmountByPlayType(play.type, perf.audience);
    }
    return {volumeCredits, totalAmount};
}

function statement (invoice, plays) {
    return createResultStatement(invoice, plays, createCalculatedObject(invoice, plays));
}

module.exports = statement;
