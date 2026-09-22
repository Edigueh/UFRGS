library ieee;
use ieee.std_logic_1164.all;

ENTITY codif_4x2 IS
    PORT (
        e : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
        s : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
    );
END codif_4x2;

ARCHITECTURE impl of codif_4x2 IS
BEGIN
    s <= "11" WHEN e(3) = '1' ELSE
         "10" WHEN e(2) = '1' ELSE
         "01" WHEN e(1) = '1' ELSE
         "00";
END impl;
