import { describe, it, expect } from "@jest/globals";
import { Play } from "../src/Play";
import { Performance } from "../src/Performance";
import { Invoice } from "../src/Invoice";
import { StatementPrinter } from "../src/StatementPrinter";

describe('StatementPrinter', () => {
    it('test can print invoice', () => {
        const plays = {
            "hamlet": new Play("Hamlet", "tragedy"),
            "as-like": new Play("As You Like It", "comedy"),
            "othello": new Play("Othello", "tragedy")
        };

        const performances = [
            new Performance("hamlet", 55),
            new Performance("as-like", 35),
            new Performance("othello", 40)
        ];

        const invoice = new Invoice("BigCo", performances);

        const statementPrinter: StatementPrinter = new StatementPrinter();
        const result = statementPrinter.print(invoice, plays);

        expect(result).toMatchSnapshot();
    });

    it('test new play types', () => {
        const plays = {
            "henry-v": new Play("Henry V", "history"),
            "as-like": new Play("As You Like It", "comedy"),
        };

        const performances = [
            new Performance("henry-v", 53),
            new Performance("as-like", 55),
        ];

        const invoice = new Invoice("BigCo", performances);
        const statementPrinter = new StatementPrinter();
        expect(() => statementPrinter.print(invoice, plays)).toThrow(/unknown type/);
    });
});
