class CalculatePlayAmount{

    constructor(_plays,_invoice, _performance) {
        this.plays = _plays;
        this.invoice = _invoice;
        this.performance = _performance;
    }

    get amount() {
        throw new Error('하위 클래스에서 처리하도록 했습니다.');
    }

    get volumeCredits() {
        throw new Error('하위 클래스에서 처리하도록 했습니다.');
    }

    printStatement() {
        console.log(this.createResultStatement(this.invoice.performances, this.plays, this.createCalculatedObject(this.invoice, this.plays)))
        return this.createResultStatement(this.invoice.performances, this.plays, this.createCalculatedObject(this.invoice, this.plays));
    }

    USDFormatting(_number) {
        return new Intl.NumberFormat("en-US",
          {
              style: "currency", currency: "USD",
              minimumFractionDigits: 2
          }).format(_number / 100);
    }

    createResultStatement(_performances, _plays, _calculatedObject) {
        let result = `Statement for ${this.performance.playId}\n`;
        result += this.createPlayDescriptionStatement(_performances, _plays);
        result += `Amount owed is ${this.USDFormatting(_calculatedObject.totalAmount/100)}\n`;
        result += `You earned ${_calculatedObject.volumeCredits} credits\n`;
        return result;
    }

    createPlayDescriptionStatement(performances, plays) {
        let playDescriptionStatement = '';
        for (let performance of performances) {
            const play = plays[performance.playID];
            playDescriptionStatement += ` ${play.name}: ${this.USDFormatting(this.amount)} (${performance.audience} seats)\n`;
        }
        return playDescriptionStatement;
    }

     createCalculatedObject(invoice, plays) {
        let totalAmount = 0;
        let volumeCredits = 0
        for (let performance of invoice.performances) {
            volumeCredits += this.volumeCredits
            totalAmount += this.amount;
        }
        return {volumeCredits, totalAmount};
    }
}


class CalculatePlayAmountForTragedy extends CalculatePlayAmount {

    // constructor(_plays,_invoice, _performance) {
    //     super(_plays,_invoice, _performance);
    // }

    get amount() {
        return 40000 + (this.performance.audience > 30 ? 1000 * (this.performance.audience - 30) : 0)
    }

    get volumeCredits() {
        return Math.max(this.performance.audience - 30, 0);
    }
}



class CalculatePlayAmountForComedy extends CalculatePlayAmount {
    get amount() {
        return 30000 + (300 * this.performance.audience) + (this.performance.audience > 20 ? 10000 + 500 * (this.performance.audience - 20) : 0);

    }

    get volumeCredits() {
        return Math.max(this.performance.audience - 30, 0) + Math.floor(this.performance.audience / 5);
    }
}

function getPrintStatementByPlayType(_plays, _invoice, _performance) {
    const play = _plays[_performance.playID];
    switch (play.type) {
        case "tragedy":
            return new CalculatePlayAmountForTragedy(_plays,_invoice, _performance);
        case "comedy":
            return new CalculatePlayAmountForComedy(_plays,_invoice, _performance);
        default:
            throw new Error(`unknown type: ${play.type}`);
    }
}

function statement (invoice, plays) {

    for (let performance of invoice.performances) {

        let printStatementByPlayType = getPrintStatementByPlayType(plays, invoice, performance);
        printStatementByPlayType.printStatement();
    }

}


module.exports = statement;
