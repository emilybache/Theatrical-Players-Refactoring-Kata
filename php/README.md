# Theatrical Players Refactoring Kata - PHP version

See the [top level readme](../README.md) for general information
 about this exercise. This is the PHP version of the Theatrical Players Refactoring Kata. Download the PDF of the first 
chapter of ['Refactoring' by Martin Fowler, 2nd Edition](https://www.thoughtworks.com/books/refactoring2) which contains 
a worked example of this exercise, in javascript.

## Installation

The kata uses:

- [PHP 8.0+](https://www.php.net/downloads.php)
- [Composer](https://getcomposer.org)

Recommended:

- [Git](https://git-scm.com/downloads)

See [GitHub cloning a repository](https://help.github.com/en/articles/cloning-a-repository) for details on how to
create a local copy of this project on your computer.

```sh
git clone git@github.com:emilybache/Theatrical-Players-Refactoring-Kata.git
```

or

```shell script
git clone https://github.com/emilybache/Theatrical-Players-Refactoring-Kata.git
```

Install all the dependencies using composer:

```sh
cd ./Theatrical-Players-Refactoring-Kata/php
composer install
```

## Dependencies

The project uses composer to install:

- [PHPUnit](https://phpunit.de/)
- [ApprovalTests.PHP](https://github.com/approvals/ApprovalTests.php)
- [PHPStan](https://github.com/phpstan/phpstan)
- [Easy Coding Standard (ECS)](https://github.com/symplify/easy-coding-standard)

## Folders

- `src` - Contains the **StatementPrinter** Class along with the setup classes. Only **StatementPrinter.php** is
    refactored. 
- `tests` - Contains the corresponding tests. There should be no need to amend the test.
  - `approvals` - Contains the text output for the tests. There should be no need to amend.

## Testing

PHPUnit is configured for testing, a composer script has been provided. To run the unit tests, from the root of the PHP
project run:

```shell script
composer tests
```

On Windows a batch file has been created, like an alias on Linux/Mac (e.g. `alias pu="composer tests"`), the same
PHPUnit `composer tests` can be run:

```shell script
pu.bat
```

### Tests with Coverage Report

To run all test and generate a html coverage report run:

```shell script
composer test-coverage
```

The test-coverage report will be created in /builds, it is best viewed by opening /builds/**index.html** in your
browser.

The [XDEbug](https://xdebug.org/download) extension is required for coverage report generating. 

## Code Standard

Easy Coding Standard (ECS) is configured for style and code standards,
**[PSR-12](https://www.php-fig.org/psr/psr-12/)** is used. As the code is constantly being refactored only run code
  standard checks once the chapter is complete.

### Check Code

To check code, but not fix errors:

```shell script
composer check-cs
``` 

On Windows a batch file has been created, like an alias on Linux/Mac (e.g. `alias cc="composer check-cs"`), the
 same ECS `composer check-cs` can be run:

```shell script
cc.bat
```

### Fix Code

ECS provides may code fixes, automatically, if advised to run --fix, the following script can be run:

```shell script
composer fix-cs
```

On Windows a batch file has been created, like an alias on Linux/Mac (e.g. `alias fc="composer fix-cs"`), the same
 ECS `composer fix-cs` can be run:

```shell script
fc.bat
```

## Static Analysis

PHPStan is used to run static analysis checks. As the code is constantly being refactored only run static analysis
  checks once the chapter is complete.

```shell script
composer phpstan
```

On Windows a batch file has been created, like an alias on Linux/Mac (e.g. `alias ps="composer phpstan"`), the
 same PHPStan `composer phpstan` can be run:

```shell script
ps.bat
```

**Happy coding**!
