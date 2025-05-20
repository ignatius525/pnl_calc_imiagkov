# pnl_calc_imiagkov

## Usage
`./pnl_calc {file of choice} {fifo | lifo}`  

Create and cd into build directory `mkdir build && cd build`
Cmake setup `cmake ..`
Build `build`

`moretickers.csv` will be copied into binary directory (in `/data`) for ease of testing example and for unit tests. Feel free to designate your own as part of command line.

Example run (from build directory)
`./pnl_calc data/moretickers.csv fifo`

### Unit tests
Gtest and Gmock should automatically be pulled in via content fetcher (by default when running build commands above)
`./test/test_pnl_calc`
