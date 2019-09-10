
import org.junit.jupiter.api.Assertions.assertThrows
import org.junit.jupiter.api.Test
import org.approvaltests.Approvals.verify

class StatementPrinterTests {

    @Test
    internal fun exampleStatement() {

        val plays = mapOf(
            "hamlet" to Play("Hamlet", "tragedy"),
            "as-like" to Play("As You Like It", "comedy"),
            "othello" to Play("Othello", "tragedy")
        )

        val invoice = Invoice(
            "BigCo", listOf(
                Performance("hamlet", 55),
                Performance("as-like", 35),
                Performance("othello", 40)
            )
        )

        val statementPrinter = StatementPrinter()
        val result = statementPrinter.print(invoice, plays)

        verify(result)
    }

    @Test
    internal fun statementWithNewPlayTypes() {
        val plays = mapOf(
            "henry-v" to Play("Henry V", "history"),
            "as-like" to Play("As You Like It", "pastoral")
        )

        val invoice = Invoice(
            "BigCo", listOf(
                Performance("henry-v", 53),
                Performance("as-like", 55)
            )
        )

        val statementPrinter = StatementPrinter()
        assertThrows(Error::class.java) { statementPrinter.print(invoice, plays) }
    }
}
