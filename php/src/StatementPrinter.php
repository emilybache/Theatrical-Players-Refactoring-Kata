<?php

declare(strict_types=1);

namespace Theatrical;

use Error;
use NumberFormatter;

class StatementPrinter
{
    private const TRAGEDY_BASELINE_COST = 40000;
    private const COMEDY_BASELINE_COST = 30000;

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

    private function tragedyCost(Performance $performance): int|float
    {
        if ($performance->audience > 30) {
            return self::TRAGEDY_BASELINE_COST + (1000 * ($performance->audience - 30));
        }

        return self::TRAGEDY_BASELINE_COST;
    }

    private function comedyCost(Performance $performance): int|float
    {
        if ($performance->audience > 20) {
            $cost = $this->comedyBaseCost($performance);

            $cost += 10000 + 500 * ($performance->audience - 20);

            return $cost;
        }

        return $this->comedyBaseCost($performance);
    }

    private function performancePlayCost(Play $play, Performance $performance): int|float
    {
        switch ($play->type) {
            case 'tragedy':
                return $this->tragedyCost($performance);

            case 'comedy':
                return $this->comedyCost($performance);

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

    private function comedyBaseCost(Performance $performance): int|float
    {
        return self::COMEDY_BASELINE_COST + (300 * $performance->audience);
    }
}
