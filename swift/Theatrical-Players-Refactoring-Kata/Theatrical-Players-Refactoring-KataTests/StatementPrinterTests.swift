
import XCTest
@testable import Theatrical_Players_Refactoring_Kata

class StatementPrinterTests: XCTestCase {
    func test_exampleStatement() throws {
        
        let expected = """
            Statement for BigCo
              Hamlet: $650.00 (55 seats)
              As You Like It: $580.00 (35 seats)
              Othello: $500.00 (40 seats)
            Amount owed is $1,730.00
            You earned 47 credits

            """
        
        let plays = [
            "hamlet": Play(name: "Hamlet", type: "tragedy"),
            "as-like": Play(name: "As You Like It", type: "comedy"),
            "othello": Play(name: "Othello", type: "tragedy")
        ]
        
        let invoice = Invoice(
            customer: "BigCo", performances: [
                Performance(playID: "hamlet", audience: 55),
                Performance(playID: "as-like", audience: 35),
                Performance(playID: "othello", audience: 40)
            ]
        )
        
        let statementPrinter = StatementPrinter()
        let result = try statementPrinter.print(invoice, plays)
        
        XCTAssertEqual(result, expected)
    }
    
    func test_statementWithNewPlayTypes() {
        let plays = [
            "henry-v": Play(name: "Henry V", type: "history"),
            "as-like": Play(name: "As You Like It", type: "pastoral")
        ]
        
        let invoice = Invoice(
            customer: "BigCo", performances: [
                Performance(playID: "henry-v", audience: 53),
                Performance(playID: "as-like", audience: 55)
            ]
        )
        
        let statementPrinter = StatementPrinter()
        XCTAssertThrowsError(try statementPrinter.print(invoice, plays))        
    }
}

