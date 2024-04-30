package theatre_test

import (
	"encoding/json"
	"testing"

	"github.com/emilybache/Theatrical-Players-Refactoring-Kata/go/theatre"
)

func TestPrinterPrintByApproval(t *testing.T) {
	verify(t, "json", "txt", func(t testing.TB, data []byte) []byte {
		var printer theatre.StatementPrinter
		statement, err := printer.Print(createTestData(t, data))
		if err != nil {
			t.Fatalf("failed to create statement, unexpected error: %v", err)
		}
		return []byte(statement)
	})
}

func TestStatementWithNewPlayTypes(t *testing.T) {
	plays := map[string]theatre.Play{
		"henry-v": {Name: "Henry V", Type: "history"},
		"as-like": {Name: "As You Like It", Type: "pastoral"},
	}
	invoice := theatre.Invoice{
		Customer: "BigCo",
		Performances: []theatre.Performance{
			{PlayID: "henry-v", Audience: 53},
			{PlayID: "as-like", Audience: 55},
		},
	}

	var printer theatre.StatementPrinter
	_, err := printer.Print(invoice, plays)
	if err == nil {
		t.Errorf("Expected an error, got none")
	}
}

func createTestData(t testing.TB, data []byte) (theatre.Invoice, map[string]theatre.Play) {
	var in struct {
		Plays []struct {
			ID   string
			Play struct {
				Name string
				Type string
			}
		}
		Invoice struct {
			Customer     string
			Performances []struct {
				PlayID   string
				Audience int
			}
		}
	}

	if err := json.Unmarshal(data, &in); err != nil {
		t.Fatalf("failed to unmarshal input data: %v", err)
	}

	invoice := theatre.Invoice{
		Customer:     in.Invoice.Customer,
		Performances: make([]theatre.Performance, 0, len(in.Invoice.Performances)),
	}
	for _, perf := range in.Invoice.Performances {
		invoice.Performances = append(invoice.Performances, perf)
	}

	plays := make(map[string]theatre.Play)
	for _, identifiedPlay := range in.Plays {
		plays[identifiedPlay.ID] = identifiedPlay.Play
	}

	return invoice, plays
}
