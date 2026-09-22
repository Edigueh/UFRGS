library ieee;
use ieee.std_logic_1164.all;

ENTITY demux_1x4 IS
    PORT (
        e : IN STD_LOGIC;
        sel: IN STD_LOGIC_VECTOR(1 DOWNTO 0);
        s : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
    );
END demux_1x4;

ARCHITECTURE impl OF demux_1x4 IS
BEGIN
s <=     ('0', '0', '0', e) when sel = "00" else
         ('0', '0', e, '0') when sel = "01" else
         ('0', e, '0', '0') when sel = "10" else
         (e, '0', '0', '0') when sel = "11" else
         "0000";
END impl;
