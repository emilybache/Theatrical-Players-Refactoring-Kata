package theatre

import (
	"fmt"
	"math"

	"github.com/leekchan/accounting"
)

type StatementPrinter struct{}

func (StatementPrinter) Print(invoice Invoice, plays map[string]Play) (string, error) {
	totalAmount := 0
	volumeCredits := 0
	result := fmt.Sprintf("Statement for %s\n", invoice.Customer)

	ac := accounting.Accounting{Symbol: "$", Precision: 2}

	for _, perf := range invoice.Performances {
		play := plays[perf.PlayID]
		thisAmount := 0

		switch play.Type {
		case "tragedy":
			thisAmount = 40000
			if perf.Audience > 30 {
				thisAmount += 1000 * (perf.Audience - 30)
			}
		case "comedy":
			thisAmount = 30000
			if perf.Audience > 20 {
				thisAmount += 10000 + 500*(perf.Audience-20)
			}
			thisAmount += 300 * perf.Audience
		default:
			return "", fmt.Errorf("unknown type: %s", play.Type)
		}

		// add volume credits
		volumeCredits += int(math.Max(float64(perf.Audience)-30, 0))
		// add extra credit for every ten comedy attendees
		if play.Type == "comedy" {
			volumeCredits += int(math.Floor(float64(perf.Audience) / 5))
		}

		// print line for this order
		result += fmt.Sprintf("  %s: %s (%d seats)\n", play.Name, ac.FormatMoney(float64(thisAmount)/100), perf.Audience)
		totalAmount += thisAmount
	}
	result += fmt.Sprintf("Amount owed is %s\n", ac.FormatMoney(float64(totalAmount)/100))
	result += fmt.Sprintf("You earned %d credits\n", volumeCredits)
	return result, nil
}
