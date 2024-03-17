<?php
declare(strict_types=1);

namespace Theatrical;

class Statement
{
    private float $totalAmount;
    private float $volumeCredits;
    /** @var StatementLine[] */
    private array $lines;
    private string $customer;

    /** @param array<string, Play> $plays */
    private function __construct(Invoice $invoice, array $plays)
    {
        $this->totalAmount = 0;
        $this->volumeCredits = 0;
        $this->customer = $invoice->customer;
        foreach ($invoice->performances as $performance) {
            $play = $plays[$performance->playId];
            $performanceCost = $performance->performancePlayCost($play);

            $this->volumeCredits += $performance->volumeCredits($play);

            $this->lines[] = StatementLine::create($play->name, $performanceCost, $performance->audience);

            $this->totalAmount += $performanceCost;
        }
    }

    /** @param array<string, Play> $plays */
    public static function forInvoice(Invoice $invoice, array $plays): self
    {
        return new self($invoice, $plays);
    }

    /** @return array<StatementLine> */
    public function lines():array
    {
        return $this->lines;
    }

    public function total(): float
    {
        return $this->totalAmount;
    }

    public function volumeCredits(): float
    {
        return $this->volumeCredits;
    }

    public function customer(): string
    {
        return $this->customer;
    }
}
