//Using SPI protocol

//SCL -> SPI CLOCK
//SDA -> SPI DATA

//CS -> Chip Select
//RST -> Screen Reset
//Rs/Ds -> Register Select (tells if data or command)
// BLK -> Back Light Led


// how SPI usually works,

// when CS is low, it means communication, otherwise no communication
// Usually there is a SDO for slave sending information, in this case, no info is sent out, only input
