import 'package:theatrical_plays/performance.dart';

class Invoice {
  
  final String customer;
  final List<Performance> performances;

  Invoice(this.customer, this.performances);
}