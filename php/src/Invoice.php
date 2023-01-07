<?php

declare(strict_types=1);

namespace Theatrical;

class Invoice
{
    /**
     * @param array<int, Performance> $performances
     */
    public function __construct(
        public string $customer,
        public array $performances
    ) {
    }
}
