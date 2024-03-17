<?php

declare(strict_types=1);

namespace Theatrical;

use Error;

class Performance
{
    private const TRAGEDY_BASELINE_COST = 40000;
    private const COMEDY_BASELINE_COST = 30000;

    public function __construct(
        public string $playId,
        public int $audience
    ) {
    }

    public function performancePlayCost(Play $play): int|float
    {
        switch ($play->type) {
            case 'tragedy':
                return $this->tragedyCost($this);

            case 'comedy':
                return $this->comedyCost($this);

            default:
                throw new Error("Unknown type: {$play->type}");
        }
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

    private function comedyBaseCost(Performance $performance): int|float
    {
        return self::COMEDY_BASELINE_COST + (300 * $performance->audience);
    }

    public function volumeCredits(Play $play): float
    {
        if ($play->type === 'comedy') {
            $volumeCredits = max($this->audience - 30, 0);
            $volumeCredits += floor($this->audience / 5);

            return $volumeCredits;
        }

        return max($this->audience - 30, 0);
    }
}
