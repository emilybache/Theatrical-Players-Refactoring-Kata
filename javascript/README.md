### Changes made

1. Refactored code into 3 separate functions: `statement`, `evaluatePlays`, and `formatCurrency` to encourage _Single-Responsibility Principle_.
2. Renamed variables to be more meaningful. For example, the custom `format` function has been renamed to `formatCurrency` so that it is self-defined and discriminable as a currency style format function from the `NumberFormat` object.
3. Instantiated child referencing variables at the beginning of function calls to reduce _divergent change_ and duplication, and encourage organization.
