<?php

namespace Theatrical;

class Play 
{
    public string $name;
    public string $type;

    public function __construct($name, $type)
    {
        $this->name = $name;
        $this->type = $type;
    }

    public function __toString()
    {
        return (string) $this->name . ' : ' . $this->type;
    }
}