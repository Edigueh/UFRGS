library ieee;
use ieee.std_logic_1164.all;

ENTITY comp_2v4b IS
    PORT(
        a, b : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        result : OUT STD_LOGIC
    );
END comp_2v4b;

ARCHITECTURE impl OF comp_2v4b IS
BEGIN
    result <= '1' WHEN (a = b) ELSE '0';
END impl;
