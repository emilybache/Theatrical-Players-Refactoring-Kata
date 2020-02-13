<?php

namespace Theatrical;
use Theatrical\Play;
use Theatrical\Invoice;
use Theatrical\Performance;

class StatementPrinter
{
    public function print(Invoice $invoice, array $plays) 
    {
        $totalAmount = 0;
        $volumeCredits = 0;

        $result = 'Statement for ' . $invoice->customer . '\n';

        foreach($invoice->performances as $performance)
        {
            $play = $plays[$performance->play_id];

            $thisAmount = 0;

            switch($play->type)
            {
                case "tragedy":
                    $thisAmount = 40000;
                    if($performance->audience > 30)
                    {
                        $thisAmount += 1000 * ($performance->audience - 30);
                    }
                    break;

                case "comedy":
                    $thisAmount = 30000;
                    if($performance->audience > 20)
                    {
                        $thisAmount += 10000 + 500 * ($performance->audience - 20);
                    }
                    $thisAmount += 300 * $performance->audience;
                    break;

                default:
                    throw new \Error("Unknow type: $play->type");
            }
            
            $volumeCredits += max($performance->audience - 30, 0);
            if($play->type == 'comedy')
            {
                $volumeCredits += floor($performance->audience / 5);
            }
            $thisFinalAmount = $thisAmount / 100;
            $result = "$play->name: $thisFinalAmount ($performance->audience seats)\n";
            $totalAmount += $thisAmount;
        }

        $finalTotal = ($totalAmount / 100);
        $result .= "Amount owed is $finalTotal\n";
        $result .= "You earned $volumeCredits credits\n";
        return $result;


    }
}