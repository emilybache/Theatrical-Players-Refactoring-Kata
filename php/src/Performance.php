<?php

declare(strict_types=1);

namespace Theatrical;

class Performance
{
    /**
     * @var string
     */
    public $play_id;

    /**
     * @var int
     */
    public $audience;

    /**
     * @var Play
     */
    public $play;

    public function __construct(string $play_id, int $audience)
    {
        $this->play_id = $play_id;
        $this->audience = $audience;
    }
}
