package theatricalplays;

import java.util.Map;
import java.util.Objects;

public final class StatementData {
    private final Invoice invoice;
    private final Map<String, Play> plays;

    public StatementData(Invoice invoice, Map<String, Play> plays) {
        this.invoice = invoice;
        this.plays = plays;
    }

    public Invoice invoice() {
        return invoice;
    }

    public Map<String, Play> plays() {
        return plays;
    }

}