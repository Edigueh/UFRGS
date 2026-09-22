library ieee;
use ieee.std_logic_1164.all;

ENTITY mux_4x1 IS
    PORT (
        e0, e1, e2, e3 : IN STD_LOGIC;
        sel : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
        s : OUT STD_LOGIC
    );
END mux_4x1;

ARCHITECTURE impl OF mux_4x1 IS
BEGIN
    WITH sel SELECT
        s <= e0 WHEN "00",
             e1 WHEN "01",
             e2 WHEN "10",
             e3 WHEN OTHERS;
END impl;
