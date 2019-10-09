## Theatrical-Players-Refactoring-Kata (Go)

This variant provides the kata in [Go](www.golang.org).

### Installation

* Install Go 1.12 (or later)
* In the directory of this file, run `go mod download`
* You can then run tests with `go test ./...`

### Approval Tests

Approval tests are run with a basic home-grown approval function (see `approval_test.go`).

In short, for a new test case of `TestPrinterPrintByApproval`:
* Add a new `.in.json` file under `testdata/TestPrinterPrintByApproval`. You can copy an existing one for starters.
* Run `go test ./...` - it should fail and complain about a missing file.
* However, a `.out.txt` file will have been created - use this one as the new `.approved.txt` file.

#### Approval-testing errors

Right now, the error is tested in-line. You can convert this test to an approval-test as well.
