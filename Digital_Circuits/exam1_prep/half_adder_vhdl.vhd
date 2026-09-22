library ieee;
use ieee.std_logic_1164.all;

ENTITY half_adder IS
    PORT(
        x, y : IN STD_LOGIC;
        s, co: OUT STD_LOGIC
    );
END half_adder;

ARCHITECTURE impl OF half_adder IS
BEGIN
    s <= x XOR y;
    co <= x AND y;
END impl;
