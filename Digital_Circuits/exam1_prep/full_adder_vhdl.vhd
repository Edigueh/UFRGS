library ieee;
use ieee.std_logic_1164.all;

ENTITY full_adder IS
    PORT (
        x, y, z : IN STD_LOGIC;
        s, co : OUT STD_LOGIC
    );
END full_adder;

ARCHITECTURE impl OF full_adder IS
BEGIN
    s <= x XOR y XOR z;
    co <= (x AND Y) OR (z AND (X XOR Y));
END impl;
