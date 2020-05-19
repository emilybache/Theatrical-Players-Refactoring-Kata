<?php

declare(strict_types=1);

namespace Theatrical;

class Play
{
    /**
     * @var string
     */
    public $name;

    /**
     * @var string
     */
    public $type;

    public function __construct(string $name, string $type)
    {
        $this->name = $name;
        $this->type = $type;
    }

    public function __toString()
    {
        return (string) $this->name . ' : ' . $this->type;
    }
}
