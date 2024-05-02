package theatre_test

import (
	"encoding/json"
	approvals "github.com/approvals/go-approval-tests"
	"io"
	"os"
	"testing"

	"github.com/emilybache/Theatrical-Players-Refactoring-Kata/go/theatre"
)

func TestMain(m *testing.M) {
	approvals.UseFolder("testdata")
	m.Run()
}

func TestPrinterPrintByApproval(t *testing.T) {
	file, err := os.Open("testdata/input.json")
	if err != nil {
		t.Fatal("failed to open testdata/input.json", err)
	}

	var printer theatre.StatementPrinter
	statement, err := printer.Print(createTestData(t, file))
	if err != nil {
		t.Fatalf("failed to create statement, unexpected error: %v", err)
	}
	approvals.VerifyString(t, statement)
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

func createTestData(t testing.TB, r io.Reader) (theatre.Invoice, map[string]theatre.Play) {
	var in struct {
		Plays []struct {
			ID   string
			Play struct {
				Name string
				Type string
			}
		}
		Invoice theatre.Invoice
	}

	if err := json.NewDecoder(r).Decode(&in); err != nil {
		t.Fatalf("failed to decode input data: %v", err)
	}

	plays := make(map[string]theatre.Play)
	for _, identifiedPlay := range in.Plays {
		plays[identifiedPlay.ID] = identifiedPlay.Play
	}

	return in.Invoice, plays
}
