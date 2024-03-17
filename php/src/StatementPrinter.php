<?php

declare(strict_types=1);

namespace Theatrical;

use NumberFormatter;

class StatementPrinter
{
    /**
     * @param array<string, Play> $plays
     */
    public function print(Invoice $invoice, array $plays): string
    {
        $statement = Statement::forInvoice($invoice, $plays);

        $result = "Statement for {$statement->customer()}\n";
        $format = new NumberFormatter('en_US', NumberFormatter::CURRENCY);

        foreach ($statement->lines() as $line) {
            $result .= "  {$line->playName()}: {$format->formatCurrency($line->performanceCost() / 100, 'USD')} ";
            $result .= "({$line->audience()} seats)\n";
        }

        $result .= "Amount owed is {$format ->formatCurrency($statement->total() / 100, 'USD')}\n";
        $result .= "You earned {$statement->volumeCredits()} credits";

        return $result;
    }
}
