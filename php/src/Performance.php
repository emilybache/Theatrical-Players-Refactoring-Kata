<?php

namespace Theatrical;

class Performance 
{
    public string $play_id;
    public int $audience;

    public function __construct($play_id, $audience)
    {
        $this->play_id = $play_id;
        $this->audience = $audience;
    }
}