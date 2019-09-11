struct Invoice {
    let customer: String
    let performances: [Performance]
    init(_ customer: String, _ performances: Array<Performance>) {
        self.customer = customer
        self.performances = performances
    }
}
