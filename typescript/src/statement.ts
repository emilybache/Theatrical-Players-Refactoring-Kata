//змінила назву типу Plays на Play, оскільки це відображає сутність одного об'єкта
//замість використання інтерфейсу { [key: string]: { name: string; type: string } } я використала тип Record<string, Play>, це зручний шлях визначити об'єкт, в якому ключі є рядками, а значеннями є об'єкти типу Play
//винесла форматування суми грошей у власну функцію formatAmount, що спрощує його використання
//розділила розрахунок суми кожної вистави на окрему функцію calculateAmount це покращує читабельність коду та полегшує додавання нових типів вистав
//внесла розрахунок кількості бонусних балів у функцію calculateVolumeCredits це дозволяє легко розширити правила обчислення бонусних балів для різних типів вистав
//замінила цикл for...of на for...in, оскільки for...of не підтримує об'єкти типу Record<string, T> без додаткових операцій
//замінила використання let на const для змінних, які не змінюються всередині циклу
//замінила рядкове порівняння "comedy" === play.type на playType === "comedy" у функції calculateVolumeCredits, щоб уникнути повторення





type Play = {
  name: string;
  type: string;
};

type Performance = {
  playID: string;
  audience: number;
};

type Invoice = {
  customer: string;
  performances: Performance[];
};

function statement(invoice: Invoice, plays: Record<string, Play>) {
  let totalAmount = 0;
  let volumeCredits = 0;
  let result = `Statement for ${invoice.customer}\n`;

  const formatAmount = (amount: number) => {
    return new Intl.NumberFormat("en-US", {
      style: "currency",
      currency: "USD",
      minimumFractionDigits: 2,
    }).format(amount / 100);
  };

  const calculateAmount = (play: Play, audience: number) => {
    let amount = 0;
    switch (play.type) {
      case "tragedy":
        amount = 40000;
        if (audience > 30) {
          amount += 1000 * (audience - 30);
        }
        break;
      case "comedy":
        amount = 30000;
        if (audience > 20) {
          amount += 10000 + 500 * (audience - 20);
        }
        amount += 300 * audience;
        break;
      default:
        throw new Error(`Unknown type: ${play.type}`);
    }
    return amount;
  };

  const calculateVolumeCredits = (audience: number, playType: string) => {
    let credits = Math.max(audience - 30, 0);
    if (playType === "comedy") {
      credits += Math.floor(audience / 5);
    }
    return credits;
  };

  for (const perf of invoice.performances) {
    const play = plays[perf.playID];
    const thisAmount = calculateAmount(play, perf.audience);
    const playCredits = calculateVolumeCredits(perf.audience, play.type);

    result += ` ${play.name}: ${formatAmount(thisAmount)} (${perf.audience} seats)\n`;
    totalAmount += thisAmount;
    volumeCredits += playCredits;
  }

  result += `Amount owed is ${formatAmount(totalAmount)}\n`;
  result += `You earned ${volumeCredits} credits\n`;
  return result;
}

export { statement };

