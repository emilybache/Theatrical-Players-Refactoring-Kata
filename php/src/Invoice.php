<?php

namespace Theatrical;

class Invoice
{
    public string $customer;
    public array $performances;

    public function __construct($customer, $performances)
    {
        $this->customer = $customer;
        $this->performances = $performances;
    }
    
}