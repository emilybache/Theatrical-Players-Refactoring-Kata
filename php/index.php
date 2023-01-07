<?php

declare(strict_types=1);

use Theatrical\HtmlStatement;
use Theatrical\Invoice;
use Theatrical\Performance;
use Theatrical\Play;

require __DIR__ . '/vendor/autoload.php';

$plays = [
    'hamlet' => new Play('Hamlet', 'tragedy'),
    'as-like' => new Play('As You Like It', 'comedy'),
    'othello' => new Play('Othello', 'tragedy'),
];

$performances = [
    new Performance('hamlet', 55),
    new Performance('as-like', 35),
    new Performance('othello', 40),
];
$invoice = new Invoice('BigCo', $performances);

echo '<h1>Html Statement</h1>';

// Uncomment the following two line once the HtmlStatement Class is written (Ch.1 page 31)
//$statementPrinter = new HtmlStatement();
//echo  $statementPrinter->print($invoice, $plays);
