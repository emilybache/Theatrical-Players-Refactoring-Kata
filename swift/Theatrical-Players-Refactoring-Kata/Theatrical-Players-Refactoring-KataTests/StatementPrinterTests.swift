
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
            "hamlet": Play("Hamlet", "tragedy"),
            "as-like": Play("As You Like It", "comedy"),
            "othello": Play("Othello", "tragedy")
        ]
        
        let invoice = Invoice(
            "BigCo", [
                Performance("hamlet", 55),
                Performance("as-like", 35),
                Performance("othello", 40)
            ]
        )
        
        let statementPrinter = StatementPrinter()
        let result = try statementPrinter.print(invoice, plays)
        
        XCTAssertEqual(expected, result)
    }
    
    func test_statementWithNewPlayTypes() {
        let plays = [
            "henry-v": Play("Henry V", "history"),
            "as-like": Play("As You Like It", "pastoral")
        ]
        
        let invoice = Invoice(
            "BigCo", [
                Performance("henry-v", 53),
                Performance("as-like", 55)
            ]
        )
        
        let statementPrinter = StatementPrinter()
        XCTAssertThrowsError(try statementPrinter.print(invoice, plays))        
    }
}

