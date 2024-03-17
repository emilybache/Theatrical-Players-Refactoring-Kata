<?php

declare(strict_types=1);

namespace Theatrical;

use Error;
use NumberFormatter;

class StatementPrinter
{
    /**
     * @param array<string, Play> $plays
     */
    public function print(Invoice $invoice, array $plays): string
    {
        $totalAmount = 0;
        $volumeCredits = 0;

        $result = "Statement for {$invoice->customer}\n";
        $format = new NumberFormatter('en_US', NumberFormatter::CURRENCY);

        foreach ($invoice->performances as $performance) {
            $play = $plays[$performance->playId];
            $performanceCost = $this->performancePlayCost($play, $performance);

            $volumeCredits = $this->getVolumeCredits($performance, $volumeCredits, $play);

            // print line for this order
            $result .= "  {$play->name}: {$format->formatCurrency($performanceCost / 100, 'USD')} ";
            $result .= "({$performance->audience} seats)\n";

            $totalAmount += $performanceCost;
        }

        $result .= "Amount owed is {$format ->formatCurrency($totalAmount / 100, 'USD')}\n";
        $result .= "You earned {$volumeCredits} credits";
        return $result;
    }

    private function tragedyAmount(Performance $performance): int|float
    {
        $thisAmount = 40000;
        if ($performance->audience > 30) {
            $thisAmount += 1000 * ($performance->audience - 30);
        }
        return $thisAmount;
    }

    private function comedyAmount(Performance $performance): int|float
    {
        $thisAmount = 30000;
        if ($performance->audience > 20) {
            $thisAmount += 10000 + 500 * ($performance->audience - 20);
        }
        $thisAmount += 300 * $performance->audience;
        return $thisAmount;
    }

    private function performancePlayCost(Play $play, Performance $performance): int|float
    {
        switch ($play->type) {
            case 'tragedy':
                return $this->tragedyAmount($performance);

            case 'comedy':
                return $this->comedyAmount($performance);

            default:
                throw new Error("Unknown type: {$play->type}");
        }
    }

    private function getVolumeCredits(Performance $performance, mixed $volumeCredits, Play $play): mixed
    {
// add volume credits
        $volumeCredits += max($performance->audience - 30, 0);
        // add extra credit for every ten comedy attendees
        if ($play->type === 'comedy') {
            $volumeCredits += floor($performance->audience / 5);
        }
        return $volumeCredits;
    }
}
