# Testing
This folder contains tests associated with this project. These tests leverage
the CUnit framework to validate both the individual functions within the DNS
manager and the overall functionality of the program itself.

## Run Tests
To run tests, run the following command:
```
make check
```
This will compile and run the source code necessary for testing and will run
tests both on the dns management system and the main method associated with
the DNS daemon implemented here.