<?php

declare(strict_types=1);

namespace Theatrical;

class Performance
{
    public function __construct(
        public string $playId,
        public int $audience
    ) {
    }
}
