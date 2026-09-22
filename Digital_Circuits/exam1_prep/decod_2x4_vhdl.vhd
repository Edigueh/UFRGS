library ieee;
use ieee.std_logic_1164.all;

ENTITY decod_2x4 IS
   PORT (
        e : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        s : OUT STD_LOGIC_VECTOR (3 DOWNTO 0)
   );
END decod_2x4;

ARCHITECTURE impl of decod_2x4 IS
BEGIN
    WITH e SELECT
        s <= "0001" WHEN "00",
             "0010" WHEN "01",
             "0100" WHEN "10",
             "1000" WHEN "11",
             "0000" WHEN OTHERS;
END impl;
