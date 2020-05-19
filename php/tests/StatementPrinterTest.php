<?php

declare(strict_types=1);

namespace Tests;

use ApprovalTests\Approvals;
use Error;
use PHPUnit\Framework\TestCase;
use Theatrical\Invoice;
use Theatrical\Performance;
use Theatrical\Play;
use Theatrical\StatementPrinter;

final class StatementPrinterTest extends TestCase
{
    public function testCanPrintInvoice(): void
    {
        $plays = [
            'hamlet' => new Play('Hamlet', 'tragedy'),
            'as-like' => new Play('As You Like It', 'comedy'),
            'othello' => new Play('Othello', 'tragedy'),
        ];

        $performances = [
            new Performance('hamlet', 55),
            new Performance('as-like', 35),
            new Performance('othello', 40),
        ];
        $invoice = new Invoice('BigCo', $performances);
        $statementPrinter = new StatementPrinter();
        $result = $statementPrinter->print($invoice, $plays);

        Approvals::verifyString($result);
    }

    public function testNewPlayTypes(): void
    {
        $plays = [
            'henry-v' => new Play('Henry V', 'history'),
            'as-like' => new Play('As You Like It', 'comedy'),
        ];

        $performances = [new Performance('henry-v', 53), new Performance('as-like', 55)];

        $invoice = new Invoice('BigCo', $performances);
        $statementPrinter = new StatementPrinter();
        $this->expectException(Error::class);
        $statementPrinter->print($invoice, $plays);
    }
}
