package theatricalplays;

import java.util.Map;

public final class StatementData {
    private final Invoice invoice;
    private final Map<String, Play> plays;

    public StatementData(Invoice invoice, Map<String, Play> plays) {
        this.invoice = invoice;
        this.plays = plays;
    }

    public Map<String, Play> getPlays() {
        return plays;
    }

    public Invoice getInvoice() {
        return invoice;
    }
}