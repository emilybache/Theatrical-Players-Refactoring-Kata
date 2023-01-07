<?php

declare(strict_types=1);

namespace Theatrical;

class Play implements \Stringable
{
    public function __construct(
        public string $name,
        public string $type
    ) {
    }

    public function __toString(): string
    {
        return (string) $this->name . ' : ' . $this->type;
    }
}
