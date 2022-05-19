function statement(invoice, plays) {
  const customer = invoice.customer;
  const performances = invoice.performances;

  let totalAmount = 0;
  let volumeCredits = 0;
  let result = `Statement for ${customer}\n`;

  for (let perf of performances) {
    const audience = perf.audience;
    const play = plays[perf.playID];
    const playType = play.type;
    const playName = play.name;
    let thisAmount = 0;
    switch (playType) {
      case "tragedy":
        thisAmount = 40000;
        if (perf.audience > 30) {
          thisAmount += 1000 * (audience - 30);
        }
        break;
      case "comedy":
        thisAmount = 30000;
        if (perf.audience > 20) {
          thisAmount += 10000 + 500 * (audience - 20);
        }
        thisAmount += 300 * audience;
        break;
      default:
        throw new Error(`unknown type: ${playType}`);
    }
    // add volume credits
    volumeCredits += Math.max(audience - 30, 0);
    // add extra credit for every ten comedy attendees
    if ("comedy" === playType) volumeCredits += Math.floor(audience / 5);
    // print line for this order
    result += ` ${playName}: ${formatCurrency(
      thisAmount / 100
    )} (${audience} seats)\n`;
    totalAmount += thisAmount;
  }

  result += `Amount owed is ${formatCurrency(totalAmount / 100)}\n`;
  result += `You earned ${volumeCredits} credits\n`;
  return result;
}

function formatCurrency(amount) {
  return new Intl.NumberFormat("en-US", {
    style: "currency",
    currency: "USD",
    minimumFractionDigits: 2,
  }).format(amount);
}

module.exports = statement;
