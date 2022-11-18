#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include <string>

extern "C"
{
#include "statement.h"
}

#define MAX_PRINT_LENGTH 20000

TEST_CASE ("Theatrical Players") {
    struct Play *hamlet = Play_create("hamlet", "Hamlet", "tragedy");
    struct Play *aslike = Play_create("as-like", "As You Like It", "comedy");
    struct Play *othello = Play_create("othello", "Othello", "tragedy");
    char result[MAX_PRINT_LENGTH];

    SECTION("existing play types") {
        struct Performance *bigCoHamlet = Performance_create("hamlet", 55);
        struct Performance *bigCoAsLike = Performance_create("as-like", 35);
        struct Performance *bigCoOthello = Performance_create("othello", 40);

        Performance *performances[] = {bigCoHamlet, bigCoAsLike, bigCoOthello};
        struct Invoice *invoice = Invoice_create("BigCo", performances);
        Play *plays[] = {hamlet, aslike, othello};

        int status = statement(result, invoice, 3, plays, 3);

        REQUIRE(status == NO_ERROR);
        ApprovalTests::Approvals::verify(std::string(result));
    }

    SECTION("new play types") {
        struct Play *henryv = Play_create("henry-v", "Henry V", "history");
        Play *plays[] = {aslike, henryv};
        struct Performance *bigCoIIAsLike = Performance_create("as-like", 55);
        struct Performance *bigCoIIHenryV = Performance_create("henry-v", 53);

        Performance *performances[] = {bigCoIIAsLike, bigCoIIHenryV};
        struct Invoice *invoice = Invoice_create("BigCoII", performances);

        int status = statement(result, invoice, 2, plays, 2);

        REQUIRE(status == UNKNOWN_PLAY_TYPE);
        ApprovalTests::Approvals::verify(std::string(result));
    }
}

TEST_CASE ("Currency Number Format") {
    SECTION("existing play types") {
        ApprovalTests::Approvals::verifyAll("format_currency_number",
                                            {1.0, 1.9, 1.99, 1000.0, 999.99, 1001.23,
                                             1001001.01,
                                             10001.1, 10000.0, 7500.0, 1234567.89,
                                             12345678.9},
                                            [](double input, std::ostream &stream) {
                                                stream << input << " => "
                                                       << format_currency_number(input)
                                                       << "\n";
                                            });
    }
}
