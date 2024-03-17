<?php
declare(strict_types=1);

namespace Theatrical;

class StatementLine
{
    private function __construct(private string $name, private float|int $performanceCost, private int $audience)
    {

    }

    public static function create(string $name, float|int $performanceCost, int $audience): self
    {
        return new self($name, $performanceCost, $audience);
    }

    public function playName(): string
    {
        return $this->name;
    }

    public function performanceCost(): float
    {
        return $this->performanceCost;
    }

    public function audience(): int
    {
        return $this->audience;
    }

}
