<?php

declare(strict_types=1);

namespace Theatrical;

class Invoice
{
    /**
     * @var string
     */
    public $customer;

    /**
     * @var array
     */
    public $performances;

    public function __construct(string $customer, array $performances)
    {
        $this->customer = $customer;
        $this->performances = $performances;
    }
}
